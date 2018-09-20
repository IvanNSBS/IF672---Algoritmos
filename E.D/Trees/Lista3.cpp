#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

struct Data
{
    int M;
    int l, r, RMQ;
    //int 
    Data(): l(0), r(0), M((l+r)/2){}
    Data(const int &vl, const int &vr) : l(vl), r(vr), M((vl+vr)/2){}
    Data(const int &vl, const int &vr, const int &vRMQ) : l(vl), r(vr), M((vl+vr)/2), RMQ(vRMQ){}

    friend std::ostream& operator<<(ostream& os, const Data& dd)  
    {  
        os << "[ " << dd.l << " , " << dd.r << " , " << dd.RMQ <<  " ]" << endl;  
        return os;  
    } 

    friend bool operator==(const Data& lhs, const Data& rhs)
    {
        return lhs.r == rhs.r && lhs.l == rhs.l;
    }

    //é menor se a direita for = m-1, é maior se a esquerda for = m+1
    friend bool operator<(const Data& lhs, const Data& rhs)
    {
        return lhs.r < rhs.M;
    }

    friend bool operator>(const Data& lhs, const Data& rhs)
    {
        return lhs.l > rhs.M;
    }

    friend bool operator<=(const Data& lhs, const Data& rhs)
    {
        return lhs.r <= rhs.M;
    }

    friend bool operator>=(const Data& lhs, const Data& rhs)
    {
        return lhs.l >= rhs.M;
    }
};

int GetRMQ(int arr[], int l, int r)
{
    int min = std::numeric_limits<int>::max();
    for(int i = l; i <= r; i++)
        if(min > arr[i])
            min = arr[i];

    return min;
}

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
    void CreateST(Node<Data>* node, int l, int r, int arr[] );
    int FindRMQ(Node<Data>* data, int l, int r);

    void DeleteTree(Node<T>* node);

    void PostOrder(Node<T> *node);
    void InOrder(Node<T> *node);
    void PreOrder(Node<T> *node);
public:
    //BTree(T key){ root = new Node<T>(key);}
    //BTree();
    //~Btree();
    void Add(T key);
    void CreateST(int size, int arr[]);
    Node<T>* Find(T key);

    void DeleteTree();

    int FindRMQ(int l, int r);

    void PostOrder();
    void InOrder();
    void PreOrder();
};

template <class T>
void BTree<T>::Add(Node<T> *node, T key)
{
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

template<class T>
void BTree<T>::CreateST(Node<Data> *node, int l, int r, int arr[])
{
    if( node->key.l == node->key.r )
        return;
    
    int m = (l+r)/2;
    node->left = new Node<Data>( Data( l, m, GetRMQ(arr, l, m) ) );
    node->right = new Node<Data>( Data( m+1, r, GetRMQ(arr, m+1, r) ) );
    CreateST(node->left, l, m, arr);
    CreateST(node->right, m+1, r, arr);
}

template <class T>
void BTree<T>::CreateST(int size, int arr[])
{
    root = new Node<Data> ( Data (0, size-1, GetRMQ(arr, 0, size-1) ) );
    CreateST(root, 0, size-1, arr);
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

template<class T>
int BTree<T>::FindRMQ(Node<Data> *data, int l, int r)
{
    if( l > r || l > data->key.r || r < data->key.l)
    {
        //cout << "+infinity" << endl;
        return std::numeric_limits<int>::max();
    }
    if(l == data->key.l && r == data->key.r)
        return data->key.RMQ;

    return min( FindRMQ( data->left, max(l, data->key.l), min(r, data->key.M) ), FindRMQ( data->right, max(l, data->key.M+1), min(r, data->key.r) ) );
}

template<class T>
int BTree<T>::FindRMQ(int l, int r)
{
    FindRMQ(root, l, r);
}

template<class T>
void BTree<T>::DeleteTree(Node<T> *node)
{
    if(node == nullptr)
        return;
    
    DeleteTree(node->left);
    DeleteTree(node->right);
    node == nullptr;
    delete node;
}

template<class T>
void BTree<T>::DeleteTree()
{
    DeleteTree(root);
}

int main()
{   
    //tamanho do array
    int N;
    cin >> N;

    //O array com os valores do conjunto
    int arr[N];
    for(int i = 0; i < N; i++)
    {
        int r;
        cin >> r;
        arr[i] = r;
    }

    //árvore com os xesq
    BTree<Data> *tree = new BTree<Data>();
    tree->CreateST(N, arr);

    std::string tst;
    do
    {
        cin >> tst;

        if(tst == "END")
            break;

        if(tst == "RMQ")
        {
            int a;
            int b;
            cin >> a;
            cin >> b;

            cout << tree->FindRMQ(a,b) << endl;
        }
        else if(tst == "UPD")
        {
            int a;
            int b;
            cin >> a;
            cin >> b;
            arr[a] = b;
            tree->DeleteTree();
            tree->CreateST(N, arr);
        }

    }while(tst != "END");
}