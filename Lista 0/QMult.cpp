#include <iostream>

int Mult(int a, int b)
{
    int answer = 0;
    int aux = a < 0 ? -1 : 1;

    for(int i = 0; i < a*aux; i++)
        answer = answer + b;
    return answer*aux;
};

int main ()
{
    int a,b;
    std::cin >> a >> b; 
    std::cout << Mult(a,b) << std::endl;
    return 0;
}