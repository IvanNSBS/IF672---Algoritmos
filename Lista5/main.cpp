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

                //std::cout << rset[i] << std::endl;

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

    int N; // maze size
    int M; //qntidade de paredes removidas
    int Q; //qntidade de paredes pra consultar
    std::cin >> N >> M >> Q;
    return 0;
}
