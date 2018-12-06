#include <iostream>
#include <vector>
#include <stdio.h> 
#include <stdlib.h> 

//Edge
struct roomCon
{
    int src, dest;//src, dest
    roomCon(){}
    roomCon(const int &a, const int &b): src(a), dest(b){}

    friend std::ostream& operator<<(std::ostream& os, const roomCon& pp)  
    {  
        //os << "room a: " << pp.src << " " << "room b: " << pp.dest;  
        os << pp.src << " " << pp.dest;  
        return os;  
    } 
};

struct subset 
{ 
    int parent; 
    int rank; 
}; 

class Graph 
{ 
    public:
        // V-> Number of vertices, E-> Number of edges 
        int V, E; 

        // graph is represented as an array of edges 
        roomCon* edges;
        subset *arr; 

        Graph():V(0), E(0){}
        Graph(const int &Vv):V(Vv), E(2*(Vv*Vv - Vv))
        { 
            edges = new roomCon[2*(Vv*Vv - Vv)]; 
            init_rooms();
            arr = new subset[Vv];
            for(int i = 0; i < Vv; i++){
                arr[i].parent = i;
                arr[i].rank = 0;    
            }
        }
        //set the values of src and dest
        void init_rooms()
        {
            bool sw = false;
            int counter = 0;
            int c = 0;
            roomCon *rset = new roomCon[2*(V*V - V)];
            for(int i = 0; i < 2*(V*V - V); i++){
                //std::cout << i << " ";
                counter++;
                
                if(!sw)
                    rset[i] = roomCon(i - ((V-1)*c), i - ((V-1)*c) + 1);
                else
                    rset[i] = roomCon(i - (V-1) - ((V-1)*c), i - ((V-1)*c) + 1);

                std::cout << rset[i] << std::endl;

                if(!sw && counter == V-1){
                    sw = true;
                    counter = 0;
                }
                else if(sw && counter == V){
                    sw = false;
                    counter = 0;
                    c++;
                }
            }
        }
        // A utility function to find set of an element i 
        // (uses path compression technique) 
        int find(int i) 
        { 
            // find root and make root as parent of i (path compression) 
            if (arr[i].parent != i) 
                arr[i].parent = find(arr[i].parent); 
        
            return arr[i].parent; 
        } 
        // A function that does union of two sets of x and y 
        // (uses union by rank) 
        void Union(int x, int y) 
        { 
            int xroot = find(x); 
            int yroot = find(y); 
        
            // Attach smaller rank tree under root of high rank tree 
            // (union by Rank) 
            if (arr[xroot].rank < arr[yroot].rank) 
                arr[xroot].parent = yroot; 
            else if (arr[xroot].rank > arr[yroot].rank) 
                arr[yroot].parent = xroot; 
        
            // If ranks are same, then make one as root and increment 
            // its rank by one 
            else
            { 
                arr[yroot].parent = xroot; 
                arr[xroot].rank++; 
            } 
        }

        void create_link(){

        }
}; 
  
  
  

// The main function to check whether a given graph contains cycle or not 
/*int isConnected( struct Graph* graph ) 
{ 
    int V = graph->V; 
    int E = graph->E; 
  
    // Allocate memory for creating V sets 
    struct subset *arr = 
        (struct subset*) malloc( V * sizeof(struct subset) ); 
  
    for (int v = 0; v < V; ++v) 
    { 
        arr[v].parent = v; 
        arr[v].rank = 0; 
    } 
  
    // Iterate through all edges of graph, find sets of both 
    // vertices of every edge, if sets are same, then there is 
    // cycle in graph. 
    for(int e = 0; e < E; ++e) 
    { 
        int x = find(arr, graph->edge[e].src); 
        int y = find(arr, graph->edge[e].dest); 
  
        if (x == y) 
            return 1; 
  
        union(arr, x, y); 
    } 
    return 0; 
} */

int main()
{
    Graph *a = new Graph(3);
    //a->init_rooms();

    return 0;
}
