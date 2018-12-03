#include <iostream>

struct RoomCon
{
    int r_a, r_b;
    RoomCon(){}
    RoomCon(const int &a, const int &b): r_a(a), r_b(b){}
};

int main()
{
    int n = 4;
    bool sw = false;
    int counter = 0;
    int column = 0;
    int *set = new int[2*(n*n - n)];
    for(int i = 0; i < 2*(n*n - n); i++){
        std::cout << i << " ";
        counter++;
        if(!sw && counter == n-1){
            sw = true;
            counter = 0;
            std::cout << std::endl;
        }
        else if(sw && counter == n){
            sw = false;
            counter = 0;
            std::cout << std::endl;
        }
    }
    return 0;
}