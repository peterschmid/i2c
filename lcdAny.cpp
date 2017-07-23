#include <unistd.h>
#include <iostream>
#include "lcd.h"
#include <string.h>

using namespace std;

/**
 * Main program to display any paramter given
 */
int main(int argc, char* argv[])
{
    if (argc <= 2) {
        cout << "Add parameters [LineNr] and [[Description] [Value] [Unit]] | [Text]" << endl; 
        return 1;
    }
    LCD lcd(0x27, false);
    string text(argv[2]);
    if (argc == 5) {
        text.append(" ");
        text.append(argv[3]);
        text.append(argv[4]);
    }
    // clear rest of line
    text.append("                ");
    lcd.display(text, atoi(argv[1]));
    return 0;
}
