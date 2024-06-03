#include <iostream>
#include <string>
#include "Scripts/colors.hpp"
using namespace std;

int arrow_moves = 0;
std::string yes = "yes";
std::string no = "no";
std::string Settings = "settings";
std::string StartCompile = "compile";
std::string EXIT1 = "exit";

void Compile() {
    system("start cmd /k g++ ScreamHack.cpp -o ScreamHack.exe");
    cout << "Script compile successfully.\n";
}

int main()
{
    std::string inp;

    cout << br_blue << "-. COMPILE SETTINGS .-" << RESET_COLOR << "\n>> settings\n>> compile\n>> github\n>> exit\n";
    
    while (true) {
        cin >> inp;

        if (inp == StartCompile) {
            Compile();
        }

        else if (inp == EXIT1) {
            exit(0);
        }
    }

    return 0;
}