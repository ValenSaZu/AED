#include <iostream>

using namespace std;

template <class T>
struct nodoArray {
    T Array[5];
    T* puntero = Array;
    nodoArray<T>* previous;
    nodoArray(nodoArray<T>* p = NULL) {
        previous = p;
    }
};

template <class T>
struct PilaNodoArray {
    nodoArray<T>* elemento = new nodoArray<T>(NULL);

    void CPush(T valor) {
        if (elemento->puntero == elemento->Array + 5) {
            nodoArray<T>* newElement = new nodoArray<T>(elemento);
            newElement->puntero[0] = valor;
            newElement->puntero++;
            elemento = newElement;
        }
        else {
            elemento->puntero[0] = valor;
            elemento->puntero++;
        }
    }

    bool CPop(T& valor) {
        if (elemento->puntero == elemento->Array) {
            if (elemento->previous != NULL) {
                nodoArray<T>* tmp = elemento;
                elemento = elemento->previous;
                delete tmp;
            }
            else {
                return false;
            }
        }
        elemento->puntero--;
        valor = *(elemento->puntero);
        return true;
    }

    void Cprint() {
        for (nodoArray<T>* i = elemento; i != NULL; i = i->previous) {
            cout << "[";
            for (T* j = i->Array; j < i->puntero; j++) {
                cout << *j;
                if (j < i->puntero - 1) {
                    cout << "->";
                }
            }
            cout << "] -> ";
        }
        cout << "NULL" << endl;
    }
};

int main() {
    PilaNodoArray<int> p;
    for (int i = 0; i < 50; i++) {
        p.CPush(i);
    }
    p.Cprint();

    int pop;
    while (p.CPop(pop)) {
        cout << "Pop: " << pop << endl;
    }

    p.Cprint();

    return 0;
}
