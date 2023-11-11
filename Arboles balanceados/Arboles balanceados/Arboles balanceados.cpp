#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

template <class T>
struct Node {
    Node* left, * right, * head;
    T val;

    Node(T v) {
        this->val = v;
        this->left = this->right = this->head = nullptr;
    }
};

template <class T>
struct ArbolBalanceado {
    Node<T>* root = nullptr;

    bool find(T v, Node<T>*& p) {
        p = root;
        bool confir = true;
        if (!root) return false;
        else {
            while (confir) {
                if (p->val == v) return true;
                if (p->val > v) {
                    if (p->left == NULL) { confir = false; }
                    else { p = p->left; }
                }
                if (p->val < v) {
                    if (p->right == NULL) { confir = false; }
                    else { p = p->right; }
                }
            }
        }
        return false;
    }

    int height(Node<T>* p) {
        if (p == nullptr) {
            return 0;
        }
        return 1 + max(height(p->left), height(p->right));
    }

    void leftRotate(Node<T>* x) {
        Node<T>* y = x->right;
        x->right = y->left;

        if (y->left != nullptr) {
            y->left->head = x;
        }

        y->head = x->head;
        if (x->head == nullptr) {
            root = y;
        }
        else if (x == x->head->left) {
            x->head->left = y;
        }
        else {
            x->head->right = y;
        }

        y->left = x;
        x->head = y;
    }

    void rightRotate(Node<T>* y) {
        Node<T>* x = y->left;
        y->left = x->right;

        if (x->right != nullptr) {
            x->right->head = y;
        }

        x->head = y->head;
        if (y->head == nullptr) {
            root = x;
        }
        else if (y == y->head->left) {
            y->head->left = x;
        }
        else {
            y->head->right = x;
        }

        x->right = y;
        y->head = x;
    }

    void Balanceo(Node<T>* q) {
        Node<T>* recorre = q;
        while (recorre != nullptr) {
            int balance = height(recorre->right) - height(recorre->left);

            if (balance == -2) {
                if (height(recorre->left->left) >= height(recorre->left->right)) {
                    rightRotate(recorre);
                }
                else {
                    leftRotate(recorre->left);
                    rightRotate(recorre);
                }
            }
            else if (balance == 2) {
                if (height(recorre->right->right) >= height(recorre->right->left)) {
                    leftRotate(recorre);
                }
                else {
                    rightRotate(recorre->right);
                    leftRotate(recorre);
                }
            }

            recorre = recorre->head;
        }
    }

    void add(T v) {
        Node<T>* puntero;
        if (!root) {
            root = new Node<T>(v);
            return;
        }
        if (!find(v, puntero)) {
            Node<T>* p = new Node<T>(v);
            if (puntero->val > v) puntero->left = p;
            if (puntero->val < v) puntero->right = p;
            p->head = puntero;
            Balanceo(p);
        }
    }

    void remove(T v) {
        Node<T>* puntero;
        if (!find(v, puntero)) {
            cout << "Value not found for removal." << endl;
            return;
        }

        if (puntero->left == nullptr && puntero->right == nullptr) {
            // Case 1: Node with no children
            if (puntero->head == nullptr) {
                // If it's the root
                delete puntero;
                root = nullptr;
            }
            else {
                Node<T>* parent = puntero->head;
                if (parent->left == puntero) {
                    parent->left = nullptr;
                }
                else {
                    parent->right = nullptr;
                }
                delete puntero;
                Balanceo(parent);
            }
        }
        else if (puntero->left == nullptr || puntero->right == nullptr) {
            // Case 2: Node with one child
            Node<T>* child = (puntero->left != nullptr) ? puntero->left : puntero->right;
            if (puntero->head == nullptr) {
                // If it's the root
                root = child;
                root->head = nullptr;
            }
            else {
                Node<T>* parent = puntero->head;
                if (parent->left == puntero) {
                    parent->left = child;
                }
                else {
                    parent->right = child;
                }
                child->head = parent;
                delete puntero;
                Balanceo(parent);
            }
        }
        else {
            // Case 3: Node with two children
            Node<T>* successor = puntero->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            puntero->val = successor->val;

            // Check if the successor has a right child
            if (successor->right != nullptr) {
                // Update the parent of the successor's right child
                successor->right->head = successor->head;
            }

            // Update the parent's link to the successor
            if (successor->head->left == successor) {
                successor->head->left = successor->right;
            }
            else {
                successor->head->right = successor->right;
            }

            Balanceo(successor->head);
            delete successor;
        }
    }

    void print(Node<T>* n) {
        if (!n) return;
        print(n->left);
        cout << n->val << ": ";
        if (n->left) cout << n->left->val << " ";
        if (n->right) cout << n->right->val;
        cout << endl;
        print(n->right);
    }

    void print() {
        print(root);
    }
};

int main() {
    ArbolBalanceado<int> arbol;

    vector<int> v1(101);

    /*for (int i = 0; i <= 100; i++) {
        int a = 1 + rand() % 100;
        v1[i] = a;
        arbol.add(a);
    }*/

    
    arbol.add(11);
    arbol.add(14);
    arbol.add(7);
    arbol.add(8);
    arbol.add(2);
    arbol.add(1);
    arbol.add(5);
    arbol.add(4);

    arbol.print();

    cout << "--------------------------" << endl;

    arbol.remove(11);

    arbol.print();

    cout << "La raiz es: " << arbol.root->val << endl;

    for (int i = 0; i < v1.size(); ++i)
        cout << v1[i] << " ; ";

    return 0;
}
