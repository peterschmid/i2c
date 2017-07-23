#include <unistd.h>
#include <iostream>
#include "lcd.h"
#include <string.h>

using namespace std;

/**
 * Main program for display test 20 times
 */
int main(void)
{
    cout << "LDC start" << endl;
    LCD lcd(0x27);
    cout << "LDC done" << endl;
    int i = 0;
    string helloText("Hello");
    string longText("This text is fare too long");
    string clearText("                ");
    string clearHalfText("        ");

    while(i < 20)
    {

        cout << "Step " << i << endl;

	switch (i){ 
            case (1): lcd.backlightOff(); break;
            case (2): lcd.backlightOn();  break;
            case (3): lcd.display(helloText, 1); break;
            case (4): lcd.display(helloText, 2); break;
            case (5): lcd.display(longText, 1);  break;
            case (6): lcd.display(longText, 2);  break;
            case (7): lcd.display(clearHalfText, 1); break;
            case (8): lcd.display(clearHalfText, 2); break;
            case (9): lcd.display(clearText, 1); break;
            case (10): lcd.display(clearText, 2); break;
            case (11): lcd.display(helloText, 2); break;
            case (12): lcd.display(helloText, 1); break;
            case (13): lcd.backlightOff(); break;
            case (14): lcd.backlightOn();  break;
            case (15): lcd.display(helloText, 0); break;
            case (16): lcd.display(helloText, 3); break;
            case (17): lcd.clear();          break;
        }

        sleep(1);
        i++;
    }

    return 0;
}
