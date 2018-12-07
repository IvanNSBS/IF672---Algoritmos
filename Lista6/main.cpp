#include <stdio.h> 
#include <limits.h> 
#include <iostream>
#include <sstream>
#include <string>
  
struct Graph
{
public:
    int num_vertices;
    int **adj_list;
    //int **path_list;
public:
    Graph(){}
    Graph(const int &v) : num_vertices(v)
    { 
        adj_list = new int*[v];
        for(int i = 0; i < v; i++)
            adj_list[i] = new int[v];


        for(int i = 0; i < v; i++)
            for(int j = 0; j < v; j++)
                adj_list[i][j] = 0;
    }

    void add_edge(int src, int dest, int weight){
        adj_list[src][dest] = weight;
        adj_list[dest][src] = weight;
    }
    
    int min_distance(int dist[], bool visited[]) 
    { 
        // Initialize min value 
        int min = INT_MAX, min_index; 
    
        for (int v = 0; v < num_vertices; v++) 
            if (visited[v] == false && dist[v] <= min) 
                min = dist[v], min_index = v; 
    
        return min_index; 
    } 

    void print_path(int parent[], int j) 
    { 
        if (parent[j] == - 1) 
            return; 
    
        print_path(parent, parent[j]); 
    
        printf("%d ", j); 
    } 
    
    void dijkstra(int src, int dest) 
    { 
        int dist[num_vertices];  
        bool visited[num_vertices];
        int parent[num_vertices]; 
    
        for (int i = 0; i < num_vertices; i++) 
        { 
            parent[0] = -1; 
            dist[i] = INT_MAX; 
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
        print_path(parent, dest);
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
        int X, Y, B, C;
        std::cin >> X >> Y >> B >> C;
        a->add_edge(X,Y, get_weight(P,B,C));
    }

    std::string line;
	std::getline(std::cin,line);
	std::stringstream stream(line);
    int S, T;
	while (!stream.eof()){
		stream >> S >> T;
        a->dijkstra(S, T);
	}
    return 0; 
} 






























// int printSolution(int dist[], int n, int parent[]) 
// { 
//     int src = 0; 
//     printf("Vertex\t Distance\tPath"); 
//     for (int i = 1; i < V; i++) 
//     { 
//         printf("\n%d -> %d \t\t %d\t\t%d ", 
//                       src, i, dist[i], src); 
//         print_path(parent, i); 
//     }
//     printf("\n"); 
// } 