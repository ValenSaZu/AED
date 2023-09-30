#include <iostream>

using namespace std;

template <class T>
struct nodoArray {
    T Array[5];
    nodoArray<T>* next;
    nodoArray(nodoArray<T>* n = NULL) {
        next = n;
    }
};

template <class T>
struct ColanodoArray {
    nodoArray<T>* HEAD;
    nodoArray<T>* TAIL;
    T* punteroPOP;
    T* puntero;
    T pop();
    void push(T v);
    bool vacio();
    void print();

    ColanodoArray() : HEAD(nullptr), TAIL(nullptr), puntero(nullptr), punteroPOP(nullptr) {}
};

template <class T>
void ColanodoArray<T>::push(T v) {
    if (!HEAD) {
        HEAD = new nodoArray<T>(nullptr);
        TAIL = HEAD;
        punteroPOP = HEAD->Array;
        puntero = HEAD->Array;
        *puntero = v;
    }
    else if (puntero == HEAD->Array + 4) {
        nodoArray<T>* NewNodo = new nodoArray<T>(nullptr);
        TAIL->next = NewNodo;
        TAIL = NewNodo;
        puntero = TAIL->Array;
        *puntero = v;
    }
    else {
        puntero++;
        *puntero = v;
    }
}

template <class T>
T ColanodoArray<T>::pop() {
    T valor = *punteroPOP;
    if (punteroPOP == HEAD->Array + 4) {
        nodoArray<T>* tmp = HEAD;
        HEAD = HEAD->next;
        punteroPOP = HEAD ? HEAD->Array : nullptr;
        delete tmp;
    }
    else if (HEAD == TAIL && punteroPOP == HEAD->Array + 4) {
        nodoArray<T>* tmp = HEAD;
        HEAD = nullptr;
        TAIL = nullptr;
        puntero = nullptr;
        punteroPOP = nullptr;
        delete tmp;
    }
    else if (!HEAD) {
        valor = NULL;
    }
    else {
        punteroPOP++;
    }
    return valor;
}

template <class T>
bool ColanodoArray<T>::vacio() {
    return (HEAD == nullptr);
}

template <class T>
void ColanodoArray<T>::print() {
    nodoArray<T>* current = HEAD;
    while (current) {
        cout << "[";
        for (int i = 0; i < 5; i++) {
            cout << current->Array[i];
            if (i < 4) {
                cout << ";";
            }
        }
        cout << "]";
        if (current->next) {
            cout << "->";
        }
        current = current->next;
    }
    cout << "->NULL" << endl;
}

int main() {
    ColanodoArray<int> p;

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