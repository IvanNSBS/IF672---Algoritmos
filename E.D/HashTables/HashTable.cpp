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
class HashTable
{
public: 
    HashNode<K,V> **arr;
    int capacity;
    int currSize;

    virtual int HashFunction(K key);
    void Insert(K key, V value);
    V Delete(int key);
    V Search(int key);

    HashTable(int capacity)
    {
        this.capacity = capacity;
        currSize = 0;

        for(int i = 0; i < capacity; i++)
            arr[i] = nullptr;
    }
}

template <typename K, typename V>
V HashTable::Search(int key)
{
    int hashIndex = hashCode(key);
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
}

template <typename K, typename V>
V HashTable::Insert(K key, V value)
{
    HashNode<K,V> *temp = new HashNode<K,V>(key, value);
    // Apply hash function to find index for given key
    int hashIndex = hashCode(key);
      
    //find next free space 
    while(arr[hashIndex] != nullptr && arr[hashIndex]->key != key && arr[hashIndex]->key != -1)
    {
        hashIndex++;
        hashIndex %= capacity;
    }    
    //if new node to be inserted increase the current size
    if(arr[hashIndex] == nullptr || arr[hashIndex]->key == -1)
        size++;
    arr[hashIndex] = temp;
}

