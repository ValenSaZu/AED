#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    CBinNode* m_root;
    bool m_b;
    int remove;
};

CBinTree::CBinTree()
{
    m_root = 0;
    m_b = 0;
}

CBinTree::~CBinTree()
{
    // ?
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return 0;
}
bool CBinTree::Remove(int x)
{
    CBinNode** p;
    if (!Find(x, p)) return 0;
    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinNode* t = *p;
    remove = (*p)->value;
    *p = (*p)->nodes[(*p)->nodes[0] == 0];
    delete t;
    return 1;
}

CBinNode** CBinTree::Rep(CBinNode** q)
{
    m_b = !m_b;
    q = &((*q)->nodes[!m_b]);
    while ((*q)->nodes[m_b])
        q = &((*q)->nodes[m_b]);
    return q;
}

void CBinTree::InOrder(CBinNode* n)
{
    if (!n) return;
    InOrder(n->nodes[1]);
    cout << n->value << " ";
}

void CBinTree::Print()
{
    InOrder(m_root);
    cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

class MaxHeap {
public:
    bool insert(int x);
    int remove(int x);
    int top();
    CBinTree Arbol;
};

bool MaxHeap::insert(int x) {
    return Arbol.Insert(x);
}

int MaxHeap::remove() {
    Arbol.Remove(Arbol.Find(top()));
    return Arbol.remove;
}

int MaxHeap::top() {
    int maximo;
    CBinNode* siguiente;
    for (CBinNode* p = Arbol.m_root; p; p = siguiente) {
        maximo = p->value;
        if (p->nodes[0]->value > p->nodes[1]->value) {
            siguiente = p->nodes[0];
        }
        else if (p->nodes[0]->value < p->nodes[1]->value) {
            siguiente = p->nodes[1];
        }
        else {
            return maximo;
        }
    }
}

int main()
{
    MaxHeap t;
    t.push(50); t.push(30); t.push(60);
    t.push(80); t.push(55); t.push(11);
    t.push(33); t.push(5); t.push(14);
    t.push(31); t.push(48);

    cout << t.top(); t.remove();
    cout << t.top(); t.remove();
    cout << t.top(); t.remove();
    cout << t.top(); t.remove();
    t.print();
}
