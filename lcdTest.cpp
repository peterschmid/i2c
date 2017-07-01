#include <unistd.h>
#include <iostream>
#include "lcd.h"
#include <string.h>

using namespace std;

/**
 * Main program to read 20 times
 */
int main(void)
{
    cout << "LDC start" << endl;
    LCD lcd(0x27);
    cout << "LDC done" << endl;
    int i = 0;
    string text("Hello");

    while(i < 20)
    {
        cout << "Display" << endl;

	switch (i){ 
            case (1): lcd.backlight(false); break;
            case (2): lcd.backlight(true);  break;
            case (3): lcd.display(text, 1); break;
            case (4): lcd.display(text, 2); break;
            case (5): lcd.clear();          break;
        }

        cout << "Loop " << i << endl;
        sleep(1);
        i++;
    }

    return 0;
}
