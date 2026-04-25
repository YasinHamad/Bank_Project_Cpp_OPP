#include <iostream>
#include <cmath>
#include <string> // to use the string object
#include <cstdlib>
#include <vector>
#include <cctype> // isupper(), isdigit()
#include <iomanip> // for setw()
//#include <fstream> // for files
//#include <ctime> // for time
#include <print>


#include "clsLoginScreen.h"

#include "clsCurrency.h"

using namespace std;
string message;



int main() {
    //clsMainScreen::ShowMainMenue();
    while (true) if (!clsLoginScreen::ShowLoginScreen()) break;


    
}

