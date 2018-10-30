#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int global = 0;

struct Data
{
    int M;
    int l, r, RMQ;
    //int
    Data(): l(0), r(0), M(999999), RMQ(999999){}
    Data(const int &vl, const int &vr) : l(vl), r(vr), M((vl+vr)/2), RMQ(999999){}
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

    //Ã© menor se a direita for = m-1, Ã© maior se a esquerda for = m+1
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


int GetMin(int a, int b)
{
    if( a < b )
        return a;
    else
        return b;
}

int GetMax(int a, int b)
{
    if( a > b )
        return a;
    else
        return b;
}

class Node
{
public:
    Data key;
    Node* left;
    Node* right;
    Node(Data key)
    {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(){}
};


class BTree
{
public:
    Node* root;
public:
    void CreateST(Node* node, int l, int r, int arr[] );
    int FindRMQ(Node* data, int l, int r);
    void UpdateTree(Node* node, int a, int arr[]);
    void PRT(Node* node, Data root, int l, int r);

public:
    void CreateST(int size, int arr[]);
    void UpdateTree(int arr[], int a);
    int FindRMQ(int l, int r);
    void PRT(Data rt, int l, int r);

};


void BTree::CreateST(Node *node, int l, int r, int arr[])
{
    if( node->key.l == node->key.r )
        return;

    int m = (l+r)/2;
    node->left = new Node( Data( l, m, GetRMQ(arr, l, m) ) );
    node->right = new Node( Data( m+1, r, GetRMQ(arr, m+1, r) ) );
    CreateST(node->left, l, m, arr);
    CreateST(node->right, m+1, r, arr);
}


void BTree::CreateST(int size, int arr[])
{
    root = new Node ( Data (0, size-1, GetRMQ(arr, 0, size-1) ) );
    CreateST(root, 0, size-1, arr);
}


int BTree::FindRMQ(Node *data, int l, int r)
{
    if(data == nullptr)
    {
        cout << "asdkosadko" << endl;
        return 99999;
    }

    if( l > r || l > data->key.r || r < data->key.l)
    {
        global = INT_MAX;
        return INT_MAX;
    }

    if(l == data->key.l && r == data->key.r)
    {
        global = data->key.RMQ;
        return data->key.RMQ;
    }

    //cout << "RMQ IS: " << data->key.RMQ << endl;
    
    int a = GetMin( FindRMQ( data->left, GetMax(l, data->key.l), GetMin(r, data->key.M) ), FindRMQ( data->right, GetMax(l, data->key.M+1), GetMin(r, data->key.r) ) );
    global = a;
    //cout << "A is: " << a << endl;
    return a;
}

int BTree::FindRMQ(int l, int r)
{
    FindRMQ(root, l, r);
}


void BTree::UpdateTree(Node *node, int a, int arr[])
{
    if(node == nullptr)
        return;

    if( a >= node->key.l && a <= node->key.r )
    {
        //cout << "Passei pelo nó " << node->key << endl;
        node->key.RMQ = GetRMQ(arr, node->key.l, node->key.r);

        if( (a <= node->key.M) )
            UpdateTree(node->left, a, arr);

        if( (a >= node->key.M + 1) )
            UpdateTree(node->right, a, arr);
    }    
}

void BTree::UpdateTree(int arr[], int a)
{
    UpdateTree(root, a, arr);
}


void BTree::PRT(Node *node, Data root, int a, int b) 
{
    if( node->key.l != node->key.r)
    {
        if( !(node->left->key.r < a) )
            PRT( node->left, root, max(a, node->key.l), min(b, node->key.M) );

        if( !(node->right->key.l > b) )    
            PRT( node->right, root, max(a, node->key.M+1), min(b, node->key.r) );
    }

    if( !(node->key == root) )
        cout << node->key.RMQ << " ";
    else
        cout << node->key.RMQ;
}


void BTree::PRT(Data rt, int l, int r)
{
    PRT(root, rt, l, r);
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

    //Ã¡rvore com os xesq
    BTree *tree = new BTree();
    tree->CreateST(N, arr);

    std::string tst;
    do
    {
        cin >> tst;
        if(tst == "END")
            break;

        if(tst == "RMQ")
        {
            int a,b;
            cin >> a;
            cin >> b;
            int aux = tree->FindRMQ(a ,b);
            cout << tree->FindRMQ(a ,b) << endl; 
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
            tree->PRT(tree->root->key, a, b);
            cout << endl;
        }

    }while(tst != "END");
}