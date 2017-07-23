#include <unistd.h>
#include <iostream>
#include "lcd.h"
#include <string.h>

using namespace std;

/**
 * Main program to display water level
 */
int main(int argc, char* argv[])
{
    if (argc <= 1) {
        cout << "Add parameter [water level in cm]" << endl; 
        return 1;
    }
    LCD lcd(0x27, false);
    string text("Waterlevel ");
    text.append(argv[1]);
    text.append("cm  ");
    lcd.display(text, 1);
    return 0;
}
