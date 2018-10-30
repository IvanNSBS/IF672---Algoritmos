#include <iostream>
#include <vector>
#include <climits>
#include <string>

using namespace std;

struct Paciente;
class Heap;
enum HeapType {Max, Min};
const HeapType TMax = HeapType::Max;
const HeapType TMin = HeapType::Min;
void swap(Paciente *x, Paciente *y); 
int FindNext(vector<Heap> &list);

struct Paciente
{
    int idade, urgencia, servico, chegada;

    Paciente() : idade(-1), urgencia(-1), servico(-1) {}
    Paciente(const int &i, const int &u, const int &s): idade(i), urgencia(u), servico(s) {}
    Paciente(const int &i, const int &u, const int &s, const int &c): idade(i), urgencia(u), servico(s), chegada(c) {}

    friend std::ostream& operator<<(std::ostream& os, const Paciente& pp)  
    {  
        os << pp.servico << " " << pp.idade << " " << pp.urgencia << std::endl;  
        return os;  
    } 

    friend bool operator==(const Paciente& lhs, const Paciente& rhs)
    {
        return lhs.urgencia == rhs.urgencia && lhs.idade == rhs.idade;
    }

    friend bool operator < (const Paciente& lhs, const Paciente& rhs)
    {
        if(lhs.urgencia != rhs.urgencia)
            return lhs.urgencia < rhs.urgencia;
        else if(lhs.urgencia == rhs.urgencia)
        {
            if(lhs.idade != rhs.idade)
                return lhs.idade < rhs.idade;
            else
                return lhs.chegada < rhs.chegada;
        }
    }

    friend bool operator>(const Paciente& lhs, const Paciente& rhs)
    {
       if(lhs.urgencia != rhs.urgencia)
            return lhs.urgencia > rhs.urgencia;
        else if(lhs.urgencia == rhs.urgencia)
        {
            if(lhs.idade != rhs.idade)
                return lhs.idade > rhs.idade;
            else
                return lhs.chegada > rhs.chegada;
        }
    }

    friend bool operator<=(const Paciente& lhs, const Paciente& rhs)
    {
       if(lhs.urgencia != rhs.urgencia)
            return lhs.urgencia <= rhs.urgencia;
        else if(lhs.urgencia == rhs.urgencia)
        {
            if(lhs.idade != rhs.idade)
                return lhs.idade <= rhs.idade;
            else
                return lhs.chegada <= rhs.chegada;
        }
    }

    friend bool operator>=(const Paciente& lhs, const Paciente& rhs)
    {
       if(lhs.urgencia != rhs.urgencia)
            return lhs.urgencia >= rhs.urgencia;
        else if(lhs.urgencia == rhs.urgencia)
        {
            if(lhs.idade != rhs.idade)
                return lhs.idade >= rhs.idade;
            else
                return lhs.chegada >= rhs.chegada;
        }
    }
};

// A class for Min Heap 
class Heap 
{ 
public:
    vector<Paciente> arr; 
    int curSize; // Current number of elements in heap
    HeapType type; 
    // Constructor 
    Heap(HeapType tipo); 
  
    void MinHeapify(int i); 
    void MaxHeapify(int i); 

    int parent(int i) { return (i-1)/2; } 
    int left(int i) { return (2*i + 1); } 
    int right(int i) { return (2*i + 2); } 
 
    void InsertKey(Paciente k);
    Paciente ExtractRoot();
}; 
  
// Constructor: Builds a heap from a given array a[] of given size 
Heap::Heap(HeapType tipo) 
{ 
    curSize = 0;  
    //arr = new vector<Paciente>();
    type = tipo;
} 
  
void Heap::InsertKey(Paciente key) 
{ 
    curSize++; 
    arr.push_back(key);
    int i = curSize - 1;

    while (i != 0 && type == Min ? arr[parent(i)] > arr[i] : arr[parent(i)] < arr[i]) 
    { 
        swap(&arr[i], &arr[parent(i)]); 
        i = parent(i); 
    }
} 

//deleta a raiz.
Paciente Heap::ExtractRoot() 
{ 
    if (curSize <= 0) 
        return Paciente(); 

    if (curSize == 1) 
    { 
        curSize--;
        Paciente p = arr[0];
        arr.pop_back(); 
        return p; 
    } 

    Paciente root = arr[0]; 
    

    arr[0] = arr[curSize-1];
    arr.pop_back();
    curSize--; 

    if(type == Min)
        MinHeapify(0);
    else
        MaxHeapify(0); 
  
    return root; 
} 

void Heap::MinHeapify(int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < curSize && arr[l] < arr[i]) 
        smallest = l; 
    if (r < curSize && arr[r] < arr[smallest]) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&arr[i], &arr[smallest]); 
        MinHeapify(smallest); 
    } 
} 

void Heap::MaxHeapify(int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int biggest = i; 
    if (l < curSize && arr[l] > arr[i]) 
        biggest = l; 
    if (r < curSize && arr[r] > arr[biggest]) 
        biggest = r;
         
    if(biggest == i) 
        return;
    else
    { 
        swap(&arr[i], &arr[biggest]); 
        MaxHeapify(biggest); 
    }
} 
  
// A utility function to swap two elements 
void swap(Paciente *x, Paciente *y) 
{ 
    Paciente temp = *x; 
    *x = *y; 
    *y = temp; 
} 

int FindNext(vector<Heap> &list)
{
    int minIndex = 0;
    for(int i = 0; i < list.size(); i++)
    {
        
        if(minIndex == i)
            continue;

        if(list[i].arr.size() == 0)
            continue;

        //se o minIndex atual(0) for vazio, pegar o proximo nao vazio como minimo
        if(list[minIndex].arr.size() == 0 && list[i].arr.size() > 0)
        {
            minIndex = i;
            continue;
        }
        
        if(list[i].arr[0] < list[minIndex].arr[0])
        {
            minIndex = i;
            continue;
        }
    }
    return minIndex;
}

int main()
{
    int S;
    std::cin >> S;

    vector<Heap> MaxHeapList(S, Heap(Max));

    string tst;
    int chegada = 0;
    do
    {
        cin >> tst;
        if(tst == "END")
            break;
        
        if(tst == "CIN")
        {
            int i, u, a;
            cin >> i;
            cin >> u;
            cin >> a;
            Paciente p(i,u,a,chegada);
            chegada++;
            MaxHeapList[a].InsertKey(p);
        }

        if(tst == "NXT")
        {
            int A;
            cin >> A;
            cout << MaxHeapList[A].ExtractRoot();
        }

        if(tst == "STD")
        {
            int i = FindNext(MaxHeapList);
            cout << MaxHeapList[i].ExtractRoot();
        }

    }while(tst != "END");

    return 0;
}