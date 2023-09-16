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
    bool push(T valor);
    bool pop();
    void print();
};

template <class T>
bool nodoArray<T>::push(T valor) {
    if (puntero == Array + 5) {
        return false;
    }
    else {
        *puntero = valor;
        puntero++;
        return true;
    }
}

template <class T>
bool nodoArray<T>::pop() {
    if (puntero == Array) {
        return false;
    }
    else {
        puntero--;
        return true;
    }
}

template <class T>
void nodoArray<T>::print() {
    cout << "[";
    for (T* i = Array; i < puntero; i++) {
        if (i != puntero - 1)
            cout << *i << "->";
        else
            cout << *i;
    }
    cout << "]";
}

template <class T>
struct ColaNodoArray {
    nodoArray<T>* elemento = new nodoArray<T>(NULL);
    void CPush(T valor);
    bool CPop();
    void Cprint();
};

template<class T>
void ColaNodoArray<T>::CPush(T valor) {
    if (!elemento->push(valor)) {
        nodoArray<T>* newElement = new nodoArray<T>(elemento);
        newElement->push(valor);
        elemento = newElement;
    }
}

template<class T>
bool ColaNodoArray<T>::CPop() {
    if (!elemento->pop()) {
        if (elemento->previous != NULL) {
            nodoArray<T>* tmp = elemento;
            elemento = elemento->previous;
            delete tmp;
            return true;
        }
        else {
            elemento->puntero = elemento->Array;
            return false;
        }
    }
}

template<class T>
void ColaNodoArray<T>::Cprint() {
    for (nodoArray<T>* i = elemento; i != NULL; i = i->previous) {
        i->print();
        cout << "-> ";
    }
    cout << "NULL" << endl;
}

int main() {
    ColaNodoArray<int> p;
    for (int i = 0; i < 50; i++) {
        p.CPush(i);
    }
    p.Cprint();

    while (p.CPop());

    p.Cprint();

    return 0;
}
