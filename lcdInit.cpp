#include <unistd.h>
#include <iostream>
#include "lcd.h"
#include <string.h>

using namespace std;

/**
 * Main program to init the display
 */
int main(void)
{
    LCD lcd(0x27);
    string text("Init Display");
    lcd.display(text, 1);
    lcd.display(text, 2);
    return 0;
}
