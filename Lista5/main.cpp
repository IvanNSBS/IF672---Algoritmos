#include <iostream>

// A union by rank and path compression based program to detect cycle in a graph 
#include <stdio.h> 
#include <stdlib.h> 
  
// a structure to represent an edge in the graph 
struct Edge 
{ 
    int src, dest; 
}; 
  
// a structure to represent a graph 
struct Graph 
{ 
    // V-> Number of vertices, E-> Number of edges 
    int V, E; 
  
    // graph is represented as an array of edges 
    struct Edge* edge; 
}; 
  
struct subset 
{ 
    int parent; 
    int rank; 
}; 
  
// Creates a graph with V vertices and E edges 
struct Graph* createGraph(int V, int E) 
{ 
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) ); 
    graph->V = V; 
    graph->E = E; 
  
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) ); 
  
    return graph; 
} 
  
// A utility function to find set of an element i 
// (uses path compression technique) 
int find(struct subset subsets[], int i) 
{ 
    // find root and make root as parent of i (path compression) 
    if (subsets[i].parent != i) 
        subsets[i].parent = find(subsets, subsets[i].parent); 
  
    return subsets[i].parent; 
} 
  
// A function that does union of two sets of x and y 
// (uses union by rank) 
void Union(struct subset subsets[], int x, int y) 
{ 
    int xroot = find(subsets, x); 
    int yroot = find(subsets, y); 
  
    // Attach smaller rank tree under root of high rank tree 
    // (Union by Rank) 
    if (subsets[xroot].rank < subsets[yroot].rank) 
        subsets[xroot].parent = yroot; 
    else if (subsets[xroot].rank > subsets[yroot].rank) 
        subsets[yroot].parent = xroot; 
  
    // If ranks are same, then make one as root and increment 
    // its rank by one 
    else
    { 
        subsets[yroot].parent = xroot; 
        subsets[xroot].rank++; 
    } 
} 

struct RoomCon
{
    int r_a, r_b;//src, dest
    RoomCon(){}
    RoomCon(const int &a, const int &b): r_a(a), r_b(b){}

    friend std::ostream& operator<<(std::ostream& os, const RoomCon& pp)  
    {  
        //os << "room a: " << pp.r_a << " " << "room b: " << pp.r_b;  
        os << pp.r_a << " " << pp.r_b;  
        return os;  
    } 
};

int main()
{
    int n = 5;
    bool sw = false;
    int counter = 0;
    int c = 0;
    RoomCon *rset = new RoomCon[2*(n*n - n)];
    for(int i = 0; i < 2*(n*n - n); i++){
        //std::cout << i << " ";
        counter++;
        
        if(!sw)
            rset[i] = RoomCon(i - ((n-1)*c), i - ((n-1)*c) + 1);
        else
            rset[i] = RoomCon(i - (n-1) - ((n-1)*c), i - ((n-1)*c) + 1);

        std::cout << rset[i] << std::endl;

        if(!sw && counter == n-1){
            sw = true;
            counter = 0;
        }
        else if(sw && counter == n){
            sw = false;
            counter = 0;
            c++;
        }
    }
    return 0;
}
