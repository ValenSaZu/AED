#include <iostream>

using namespace std;

template <class T>
struct nodoArray {
    T Array[5];
    nodoArray<T>* previous;
    nodoArray(nodoArray<T>* p = NULL) {
        previous = p;
    }
};

template <class T>
struct PilanodoArray {
    nodoArray<T>* TOP;
    T* puntero;
    T pop();
    void push(T v);
    bool vacio();
    void print();

    PilanodoArray() : TOP(nullptr), puntero(nullptr) {}
};

template <class T>
void PilanodoArray<T>::push(T v) {
    if (!TOP || puntero == TOP->Array + 4) {
        TOP = new nodoArray<T>(TOP);
        puntero = TOP->Array;
        *puntero = v;
    }
    else {
        puntero++;
        *puntero = v;
    }
}

template <class T>
T PilanodoArray<T>::pop() {
    T valor = *puntero;
    if (TOP && puntero != TOP->Array) {
        puntero--;
    }
    else if (TOP && puntero == TOP->Array) {
        nodoArray<T>* tmp = TOP;
        TOP = TOP->previous;
        puntero = TOP->Array + 4;
        delete tmp;
    }
    else {
        valor = NULL;
    }
    return valor;
}

template <class T>
bool PilanodoArray<T>::vacio() {
    return (TOP == nullptr);
}

template <class T>
void PilanodoArray<T>::print() {
    nodoArray<T>* current = TOP;
    while (current) {
        cout << "[";
        for (int i = 0; i < 5; i++) {
            cout << current->Array[i];
            if (i < 4) {
                cout << ";";
            }
        }
        cout << "]";
        if (current->previous) {
            cout << "->";
        }
        current = current->previous;
    }
    cout <<" -> NULL" << endl;
}

int main()
{
    PilanodoArray<int> p;

    for (int i = 0; i < 10; i++) {
        p.push(i);
    }

    p.print();

    while (!p.vacio()) {
        p.pop();
    }

    p.print();

    return 0;
}
