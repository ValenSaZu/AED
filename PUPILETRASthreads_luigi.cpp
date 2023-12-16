#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

//mutex m;

void Busqueda(char(*p)[40], string palabraBuscada) {
    //lock_guard<mutex> lock(m);
    char* inicioPalabra = &palabraBuscada[0];
    char* finPalabra = &palabraBuscada[palabraBuscada.length() - 1];
    bool match{ true };

    //auto start = chrono::high_resolution_clock::now();

    cout << "PALABRA: " << palabraBuscada << endl;

    for (int fila = 0; fila < 40; fila++) {
        for (int col = 0; col < 40; col++) {
            if (p[fila][col] == *inicioPalabra) {
                if (palabraBuscada.length() == 1) {
                    cout << "Palabra de una letra: Encontrada en la fila " << fila << " columna " << col << endl;
                }
                if (p[fila][col + 1] == *(inicioPalabra + 1)) {
                    for (char* i{ &p[fila][col] }, * j{ inicioPalabra }; match && j <= finPalabra; i++, j++) {
                        if (*i != *j) {
                            match = false;
                        }
                    }
                    if (match) cout << "Derecha: Fila " << fila << " Columna " << col << endl;
                    else match = true;
                }
                if (p[fila + 1][col] == *(inicioPalabra + 1)) {
                    for (char* i{ &p[fila][col] }, * j{ inicioPalabra }; match && j <= finPalabra; i += 40, j++) {
                        if (*i != *j) {
                            match = false;
                        }
                    }
                    if (match) cout << "Abajo: Fila " << fila << " Columna " << col << endl;
                    else match = true;
                }
            }
        }
    }

    //auto end = chrono::high_resolution_clock::now();
    //auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    //cout << "Tiempo: " << duration.count() << " milisegundos" << endl;
    cout << endl;
}


int main() {
    // Define the words
    vector<string> words = { "copy", "swap", "data", "user", "computer" };

    // Define the size of the matrix
    const int rows = 40;
    const int cols = 40;

    // Initialize the matrix with spaces
    char matrix[rows][cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = (rand() % 26) + 97;
            //matrix[i][j] = ' ';
        }
    }

    // Place the words horizontally and vertically
    for (const string& word : words) {
        // Place horizontally
        int start_col = rand() % (cols - word.length() + 1);
        for (int i = 0; i < word.length(); ++i) {
            matrix[start_col][i] = word[i];
        }

        // Place vertically
        int start_row = rand() % (rows - word.length() + 1);
        for (int i = 0; i < word.length(); ++i) {
            matrix[i][start_row] = word[i];
        }
    }

    // Print the matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }

    //BUSQUEDA DE PALABRAS

    vector<thread> threads;

    for (const string& word : words) {
        threads.emplace_back(Busqueda, matrix, word);
    }

    auto start = chrono::high_resolution_clock::now();

    for (auto& thread : threads) {
        thread.join();
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Tiempo: " << duration.count() << " milisegundos" << endl;

	return 0;
}