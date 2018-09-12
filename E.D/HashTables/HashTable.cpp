#include "../ListaQueueStack/List.cpp"
using namespace std;

template <typename K, typename V>
class HashNode
{
public: 
    V value;
    K key;

    HashNode(K key, V value)
    {
        this.key = key;
        this.value = value;
    }
};

template <typename K, typename V>
class CHashTable
{
public: 

    List<HashNode<K,V>> *arr;
    int capacity;
    int currSize;

    virtual int HashFunction(K key);
    void Insert(K key, V value);
    V Search(int key);

    CHashTable(int capacity)
    {
        this->capacity = capacity;
        arr = new List<HashNode<K,V>>[capacity];
        currSize = 0;
    }
};

template <typename K, typename V>
void CHashTable<K, V>::Insert(K key, V value)
{
    HashNode<K,V> *temp = new HashNode<K,V>(key, value);
    // Apply hash function to find index for given key
    int hashIndex = hashCode(key);
    if(arr[hashIndex] == nullptr)
    {
        arr[hashIndex] = *temp;
        return;
    }
    arr[hashIndex].Enqueue(temp);    
}

/*template <typename K, typename V>
V CHashTable<K, V>::Search(int key)
{
    int hashIndex = HashFunction(K);
    //finding the node with given key   
    while(arr[hashIndex] != nullptr)
    {
        //if node found return its value
        if(arr[hashIndex]->key == key)
            return arr[hashIndex]->value;
        hashIndex++;
        hashIndex %= capacity;
    }
    //If not found return null
    return nullptr;
}*/

