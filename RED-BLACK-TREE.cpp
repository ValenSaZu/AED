#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* parent;
    Node* left;
    Node* right;
    int color;
};

typedef Node* NodePtr;

class RedBlackTree {
private:
    NodePtr root;
    NodePtr TNULL;

    void initializeNULLNode(NodePtr node, NodePtr parent) {
        if (node != nullptr) {
            node->data = 0;
            node->parent = parent;
            node->left = nullptr;
            node->right = nullptr;
            node->color = 0;
        }
    }

    void preOrderHelper(NodePtr node) {
        if (node != TNULL) {
            cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(NodePtr node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    // Post order
    void postOrderHelper(NodePtr node) {
        if (node != TNULL) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data << " ";
        }
    }

    NodePtr searchTreeHelper(NodePtr node, int key) {
        if (node == TNULL || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    void deleteFix(NodePtr x) {
        NodePtr s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void rbTransplant(NodePtr u, NodePtr v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key) {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            deleteFix(x);
        }
    }

    int height(Node* p) {
        if (p == nullptr) {
            return 0;
        }
        return 1 + max(height(p->left), height(p->right));
    }

    void Balanceo(Node* q) {
        Node* recorre = q;
        while (recorre != nullptr) {
            int balance = height(recorre->right) - height(recorre->left);

            if (balance == -2) {
                recorre->color = 1;
                if (height(recorre->left->left) >= height(recorre->left->right)) {
                    rightRotate(recorre);
                }
                else {
                    leftRotate(recorre->left);
                    rightRotate(recorre);
                }
            }
            else if (balance == 2) {
                recorre->color = 1;
                if (height(recorre->right->right) >= height(recorre->right->left)) {
                    leftRotate(recorre);
                }
                else {
                    rightRotate(recorre->right);
                    leftRotate(recorre);
                }
            }

            recorre = recorre->parent;
        }
    }

    void insertFix(NodePtr k) {
        NodePtr u = nullptr;
        while (k != nullptr && k->parent != nullptr && k->parent->parent != nullptr && k->parent->color == 1) {
            if (k->parent == k->parent->parent->right && k->parent->parent->left) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                if(k->parent->parent->right) u = k->parent->parent->right;

                if (u && u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void printHelper(NodePtr root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->data << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    RedBlackTree() {
        initializeNULLNode(TNULL, nullptr);
        root = TNULL;
    }

    void preorder() {
        preOrderHelper(this->root);
    }

    void inorder() {
        inOrderHelper(this->root);
    }

    void postorder() {
        postOrderHelper(this->root);
    }

    NodePtr searchTree(int k) {
        return searchTreeHelper(this->root, k);
    }

    NodePtr minimum(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    NodePtr maximum(NodePtr node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    NodePtr successor(NodePtr x) {
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodePtr predecessor(NodePtr x) {
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    bool find(int v) {
        Node *p = root;
        bool confir = true;
        if (!root) return false;
        else {
            while (confir) {
                if (p->data == v) return true;
                if (p->data > v) {
                    if (p->left == NULL) { confir = false; }
                    else { p = p->left; }
                }
                if (p->data < v) {
                    if (p->right == NULL) { confir = false; }
                    else { p = p->right; }
                }
            }
        }
        return false;
    }

    void insert(int key) {

        if (!find(key)) {

            NodePtr node = new Node;
            node->parent = nullptr;
            node->data = key;
            node->left = TNULL;
            node->right = TNULL;
            node->color = 1;

            NodePtr y = nullptr;
            NodePtr x = this->root;

            while (x != TNULL) {
                y = x;
                if (node->data < x->data) {
                    x = x->left;
                }
                else {
                    x = x->right;
                }
            }

            node->parent = y;
            if (y == nullptr) {
                root = node;
            }
            else if (node->data < y->data) {
                y->left = node;
            }
            else {
                y->right = node;
            }

            if (node->parent == nullptr) {
                node->color = 0;
                return;
            }

            if (node->parent->parent == nullptr) {
                return;
            }
            Balanceo(node);
            insertFix(node);
        }
    }

    NodePtr getRoot() {
        return this->root;
    }

    void deleteNode(int data) {
        deleteNodeHelper(this->root, data);
    }

    void printTree() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }
};

void drawTree(sf::RenderWindow& window, NodePtr node, float x, float y, float xOffset, float level,
    const sf::Font& font) {
    if (!node) return;

    sf::CircleShape circle(20.f);
    circle.setFillColor((node->color == 1) ? sf::Color::Red : sf::Color::Black);
    circle.setPosition(x, y);

    window.draw(circle);

    sf::Text text(std::to_string(node->data), font, 20);
    text.setPosition(x + 8, y + 5);
    window.draw(text);

    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x - xOffset + 20, y + 80), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->left, x - xOffset, y + 80, xOffset / 2, level + 1, font);
    }

    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x + xOffset + 20, y + 80), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->right, x + xOffset, y + 80, xOffset / 2, level + 1, font);
    }
}

int main() {
    RedBlackTree arbol;

    sf::Font font;
    if (!font.loadFromFile("C:/Users/51955/source/repos/red-black-tree/SFML-2.6.1/arial.ttf")) {
        cerr << "Failed to load font." << endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Binary red-black tree");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) {
                    int dataue;
                    cout << "Enter dataue to add: ";
                    cin >> dataue;
                    arbol.insert(dataue);
                }

                if (event.key.code == sf::Keyboard::R) {
                    int dataue;
                    cout << "Enter dataue to remove: ";
                    cin >> dataue;
                    arbol.deleteNode(dataue);
                }
            }
        }

        window.clear(sf::Color::White);

        if (arbol.getRoot()) {
            drawTree(window, arbol.getRoot(), 640, 50, 300, 1, font);
        }

        window.display();
    }

    return 0;
};