#include <iostream>
#include <string>

using namespace std;

int main()
{
    int N;
    cin >> N;
    string* nomes = new string[N];

    for(int i = 0; i < N; i++)
        cin >> nomes[i];

    
    return 0;
}