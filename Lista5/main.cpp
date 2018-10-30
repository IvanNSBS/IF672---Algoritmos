#include <iostream>

struct Room
{
    int r_a, r_b;
    Room(){}
    Room(const int &a, const int &b): r_a(a), r_b(b){}
};

struct Indexes
{
public:
    int i,j, multi, multj;
    Indexes(){}
    Indexes(const int &ii, const int &jj): i(ii), j(jj){}
    Indexes(const int &ii, const int &jj, const int &mi, const int &mj): i(ii), j(jj), multi(mi), multj(j){}
};


Indexes GetIndexes(int index, int n)
{
    int auxi = 1;
    int auxj = 1;
    int i=0, j=0;
    int indexi = 0, indexj = 0;

    int result = 0;
    while(result != index)
    {
        indexi++;
        for(i; i < (n-1)*auxi; ++i)
        {
            i++;
            if(result == index)
            {
                //std::cout << i << "   " << j << std::endl;
                return Indexes(i,j, auxi, auxj);
            }

            result++;
            i--;
        }
        auxi++;

        indexj++;
        for(j; j < n*auxj; j++)
        {
            j++;
            if(result == index)
            {
                //std::cout << i << "   " << j << std::endl;
                //std::cout << "indexi: " << indexi << "   " << "indexj: " << indexj << std::endl;
                return Indexes(i,j, auxi, auxj);
            }
                
            result++;
            j--;
        }
        auxj++;
    }
}

Room getRoom(int index, int n)
{
    Indexes in = GetIndexes(index, n);
    bool bIsHorizontal = in.i != in.j;

    if(bIsHorizontal)
        return Room(index, index+1);
    else
        return Room(index-1-((n-1)*in.multi), index-1-((n-1)*in.multi)+n);
}

int main()
{
    int n = 3;
    int index = 2, aux = 0;
    //int *rooms = new int[(n*n)-1];
    //int *doors = new int[2*(n*n - n) - 1];

    Room r = getRoom(index, n);
    std::cout << r.r_a << "  " << r.r_b << std::endl;
    return 0;
}