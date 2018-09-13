#include "../ListaQueueStack/List.cpp"
#include <iostream>
#include <string>

using namespace std;


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
        os << "Value: " << hd.value << "  ::  Pos: " << hd.pos;  
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

    for(int j = 0; j < M; j++)
    {
        for(int i = 0; i < Y; i++)
        {
            HashNode temp(0, toAnalyse[i]);
            cout << "temp is:" << toAnalyse[i] << endl;
            string msg = to_string(j) + ": ";
            newOffice->arr[i].SelectivePrint(temp, msg);
        }
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