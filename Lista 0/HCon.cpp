#include <iostream>

int Conversion(int hour)
{
    if(hour == 0)
        return 12;
    else if(hour >=1 && hour <= 12)
    {
        return hour;
    }
    else
    {
        return (hour - 12);
    }
};

int main ()
{
    int x;
    std::cin >> x; 
    std::cout << Conversion(x) << std::endl;
    return 0;
}