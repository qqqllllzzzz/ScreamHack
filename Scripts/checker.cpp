#include <iostream>
#include <fstream>
#include <string>
#include "symbols.hpp"

using namespace std;

void CheckDOS() {
    ifstream iff("scripts\\tools\\dos\\dos.exe");
    if(iff.bad()==true) {
        SendError();
    } 
    else cout<<"dos.exe is alive.";
}

void CheckSTEALER() {
    ifstream iff("scripts\\tools\\stealer\\stealer.py");
    if(iff.bad()==true) {
        SendError();
    } 
    else cout<<"stealer.py is alive.";
}

int main() {

    string input;

    cout << "1. DOS\n2. Stealer\nWhat do you want check?: ";

    cin >> input;
    if(input == "1") {
        CheckDOS();
    }
    else CheckSTEALER();

    return 0;
}