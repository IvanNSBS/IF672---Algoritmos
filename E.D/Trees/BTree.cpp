#include <iostream>
using namespace std;

template <class T>
class Node 
{
public:
    T key;
    Node* left;
    Node* right;
    Node(T key)
    {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(){}
};

template <class T>
class BTree 
{
public: 
    Node<T>* root;
private:
    void Add(Node<T> *node, T key);
    Node<T>* Find(Node<T> *node, T key);
    void PostOrder(Node<T> *node);
    void InOrder(Node<T> *node);
    void PreOrder(Node<T> *node);
public:
    //BTree(T key){ root = new Node<T>(key);}
    //BTree();
    void Add(T key);
    Node<T>* Find(T key);
    void PostOrder();
    void InOrder();
    void PreOrder();
};

template <class T>
void BTree<T>::Add(Node<T> *node, T key)
{
    /*if(node == nullptr)
    {
        node = new Node<T>(key);
        return;
    }*/

    if(key > node->key)
    {
        if(node->right == nullptr)
            node->right = new Node<T>(key);
        else
            Add(node->right, key);
    }
    else
    {
        if(node->left == nullptr)
            node->left = new Node<T>(key);
        else
            Add(node->left, key);
    }
}

template <class T>
void BTree<T>::Add(T key)
{
    if(root == nullptr)
        root = new Node<T>(key);
    else    
        Add(root, key);
}

template <class T>
Node<T>* BTree<T>::Find(Node<T> *node, T key)
{
    if(node->key == key)
        return node;

    if(key > node->key)
    {
        if(node->right != nullptr)
            Find(node->right, key);
        else
            return nullptr;
    }
    else
    {
        if(node->left != nullptr)
            Find(node->left, key);
        else
            return nullptr;
    }
}

template <class T>
Node<T>* BTree<T>::Find(T key)
{
    Find(root, key);
}

template <class T>
void BTree<T>::PreOrder(Node<T> *node)
{
    if(node == nullptr)
        return;

    cout << node->key << endl;
    PreOrder(node->left);
    PreOrder(node->right);
}

template <class T>
void BTree<T>::PreOrder()
{
    PreOrder(root);
}

template <class T>
void BTree<T>::InOrder(Node<T> *node)
{
    if(node == nullptr)
        return;

    InOrder(node->left);
    cout << node->key << endl;
    InOrder(node->right);
}

template <class T>
void BTree<T>::InOrder()
{
    InOrder(root);
}

template <class T>
void BTree<T>::PostOrder(Node<T> *node)
{
    if(node == nullptr)
        return;

    PostOrder(node->left);
    PostOrder(node->right);
    cout << node->key << endl;
}

template <class T>
void BTree<T>::PostOrder()
{
    PostOrder(root);
}