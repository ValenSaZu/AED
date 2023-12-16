#include <iostream>
#include <string>
using namespace std;


int Busqueda(char(*p)[6], string palabraBuscada) {
    char* inicioPalabra = &palabraBuscada[0];
    char* finPalabra = &palabraBuscada[palabraBuscada.length() - 1];
    int contador{ 0 };
    bool match{ true };
    for (char(*filaPtr)[6] = p; filaPtr < p + 5; filaPtr++) {
        for (char* elementoPtr = *filaPtr; elementoPtr < *filaPtr + 6; elementoPtr++) {
            if (*elementoPtr == *inicioPalabra) {
                if (palabraBuscada.length() == 1) {
                    contador++;
                }
                if (*(elementoPtr + 1) == *(inicioPalabra + 1)) {
                    cout << "Derecha" << endl;
                    for (char* i{ elementoPtr }, * j{ inicioPalabra }; match && j <= finPalabra; i++, j++) {
                        if (*i == *j) {
                            match = true;
                        }
                        else {
                            match = false;
                        }
                    }
                    if (match == true) {
                        contador++;
                    }
                    else {
                        match == true;
                    }
                }
                if (elementoPtr > *filaPtr && *(elementoPtr - 1) == *(inicioPalabra + 1)) {
                    cout << "Izquierda" << endl;
                    for (char* i{ elementoPtr }, * j{ inicioPalabra }; match && j <= finPalabra; i--, j++) {
                        if (*i == *j) {
                            match = true;
                        }
                        else {
                            match = false;
                        }
                    }
                    if (match == true) {
                        contador++;
                    }
                    else {
                        match == true;
                    }
                }
                if ((filaPtr + 1) < p + 5 && *((*(filaPtr + 1)) + (elementoPtr - *filaPtr)) == *(inicioPalabra + 1)) {
                    cout << "Abajo" << endl;
                    for (char* i{ elementoPtr }, * j{ inicioPalabra }; match && j <= finPalabra; i += 6, j++) {
                        if (*i == *j) {
                            match = true;
                        }
                        else {
                            match = false;
                        }
                    }
                    if (match == true) {
                        contador++;
                    }
                    else {
                        match == true;
                    }
                }
                if (filaPtr > p && *((*(filaPtr - 1)) + (elementoPtr - *filaPtr)) == *(inicioPalabra + 1)) {
                    cout << "Arriba" << endl;
                    for (char* i{ elementoPtr }, * j{inicioPalabra}; match && j <= finPalabra; i-=6, j++) {
                        if (*i == *j) {
                            match = true;
                        }
                        else {
                            match = false;
                        }
                    }
                    if (match == true) {
                        contador++;
                    }
                    else {
                        match == true;
                    }
                }
            }
        }
    }
    return contador;
}

int main()
{
    char A[5][6] = { {'A','J','P','A','T','O'},{'M', 'L','O', 'T', 'A','P'},{'N', 'T', 'T', 'H', 'L', 'O'},{'K','H', 'A', 'T', 'O', 'L'},{'T', 'I', 'P', 'O', 'J', 'M'} };
    cout << Busqueda(A, "PATO");
    return 0;
}
