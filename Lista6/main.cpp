#include <stdio.h> 
#include <limits.h> 
  
struct Graph
{
public:
    int num_vertices;
    int **adj_list;// = new int[num_vertices][num_vertices];
    int **path_list;
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


// Driver Code 
int main() 
{ 
    //  Let us create the example 
    // graph discussed above 
    int graph[9][9] = {{0, 4, 0, 0, 0, 0, 0, 8, 0}, 
                       {4, 0, 8, 0, 0, 0, 0, 11, 0}, 
                       {0, 8, 0, 7, 0, 4, 0, 0, 2}, 
                       {0, 0, 7, 0, 9, 14, 0, 0, 0}, 
                       {0, 0, 0, 9, 0, 10, 0, 0, 0}, 
                       {0, 0, 4, 0, 10, 0, 2, 0, 0}, 
                       {0, 0, 0, 14, 0, 2, 0, 1, 6}, 
                       {8, 11, 0, 0, 0, 0, 1, 0, 7}, 
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}}; 
  
    Graph *a = new Graph(9);
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j)
            a->add_edge(i,j, graph[i][j]);

    a->dijkstra(0, 9); 
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