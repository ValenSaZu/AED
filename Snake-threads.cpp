#include <SFML/Graphics.hpp>
#include <time.h>
#include <thread>
#include <mutex>
#include <vector>

class Snake {
public:
    Snake(int initialSize, int gridSize, sf::Color color, int startX, int startY);
    ~Snake();

    // Añadir funciones de movimiento
    Snake(const Snake& other) = delete; // Elimina la copia
    Snake& operator=(const Snake& other) = delete; // Elimina la copia
    Snake(Snake&& other) noexcept; // Mueve el constructor
    Snake& operator=(Snake&& other) noexcept; // Mueve el operador de asignación

    void move(int direction);
    void checkBounds();
    void draw(sf::RenderWindow& window);

private:
    struct Segment {
        int x, y;
    };

    int size;
    int gridSize;
    sf::Color color;
    Segment* snake;
    std::mutex mutex;
};


Snake::Snake(int initialSize, int gridSize, sf::Color color, int startX, int startY)
    : size(initialSize), gridSize(gridSize), color(color) {
    snake = new Segment[size];
    // Inicializar la serpiente en una línea recta con coordenadas iniciales
    for (int i = 0; i < size; ++i) {
        snake[i].x = startX + i;
        snake[i].y = startY;
    }
}

Snake::~Snake() {
    delete[] snake;
}

// Implementar funciones de movimiento
Snake::Snake(Snake&& other) noexcept
    : size(other.size), gridSize(other.gridSize), color(other.color), snake(other.snake) {
    other.snake = nullptr; // Invalidar el objeto original
}

Snake& Snake::operator=(Snake&& other) noexcept {
    if (this != &other) {
        delete[] snake; // Liberar la memoria existente
        size = other.size;
        gridSize = other.gridSize;
        color = other.color;
        snake = other.snake;
        other.snake = nullptr; // Invalidar el objeto original
    }
    return *this;
}

void Snake::move(int direction) {
    std::lock_guard<std::mutex> lock(mutex);
    for (int i = size - 1; i > 0; --i) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    if (direction == 0) {
        snake[0].y += 1;
    }
    else if (direction == 1) {
        snake[0].x -= 1;
    }
    else if (direction == 2) {
        snake[0].x += 1;
    }
    else if (direction == 3) {
        snake[0].y -= 1;
    }
}

void Snake::checkBounds() {
    std::lock_guard<std::mutex> lock(mutex);
    for (int i = 0; i < size; ++i) {
        if (snake[i].x >= gridSize) {
            snake[i].x = 0;
        }
        else if (snake[i].x < 0) {
            snake[i].x = gridSize - 1;
        }
        if (snake[i].y >= gridSize) {
            snake[i].y = 0;
        }
        else if (snake[i].y < 0) {
            snake[i].y = gridSize - 1;
        }
    }
}

void Snake::draw(sf::RenderWindow& window) {
    std::lock_guard<std::mutex> lock(mutex);
    sf::RectangleShape block(sf::Vector2f(gridSize, gridSize));
    block.setFillColor(color);
    block.setOutlineColor(sf::Color::White);
    block.setOutlineThickness(1);

    for (int i = 0; i < size; ++i) {
        block.setPosition(snake[i].x * gridSize, snake[i].y * gridSize);
        window.draw(block);
    }
}

class SnakeGame {
public:
    SnakeGame(int size, int gridSize);
    ~SnakeGame();

    void run();

private:
    sf::RenderWindow window;
    std::vector<Snake> snakes;
    std::vector<std::thread> threads;

    void runSnakeThread(Snake& snake, int initialDirection);

    // Elimina estas funciones ya que no son necesarias
    // Snake(const Snake& other);
    // Snake& operator=(const Snake& other);
};

void SnakeGame::runSnakeThread(Snake& snake, int initialDirection) {
    int direction = initialDirection;
    while (true) {
        snake.move(direction);
        snake.checkBounds();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust the wait time as needed

        // Optionally, update the direction logic here based on your game's rules.
        direction = rand() % 4;
    }
}

SnakeGame::SnakeGame(int size, int gridSize)
    : window(sf::VideoMode(size* gridSize, size* gridSize), "Snake Threads") {
    srand(static_cast<unsigned>(time(0))); // Inicializar la semilla para números aleatorios

    sf::Color colors[] = {
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color::Magenta
    };

    for (int i = 0; i < 5; ++i) {
        int startX = rand() % (size - 5);  // Ajusta según el tamaño de la serpiente
        int startY = rand() % size;
        snakes.emplace_back(5, gridSize, colors[i], startX, startY);
    }
}

SnakeGame::~SnakeGame() {
    for (auto& thread : threads) {
        thread.join();
    }
}

void SnakeGame::run() {
    srand(static_cast<unsigned>(time(0)));

    int v1 = (rand() + 2) % 4;
    int v2 = (rand() + 3) % 4;
    int v3 = (rand() + 5) % 4;
    int v4 = (rand() + 7) % 4;
    int v5 = (rand() + 13) % 4;

    int variables[5] = { v1,v2,v3,v4,v5 };
    int i = 0;
    for (auto& snake : snakes) {
        threads.emplace_back(&SnakeGame::runSnakeThread, this, std::ref(snake), variables[i]);
        i++;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (auto& snake : snakes) {
            snake.draw(window);
        }

        window.display();
    }
}

int main() {
    SnakeGame game(25, 25);
    game.run();

    return 0;
}