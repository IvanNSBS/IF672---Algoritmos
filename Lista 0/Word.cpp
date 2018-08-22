#include <iostream>
#include <string>

bool IsCool(std::string name)
{
    int alphabet[27] = {0};
    
    for(int i = 0; i< name.length(); i++)
    {
        alphabet[(int)name.at(i)-65]++;
        if(alphabet[(int)name.at(i)-65] > 1)
            return false;
    }
    return true;
}

int main()
{
    std::string name = "";
    std::cin >> name;
    std::string answer = IsCool(name) ? "MANEIRA" : "NÃO MANEIRA";
    std::cout << answer << std::endl; 
    return 0;
}