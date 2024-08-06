#include <iostream>
#include <string>
#include "Scripts/colors.hpp"

using namespace std;

int arrow_moves = 0;
int yes = 10;
int no = 20;
int Settings = 01;
int StartCompile = 02;
int GitHub = 03;
int EXIT1 = 04;

void Compile() {
    system("start cmd /k g++ ScreamHack.cpp -o ScreamHack.exe -Wl,-subsystem,windows -municode -lcomdlg32 -static-libgcc -static-libstdc++ --static -lgdi32");
    cout << "Script compile successfully.\n";
}

int main()
{
    int inp;
    cout << br_green << "ScreamHack compiler 1.0.2" << RESET_COLOR << "\n> [01] Settings\n> [02] Compile\n> [03] Github\n> [04] Exit\n";
    while (true) {
        cin >> inp;

        if (inp == StartCompile) {
            Compile();
        }
        else if(inp == GitHub) {

        }
        else if (inp == EXIT1) {
            exit(0);
        }
    }
    return 0;
}