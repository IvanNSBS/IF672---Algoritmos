#include <iostream>
#include <stdio.h> 
#include <vector>

class KnapsackP
{
public:
    int N;
    int capacity;
    int *W, *V;

    KnapsackP(){}
    KnapsackP(const int &n, const int &c):N(n), capacity(c){ W = new int[n]; V = new int[n];} 


    void zo_knapsack()
    {
        int **DP = new int*[N+1];
        for(int i = 0; i < N + 1; ++i)
            DP[i] = new int[capacity+1];
        
        for (int i = 0; i < N + 1; ++i)
            for (int j = 0; j < capacity + 1; ++j)
                DP[i][j] = 0;

        for (int i = 1; i < N + 1; ++i)
        {
            int w = W[i-1];
            int v = V[i-1];
            
            for (int j = 1; j < capacity + 1; ++j)
            {
                DP[i][j] = DP[i-1][j];
                if (j >= w && DP[i-1][j-w] + v > DP[i][j]){
                    DP[i][j] = DP[i-1][j-w] + v;
                }
            }
        }

        int cur_size = capacity;
        std::vector<int> selected_list;

        for (int i = N; i > 0; --i)
        {
            if (DP[i][cur_size] != DP[i-1][cur_size])
            {
                int cur_item = i-1;
                selected_list.push_back(cur_item);
                cur_size -= W[cur_item];
            }
        } 

        printf("Maximum profit: %d\n", DP[N][capacity]);
        for(int i = selected_list.size() - 1; i >= 0; --i)
            printf("%d ", selected_list[i]);
            
        return;
    }
};

int main()
{
    int cap = 10;
    int N = 4;
    int V[] = {5, 4, 8, 5};
    int W[] = {3, 3, 5, 6};
    KnapsackP kn(N, cap);
    for(int i = 0; i < 4; ++i){
        kn.W[i] = W[i]; 
        kn.V[i] = V[i]; 
    }
    kn.zo_knapsack();
    return 0;
}