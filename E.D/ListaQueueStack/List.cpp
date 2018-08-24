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
    Node()
    {
        
    }
};

template <typename T>
class List{
public:
    Node<T>* head;
    Node<T>* last;

private:
    void Stack_push(Node<T>* node, T key);
    void PrintTree(Node<T>* node);

public:
    void Stack_push(T key);
    void Enqueue(T key);
    void Stack_pop();
    void Queue_pop();
    void PrintTree();


    //List(T key);
    //List();
};

/*template <class T>
List<T>::List(T key)
{
    head = new Node<T>(key);
    last = head;
    last->prev = head;
}

template <class T>
List<T>::List()
{
    head = nullptr;
    last = head;
    last->prev = head;
}*/

template <class T>
void List<T>::Enqueue(T key)
{
    if(head == nullptr)
    {
        head = new Node<T>(key);
        last = head;
        last->prev = head;
        return;
    }
    Node<T>* newhead = new Node<T>(key);
    Node<T>* temp = head;
    head = newhead;
    head->next = temp;
}

template <class T>
void List<T>::Stack_push(T key)
{
    Stack_push(last, key);
}

template <class T>
void List<T>::Stack_push(Node<T> *node, T key)
{
    if(head == nullptr)
    {
        head = new Node<T>(key);
        last = head;
        last->prev = head;
        return;
    }
    Node<T>* temp = new Node<T>(key);
    Node<T>* prev = last;
    last->next = temp;
    last = last->next;
    last->prev = prev;
}

template <class T>
void List<T>::Queue_pop()
{
    Node<T>* temp = head->next;
    delete head;
    head = temp;
    if(temp != nullptr)
        head->next = temp->next;
    //else
     //   cout << "Lista Vazia" << endl;
    //while(true){}
}

template <class T>
void List<T>::Stack_pop()
{
    if(last->prev == head)
    {
        last == nullptr;
        return;  
    }
    Node<T>* temp = last->prev;
    delete last;
    last = temp;
    last->prev = temp->prev;
    last->next = nullptr;
}

template <class T>
void List<T>::PrintTree()
{
    PrintTree(head);
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