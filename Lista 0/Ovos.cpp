#include <iostream>

using namespace std;

int main()
{
    int N,K;
    cin >> N >> K;

    int answer = N + (N/K);
    int casc = N/K + (N%K);

    while(casc >= K)
    {
        answer = answer + (casc/K);
        casc = casc/K + (casc%K);
    }
    cout << answer << endl;
    return 0;
}