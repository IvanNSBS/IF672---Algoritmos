#include <iostream>
using namespace std;

template <class T>
class Node 
{
public:
    T key;
    Node* left;
    Node* right
    Node(T key)
    {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <class T>
class BTree 
{
public: 
    Node<T>* root;
private:
    void Add(Node<T> node, T key);
    void Find(Node<T> node, T key);
public:
    Tree(T key);
    void Add(T key);
    void Find(T key);
    void PostOrder();
    void InOrder();
    void InOrder();
}

template <class T>
void Tree::Add(T key)
{

}

void Tree::Add(T key)
{

}