#include <iostream>
#include <cmath>
#include <string> // to use the string object
#include <cstdlib>
#include <vector>
#include <cctype> // isupper(), isdigit()
#include <iomanip> // for setw()


#include "clsLoginScreen.h"
#include "clsCurrency.h"

using namespace std;

int main() {
    while (true) if (!clsLoginScreen::ShowLoginScreen()) break;
}

