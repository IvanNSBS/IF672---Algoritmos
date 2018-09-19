//#include "../ListaQueueStack/List.cpp"
#include <iostream>
#include <string>

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
    Node(){}
};

template <typename T>
class List{
public:
    Node<T>* head;
    Node<T>* last;
    int size;

private:
    void Stack_push(Node<T>* node, T key);
    void PrintTree(Node<T>* node);
    void SelectivePrint(Node<T>* node, T key, string msg);
    T Search(Node<T>* node, T key);

public:
    void Stack_push(T key);
    void Enqueue(T key);
    void Stack_pop();
    void Queue_pop();
    void PrintTree();
    void SelectivePrint(T key, string msg);
    T Search(T Key);


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
    size++;
    if(head == nullptr)
    {
        head = new Node<T>(key);
        head->next = nullptr;
        last = head;
        last->prev = nullptr;
        return;
    }
    Node<T>* newhead = new Node<T>(key);
    Node<T>* temp = head;
    temp->prev = newhead;
    head = newhead;
    head->next = temp;
    if(head->next == nullptr)
        last->prev = head;
}

template <class T>
void List<T>::Stack_push(T key)
{
    Stack_push(last, key);
}

template <class T>
void List<T>::Stack_push(Node<T> *node, T key)
{
    size++;
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
    else
        head = nullptr;
}

template <class T>
void List<T>::Stack_pop()
{
    if(last == head)
    {
        last = head = nullptr;
        return;
    }
    if(last->prev == head)
    {{
    PrintTree(head);
}
        last = head;
        last->prev = nullptr;
        return;  
    }
    Node<T>* temp = last->prev;
    delete last;
    last = temp;
    last->prev = temp->prev;
    last->next = nullptr;
}

template <class T>
T List<T>::Search(Node<T> *node, T key)
{
    if(node->next == nullptr)
    {
        if(node->key == key)
            return node->key;
        else
            return T();
    }
    else
    {
        if(node->key == key)
            return node->key;
        else
            return Search(node->next, key);
    }
}

template <class T>
T List<T>::Search(T key)
{
    Search(head, key);
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

template <class T>
void List<T>::SelectivePrint(T key, string msg)
{
    SelectivePrint(head, key, msg);
}

template <class T>
void List<T>::SelectivePrint(Node<T> *node, T key, string msg)
{
    if(node != nullptr)
    {
        if(node->key == key)
            cout << msg << node->key << endl;

        SelectivePrint(node->next, key, msg);
    }
    else
        return;
}



struct HashNode
{
    string value;
    int key;
    int pos;

    HashNode(const int &k, const string &val) : key(k), value(val), pos(-1) {}
    HashNode(const int &k, const string &val, const int &p) : key(k), value(val), pos(p) {}
    HashNode(){value = ""; key = -1; pos = -1;}

    friend bool operator==(const HashNode& lhs, const HashNode& rhs)
    {
        return lhs.value.compare(rhs.value) == 0;
    }

    friend std::ostream& operator<<(ostream& os, const HashNode& hd)  
    {  
        os << hd.pos;  
        return os;  
    } 
};

class HashTable
{
public: 

    List<HashNode> *arr;
    int capacity;

    int HashFunction(string value);
    void Insert(int key, string value);
    void Insert(HashNode newNode);
    HashNode BSearchNode(int key);
    HashNode FindProc(string val);
    //int Search(int key);

    HashTable(int capacity)
    {
        this->capacity = capacity;
        arr = new List<HashNode>[capacity];
    }
};

int HashTable::HashFunction(string value)
{
    int soma = 0;
    int i = 1;
    for(char &c : value)
    {
        soma += (int)c * i;
        i++;
    }

    return soma % capacity;
}

HashNode HashTable::BSearchNode(int key)
{
    int l = 0, r = capacity-1;
    while(l <= r)
    {
        int mid = l + (r - l)/2;
        if(arr[mid].head->key.key == key)
            return arr[mid].head->key;

        if(arr[mid].head->key.key < key)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return HashNode();
}

void HashTable::Insert(int key, string value)
{
    int index = HashFunction(value);
    if(index < capacity)
    {
        HashNode neo(key, value);
        arr[index].Enqueue(neo);
    }
}

void HashTable::Insert(HashNode newNode)
{
    int index = HashFunction(newNode.value);
    if(index < capacity)
    {
        //newNode.pos = arr[index].size;
        newNode.pos = arr[index].size +1 ;
        arr[index].Enqueue(newNode);
        //arr[index].last->key.pos = arr[index].size;
    }
}

HashNode HashTable::FindProc(string val)
{
    int index = HashFunction(val);
    HashNode temp(0, val);
    return arr[index].Search(temp);
}


int main()
{
    //A = quantidade de arquivos no escritório antigo
    int A;
    cin >> A;
    HashTable *oldArchives = new HashTable(A);
    //
    for(int i = 0; i < A; i++)
    {
        string val;
        cin >> val;
        int key;
        cin >> key;

        HashNode neo(key, val); 
        oldArchives->arr[i].Enqueue(neo);
    }

    //M = quantidade de gavetas do movel que armazenará
    //os arquivos no escritório novo
    int M;
    cin >> M;

    //X = ID's dos arquivos que serao transferidos
    int X;
    cin >> X;

    int *toTransfer = new int[X];
    for(int i = 0; i < X; i++)
    {
        int id;
        cin >> id;
        toTransfer[i] = id;
    }

    //quantida de arquivos
    //para serem consultados
    int Y;
    cin >> Y;

    string *toAnalyse = new string[Y];
    for(int i = 0; i < Y; i++)
    {
        string name;
        cin >> name;
        toAnalyse[i] = name;
    }

    //Passa os arquivos do escritorio antigo para o novo
    HashTable *newOffice = new HashTable(M);

    //encontrar os arquivos para serem transferidos
    //do escritorio antigo e pô-los no novo
    for(int i = 0; i < X; i++)
    {
        HashNode temp = oldArchives->BSearchNode(toTransfer[i]);
        if(temp.key != -1)
        {
            newOffice->Insert(temp);
        }
    }

    //Imprimir quantos arquivos existem em uma gaveta
    for(int i = 0; i < M; i++)
    {
        cout << i << ": " << newOffice->arr[i].size << endl;
    }

    for(int i = 0; i < Y; i++)
    {
        HashNode temp(0, toAnalyse[i]);
        //cout << "temp is:" << toAnalyse[i] << endl;
        int index = newOffice->HashFunction(toAnalyse[i]);
        string msg = to_string(i) + ": ";
        newOffice->arr[index].SelectivePrint(temp, msg);
    }
    //for(int i = 0; i < Y;i++)
    //{
    //    newOffice->arr[i].PrintTree();
    //}


    return 0;
}

/*
20
nmIvRceRaN 6
iZ1PEB5yhR 15
A6IlLkrP45 24
LUffVqJZUz 34
URcgeaMQRw 40
MUO679xYPI 44
zdk21sGTIS 54
ALKkgL3JIx 55
10ejR7i8Gy 64
nBuELnKGKd 68
YtWuHl5eDt 73
htyVEymuNz 82
lGDQoa0IkF 91
rtPEi9cNNi 99
X40kUY2lZj 104
DRw3n9xZEA 114
zN4lAW7eSG 119
bzKiHXseEG 122
PoutMvdy6e 129
4Woumssa6Y 136
4
10
40
82
104
55
24
114
122
6
15
129
5
ALKkgL3JIx
nmIvRceRaN
iZ1PEB5yhR
bzKiHXseEG
ALKkgL3JIx
*/