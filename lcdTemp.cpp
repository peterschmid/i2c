#include <unistd.h>
#include <iostream>
#include "lcd.h"
#include <string.h>

using namespace std;

/**
 * Main program to display temperature
 */
int main(int argc, char* argv[])
{
    if (argc <= 1) {
        cout << "Add parameter [Temperature in °C]" << endl; 
        return 1;
    }
    LCD lcd(0x27, false);
    string text("Warmwater ");
    text.append(argv[1]);
    text.append("C   ");
    lcd.display(text, 2);
    return 0;
}
