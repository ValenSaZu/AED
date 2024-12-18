#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

using namespace std;

struct MaxHeap {
    vector<int> vector;

    bool find(int v, int* p) {
        for (p = &vector[0]; p <= &(vector[vector.size() - 1]); p++) {
            if (*p == v) {
                return true;
            }
            if (*p < v) {
                return false;
            }
        }
        return false;
    }

    void push(int v) {
        if (vector.empty()) {
            vector.push_back(v);
        }
        else {
            int* p = NULL;
            if (!find(v, p)) {
                vector.push_back(v);
                for (int i = vector.size() - 1; i > 0 && vector[i] > vector[(i - 1) / 2]; i = (i - 1) / 2) {
                    swap(vector[i], vector[(i - 1) / 2]);
                }
            }
        }
    }

    int pop() {
        if (vector.empty()) {
            cerr << "El heap est� vac�o." << endl;
            return -1;
        }

        int v = vector[0];
        vector[0] = vector.back();
        vector.pop_back();

        int i = 0;
        while (2 * i + 1 < vector.size()) {
            int leftChild = 2 * i + 1;
            int rightChild = 2 * i + 2;
            int maxChild = leftChild;

            if (rightChild < vector.size() && vector[rightChild] > vector[leftChild]) {
                maxChild = rightChild;
            }

            if (vector[i] < vector[maxChild]) {
                swap(vector[i], vector[maxChild]);
                i = maxChild;
            }
            else {
                break;
            }
        }

        return v;
    }

    void print() {
        while (true) {
            for (int p = 0; p < vector.size(); p++) {
                cout << vector[p];

                int leftChild = 2 * p + 1;
                int rightChild = 2 * p + 2;

                if (leftChild < vector.size()) {
                    cout << " IZQUIERDA = " << vector[leftChild];
                }
                if (rightChild < vector.size()) {
                    cout << " DERECHA = " << vector[rightChild];
                }

                cout << endl;
            }
            cout << endl;
            this_thread::sleep_for(2500ms);
        }
    }

    void AutomaticPush() {
        while (true) {
            push(rand()%1000);
            this_thread::sleep_for(2000ms);
        }
    }
};

int main() {

    MaxHeap H;

    thread t1(&MaxHeap::AutomaticPush, &H);
    thread t2(&MaxHeap::print, &H);

    t1.join();
    t2.join();

    return 0;
}