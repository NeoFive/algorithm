#include<string>

int main()
{
    std::string s = "123456789";
    for (int i = 0; i < s.length(); i++)
        printf("s.substr(%d) = %s\n", i, s.substr(i).c_str());


    return 0;
}
