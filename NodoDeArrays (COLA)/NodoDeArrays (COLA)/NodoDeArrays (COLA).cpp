#include <iostream>

using namespace std;

template <class T>
struct nodoArray {
    T Array[5];
    int size = 0;
    nodoArray<T>* next;
    nodoArray(nodoArray<T>* n = nullptr) {
        next = n;
    }

    bool push(T valor) {
        if (size == 5) {
            return false;
        }
        else {
            Array[size] = valor;
            size++;
            return true;
        }
    }

    bool pop(T& valor) {
        if (size == 0) {
            return false;
        }
        else {
            size--;
            valor = Array[size];
            return true;
        }
    }

    void print() {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << Array[i];
            if (i < size - 1)
                cout << "->";
        }
        cout << "]";
    }
};

template <class T>
struct ColaNodoArray {
    nodoArray<T>* HEAD = nullptr;
    nodoArray<T>* TAIL = nullptr;

    void CPush(T valor) {
        if (TAIL == nullptr || TAIL->size == 5) {
            nodoArray<T>* newElement = new nodoArray<T>(nullptr);
            newElement->push(valor);

            if (HEAD == nullptr) {
                HEAD = TAIL = newElement;
            }
            else {
                TAIL->next = newElement;
                TAIL = newElement;
            }
        }
        else {
            TAIL->push(valor);
        }
    }

    bool CPop(T& valor) {
        if (HEAD == nullptr) {
            return false;
        }

        if (HEAD->pop(valor)) {
            if (HEAD->size == 0) {
                nodoArray<T>* tmp = HEAD;
                HEAD = HEAD->next;
                delete tmp;
            }
            return true;
        }

        return false;
    }

    void Cprint() {
        for (nodoArray<T>* i = HEAD; i != nullptr; i = i->next) {
            i->print();
            cout << " -> ";
        }
        cout << "NULL" << endl;
    }
};

int main() {
    ColaNodoArray<int> p;
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
