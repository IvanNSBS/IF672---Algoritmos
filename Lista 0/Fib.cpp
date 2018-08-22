#include <iostream>

int CalcFib(int desired)
{
    if(desired == 0)
        return 0;
    if(desired == 1)
        return 1;
    else
        return (CalcFib(desired-1) + CalcFib(desired-2));
}

int main()
{
    int desired;
    std::cin >> desired;
    std::cout << CalcFib(desired-1) << std::endl;
    return 0;
}