#include <iostream>

void EnterPassword() {
   int passinput;
   std::cout << "Autharization, enter password\n>> ";
   std::cin >> passinput;
   if(passinput == passinput) { 
      std::cout << "Alright."; 
   }

   else { 
      std::cout << "Wrong password."; 
      exit(0); 
   }
}