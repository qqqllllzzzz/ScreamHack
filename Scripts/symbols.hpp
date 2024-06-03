#include <iostream>
#include "colors.hpp"
using namespace std;

void SendError() {
    cout << red << "[!]" << RESET_COLOR << " ERROR.";
}
void Succes_Operation() {
    cout << green << "[+]" << RESET_COLOR << " SUCCES OPERATION.";
}