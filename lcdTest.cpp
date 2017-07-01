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
    int i = 20;
    string text("Hello");
    char *cstr = new char[text.length() + 1];
    strcpy(cstr, text.c_str());

    while(i > 0)
    {
        cout << "Display" << endl;

        lcd.display(text, 1);
        cout << "Ret = " << i << endl;
        sleep(1);
        i--;
    }

    delete [] cstr;
    return 0;
}
