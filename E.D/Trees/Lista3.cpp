#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

struct Data
{
    int M;
    int l, r, RMQ;
    //int 
    Data(): l(0), r(0), M(0), RMQ(9999999){}
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
    void CreateST(Node<Data>* node, int l, int r, int arr[] );
    int FindRMQ(Node<Data>* data, int l, int r);
    void UpdateTree(Node<Data>* node, int a, int arr[]);
    void PRT(Node<Data>* node, int l, int r);

public:
    void CreateST(int size, int arr[]);
    void UpdateTree(int arr[], int a);
    int FindRMQ(int l, int r);
    void PRT(int l, int r);

};

template<class T>
void BTree<T>::CreateST(Node<Data> *node, int l, int r, int arr[])
{
    if( node->key.l == node->key.r )
        return;
    
    int m = (l+r)/2;
    node->left = new Node<Data>( Data( l, m, GetRMQ(arr, l, m) ) );
    cout << "Left is: " << node->left->key << endl;
    node->right = new Node<Data>( Data( m+1, r, GetRMQ(arr, m+1, r) ) );
    cout << "Right is: " << node->right->key << endl;
    CreateST(node->left, l, m, arr);
    CreateST(node->right, m+1, r, arr);
}

template <class T>
void BTree<T>::CreateST(int size, int arr[])
{
    root = new Node<Data> ( Data (0, size-1, GetRMQ(arr, 0, size-1) ) );
    cout << "Root is: " << root->key << endl;
    CreateST(root, 0, size-1, arr);
}

template<class T>
int BTree<T>::FindRMQ(Node<Data> *data, int l, int r)
{
    if( data == nullptr ) 
        return -1;

    if( l > r || l > data->key.r || r < data->key.l)
    {
        //cout << "+infinity" << endl;
        return 99999;
    }
    
    if(l == data->key.l && r == data->key.r)
        return data->key.RMQ;

    cout << "left is: " << data->left->key << endl;
    cout << "Right is: " << data->right->key << endl;
    return min( FindRMQ( data->left, max(l, data->key.l), min(r, data->key.M) ), FindRMQ( data->right, max(l, data->key.M+1), min(r, data->key.r) ) );
}

template<class T>
int BTree<T>::FindRMQ(int l, int r)
{
    FindRMQ(root, l, r);
}

template<class T>
void BTree<T>::UpdateTree(Node<Data> *node, int a, int arr[])
{
    if(node == nullptr)
        return;

    if(!(a >= node->key.l && a <= node->key.r))
        return;
    
    node->key.RMQ = GetRMQ(arr, node->key.l, node->key.r);
    UpdateTree(node->left, a, arr);
    UpdateTree(node->right, a, arr);
}

template<class T>
void BTree<T>::UpdateTree(int arr[], int a)
{
    UpdateTree(root, a, arr);
}

template<class T>
void BTree<T>::PRT(Node<Data> *node, int a, int b)
{
    /*if(( l > r || l > node->key.r || r < node->key.l))
        return;

    if(l == node->key.l && r == node->key.r)
    {
        cout << node->key << endl;
        return;
    }*/
    if( node == nullptr)
        return;

    PRT( node->left, max(a, node->key.l), min(b, node->key.M) );
    PRT( node->right, max(a, node->key.M+1), min(b, node->key.r) );
    if(!(b < node->key.l || a > node->key.r))
        cout << node->key.RMQ << " ";
}

template<class T>
void BTree<T>::PRT(int l, int r)
{
    PRT(root, l, r);
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
            int a, b;
            cin >> a;
            cin >> b;
            arr[a] = b;
            tree->UpdateTree(arr, a);
        }
        else if(tst == "PRT")
        {
            int a, b;
            cin >> a;
            cin >> b;
            tree->PRT(a,b);
            cout << endl;
        }
    }while(tst != "END");
}