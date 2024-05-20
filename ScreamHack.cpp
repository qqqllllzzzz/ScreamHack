/*
*   AUTHOR | qualzed
*   VERSION | 1.0.0
*   GITHUB | NONE
*/

#include <iostream>
#include <termcolor.hpp>
#include <string>

#include "scripts/reaction.hpp"
#include "scripts/colors.hpp"
#include "scripts/texts.hpp"
#include "scripts/stealerbuilder.hpp"

using namespace std;

int main() {
    
    logo();
    cout << RESET_COLOR;

    while (1) {
        string input;
        cin >> input;
        if (input == help)
            commands();
        if (input == dos)
            system("scripts\\tools\\dos\\dos.exe");
        if (input == stealer)
            buildstealer();
        if (input == exit_from)
            exit(0);

    }
    
    return 0;
}