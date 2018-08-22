#include <iostream>

using namespace std;

int main()
{
    int temp;
    cin >> temp;

    if(temp < 20)
    {
        if(temp < 10)
        {
            if(temp < -10)
            {
                if(temp < -20)
                    cout << "MUITO FRIO" << endl;
                else
                    cout << "BASTANTE FRIO" << endl;
            }
            else
                cout << "FRIO" << endl;
        }
        else
            cout << "MORNO" << endl;
    }
    else
        cout << "DESCONHECIDA" << endl;

    return 0;
}