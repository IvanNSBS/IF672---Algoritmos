#include <stdio.h> 
#include <limits.h> 
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
  
struct Graph
{
public:
    int num_vertices;
    float **adj_list;
    //int **path_list;
public:
    Graph(){}
    Graph(const int &v) : num_vertices(v)
    { 
        adj_list = new float*[v];
        for(int i = 0; i < v; i++)
            adj_list[i] = new float[v];


        for(int i = 0; i < v; i++)
            for(int j = 0; j < v; j++)
                adj_list[i][j] = 0;
    }

    void add_edge(int src, int dest, float weight){
        adj_list[src][dest] = weight;
        adj_list[dest][src] = weight;
    }
    
    int min_distance(float dist[], bool visited[]) 
    { 
        float min = (std::numeric_limits<float>::max()), min_index; 
    
        for (int v = 0; v < num_vertices; v++) 
            if (visited[v] == false && dist[v] <= min) 
                min = dist[v], min_index = v; 
    
        return min_index; 
    } 

    void print_path(int parent[], int j) 
    { 
        if (parent[j] == - 1) {
            return; 
        }
        printf("%d ", j);
        print_path(parent, parent[j]);
    } 
    
    void dijkstra(int src, int dest) 
    { 

        float *dist = new float [num_vertices];  
        bool *visited = new bool [num_vertices];
        int *parent = new int[num_vertices]; 
    
        for (int i = 0; i < num_vertices; i++) 
        { 
            parent[i] = -1; 
            dist[i] = std::numeric_limits<float>::max(); 
            visited[i] = false; 
        } 

        dist[src] = 0;  
        for (int count = 0; count < num_vertices - 1; count++) 
        {  
            int u = min_distance(dist, visited); 
            visited[u] = true; 
            for (int v = 0; v < num_vertices; v++) 
                if (!visited[v] && adj_list[u][v] && 
                    dist[u] + adj_list[u][v] < dist[v]) 
                { 
                    parent[v] = u; 
                    dist[v] = dist[u] + adj_list[u][v]; 
                }  
        }
        printf("%d ", src);
        print_path(parent, parent[dest]);
        printf("%d", dest);
        printf("\n"); 
    } 
};

float get_weight(float &P, float &B, float &C)
{
    float W = (P*B + (1-P)*C) / (B+C);
    return W;
}

int main() 
{ 
    float P;
    std::cin >> P;

    int N, M;
    std::cin >> N >> M;

    Graph *a = new Graph(N);

    for(int i = 0; i < M; ++i)
    {
        int X, Y;
        float B, C;
        std::cin >> X >> Y >> B >> C;
        a->add_edge(X,Y, get_weight(P,B,C));
    }
    
    int S, T;
    /*std::cin >> S >> T; 
    a->dijkstra(S, T);*/

    while ( std::cin >> S >> T )
   {
      a->dijkstra(S, T);
   }
    return 0; 
} 

























