#include <iostream>
using namespace std;

template <class T>
class Node {
public:
    T key;
    Node* next;
    Node* prev;
    Node(T key)
    {
        this->key = key;
        this->next = nullptr;
    }
};

template <typename T>
class List{
public:
    Node<T>* root;
    Node<T>* last;

private:
    void AddNode(Node<T>* node, T key);
    void PrintTree(Node<T>* node);

public:
    void AddNode(T key);
    void AddToHead(T key);
    void RemoveLast();
    void RemoveFirst();
    void PrintTree();


    List(T key);
};

template <class T>
List<T>::List(T key)
{
    root = new Node<T>(key);
    last = root;
    last->prev = root;
}

template <class T>
void List<T>::AddToHead(T key)
{
    if(root == nullptr)
    {
        root = new Node<T>(key);
        last = root;
        last->prev = root;
        return;
    }
    Node<T>* newhead = new Node<T>(key);
    Node<T>* temp = root;
    root = newhead;
    root->next = temp;
}

template <class T>
void List<T>::AddNode(T key)
{
    AddNode(last, key);
}

template <class T>
void List<T>::AddNode(Node<T> *node, T key)
{
    if(root == nullptr)
    {
        root = new Node<T>(key);
        last = root;
        last->prev = root;
        return;
    }
    Node<T>* temp = new Node<T>(key);
    Node<T>* prev = last;
    last->next = temp;
    last = last->next;
    last->prev = prev;
}

template <class T>
void List<T>::RemoveFirst()
{
    Node<T>* temp = root->next;
    root = temp;
    root->next = temp->next;
}

template <class T>
void List<T>::RemoveLast()
{
    if(last->prev == root)
    {
        last == nullptr;
        return;  
    }
    Node<T>* temp = last->prev;
    last = temp;
    last->prev = temp->prev;
    last->next = nullptr;
}

template <class T>
void List<T>::PrintTree()
{
    PrintTree(root);
}

template <class T>
void List<T>::PrintTree(Node<T> *node)
{
    if(node != nullptr)
    {
        cout << node->key << endl;
        PrintTree(node->next);
    }
    else
        return;
}

int main()
{
    List<int>* t = new List<int>(0);
    for(int i = 1; i < 6; i++)
        t->AddNode(i);
    t->PrintTree();
    t->RemoveFirst();
    t->RemoveFirst();
    t->RemoveFirst();
    cout << "removing first 3" << endl;
    t->PrintTree();
    cout << "adding first 3 again" << endl;
    t->AddToHead(2);
    t->AddToHead(1);
    t->AddToHead(0);
    t->PrintTree();
    t->AddNode(7);
    t->AddNode(8);
    cout << "adding 7 and 8 to end" << endl;
    t->PrintTree();
    t->RemoveLast();
    t->RemoveLast();
    cout << "removing last 2 el's" << endl;
    t->PrintTree();
    t->RemoveFirst();
    t->RemoveFirst();
    t->RemoveFirst();
    cout << "removing first 3" << endl;
    t->PrintTree();
    cout << "adding first 3 again" << endl;
    t->AddToHead(2);
    t->AddToHead(1);
    t->AddToHead(0);
    t->PrintTree();
    t->AddNode(7);
    t->AddNode(8);
    cout << "adding 7 and 8 to end" << endl;
    t->PrintTree();
    return 0;
}