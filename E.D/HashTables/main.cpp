#include "../ListaQueueStack/List.cpp"
#include <iostream>
#include <string>

using namespace std;


struct HashNode
{
    string value;
    int key;

    HashNode(const int &k, const string &val) : key(k), value(val) {}
    HashNode(){value = ""; key = -1;}
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
    int FindProcPos(string val);
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
        arr[index].Enqueue(newNode);
    }
}

int HashTable::FindProcPos(string val)
{
    int index = HashFunction(val);
    Node *temp = arr[val].head;

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



    return 0;
}