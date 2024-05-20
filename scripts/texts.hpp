#include "colors.hpp"
#include <string>

using namespace std;

void logo() {
    cout << red << "Scr" << green << "ea" << blue << "mH" << magenta << "a" << cyan << "ck";
    cout << "\nType 'help' to get a list of commands.\n";
}

void commands() {
    cout << green << "1. DOS - Caution! Your computer may catch fire\n2. Stealer " << red << "- Python, telebot and pywin32 are required\n" << RESET_COLOR;
}