#include <stdio.h> 
#include <limits.h> 
#include <iostream>
#include <limits>
  
struct Graph
{
public:
    int num_vertices;
    double **adj_list;
public:
    Graph(){}
    Graph(const int &v) : num_vertices(v)
    { 
        adj_list = new double*[v];
        for(int i = 0; i < v; i++){
            adj_list[i] = new double[v];
        }

        for(int i = 0; i < v; i++)
            for(int j = 0; j < v; j++)
                adj_list[i][j] = 9999999999;
    }

    void add_edge(int src, int dest, double weight){
        if(weight <= adj_list[src][dest])
        {
            adj_list[src][dest] = weight;
            adj_list[dest][src] = weight;
        }
    }
    
    int min_distance(double dist[], bool visited[]) 
    { 
        double min = (std::numeric_limits<double>::max()), min_index; 
    
        for (int v = 0; v < num_vertices; v++) 
            if (visited[v] == false && dist[v] <= min) 
                min = dist[v], min_index = v; 
    
        return min_index; 
    } 

    void print_path(int parent[], int j) 
    { 
        if (parent[j] == -1) 
            return; 
        
        print_path(parent, parent[j]);
        printf("%d ", j);
    } 

    void print_answer(int parent[], int src, int dest)
    {
        printf("%d ", src);
        print_path(parent, parent[dest]);
        printf("%d", dest);
        printf("\n");
    }
    
    void dijkstra(int src, int dest) 
    { 

        double *dist = new double [num_vertices];  
        bool *visited = new bool [num_vertices];
        int *parent = new int[num_vertices]; 
    
        for (int i = 0; i < num_vertices; i++) 
        { 
            parent[i] = -1; 
            dist[i] = std::numeric_limits<double>::max(); 
            visited[i] = false; 
        } 

        dist[src] = 0;  
        for (int count = 0; count < num_vertices - 1 ; count++) 
        {  
            int u = min_distance(dist, visited); 
            visited[u] = true; 
            for (int v = 0; v < num_vertices; v++) 
                if (!visited[v] && adj_list[u][v] && dist[u] + adj_list[u][v] < dist[v]) 
                { 
                    parent[v] = u;
                    dist[v] = dist[u] + adj_list[u][v]; 
                }  
        }

        print_answer(parent, src, dest);
    } 
};

double get_weight(double &P, double &B, double &C)
{
    double W = ( (P*B) + ((1-P)*C) ) / (B+C);
    return W;
}

int main() 
{ 
    double P;
    std::cin >> P;

    int N, M;
    std::cin >> N >> M;

    Graph *a = new Graph(N);

    for(int i = 0; i < M; ++i)
    {
        int X, Y;
        double B, C;
        std::cin >> X >> Y;
        std::cin >> B >> C;
        a->add_edge(X,Y, get_weight(P,B,C));
    }
    
    int S, T;

    while ( std::cin >> S >> T )
    {        
        a->dijkstra(S, T);
    }
    return 0; 
} 