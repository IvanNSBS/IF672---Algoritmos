#include <iostream>

struct RoomCon
{
    int r_a, r_b;
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
    int n = 4;
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
/*
  _________________________
  |     |     |     |     |
  |  0  |  1  |  2  |  3  |
  |     |     |     |     |
  |-----+-----+-----+-----|
  |     |     |     |     |
  |  4  |  5  |  6  |   7 |
  |     |     |     |     |
  |-----+-----+-----+-----|
  |     |     |     |     |
  |  8  |  9  |  10 |  11 |
  |     |     |     |     |
  |-----+-----+-----+-----|
  |     |     |     |     |
  |  12 |  13 |  14 | 15  |
  |     |     |     |     |
  |     |     |     |     |
  ------------------------

  _________________________
  |     |     |     |     |
  |     0     1     2     |
  |     |     |     |     |
  |--3--+--4--+--5--+--6--|
  |     |     |     |     |
  |     7     8     9     |
  |     |     |     |     |
  |-10--+-11--+-12--+-13--|
  |     |     |     |     |
  |    14     15    16    |
  |     |     |     |     |
  |-17--+-18--+-19--+-20--|
  |     |     |     |     |
  |    21    22    23     |
  |     |     |     |     |
  ------------------------

*/