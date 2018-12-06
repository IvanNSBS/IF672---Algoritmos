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
            arr = new subset[Vv*Vv];
            for(int i = 0; i < Vv*Vv; i++){
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
            for(int i = 0; i < 2*(V*V - V); i++){
                //std::cout << i << " ";
                counter++;
                
                if(!sw)
                    edges[i] = roomCon(i - ((V-1)*c), i - ((V-1)*c) + 1);
                else
                    edges[i] = roomCon(i - (V-1) - ((V-1)*c), i - ((V-1)*c) + 1);

                //std::cout << edges[i] << std::endl;

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

        int find(int i) 
        { 
            if (arr[i].parent != i) 
                arr[i].parent = find(arr[i].parent); 
        
            return arr[i].parent; 
        } 

        void Union(int x, int y) 
        { 
            int xroot = find(x); 
            int yroot = find(y); 
        
            if (arr[xroot].rank < arr[yroot].rank) 
                arr[xroot].parent = yroot; 
            else if (arr[xroot].rank > arr[yroot].rank) 
                arr[yroot].parent = xroot; 
        
            else
            { 
                arr[yroot].parent = xroot; 
                arr[xroot].rank++; 
            } 
        }

        void remove_wall(int wall){
            //std::cout << "in wall\n";
            //for(int i = 0; i < V; i++)
            //    std::cout << "at arr: " << arr[i].parent << std::endl;

            //std::cout << "Rooms of wall -> "<< edges[wall] << std::endl;
            //std::cout << "at arr: " << arr[edges[wall].src].parent << " " << arr[edges[wall].dest].parent << std::endl;
            int x = find(edges[wall].src); 
            int y = find(edges[wall].dest); 
    
            Union(x, y); 
        }

        int are_rooms_connected(int r_a, int r_b){
            int par_a = find(r_a);
            int par_b = find(r_b);   
            if(par_a == par_b)
                return 1;
            else
                return 0;
        }
}; 
  
int main()
{
    //Graph *a = new Graph(3);
    int K; //numero de casos
    std::cin >> K; 
    for(int i = 0; i < K; ++i)
    {
        int N; // maze size
        int M; //qntidade de paredes removidas
        int Q; //qntidade de paredes pra consultar
        std::cin >> N >> M >> Q;

        Graph *a = new Graph(N);
        for(int j = 0; j < M; ++j)
        {
            int index;
            std::cin >> index;
            a->remove_wall(index);
        }

        for(int j = 0; j < Q; ++j)
        {
            int r_a;
            int r_b;
            std::cin >> r_a >> r_b;
            int result = a->are_rooms_connected(r_a, r_b);
            printf("%d.%d %d\n", i, j, result);
        }
        printf("\n");
    }
    return 0;
}
