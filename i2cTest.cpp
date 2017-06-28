#include <unistd.h>
#include <iostream>
#include "i2c.h"
#include <string.h>

using namespace std;

/**
 * Main program to read 20 times
 */
int main(void)
{
    Pi2c i2c(0x27);
    int i = 20;
    string text("Ab1");
    char *cstr = new char[text.length() + 1];
    strcpy(cstr, text.c_str());

    while(i > 0)
    {
        int ret = i2c.i2cWrite(cstr, text.length());
        cout << "Ret = " << ret << endl;
        sleep(1);
        i--;
    }

    delete [] cstr;
    return 0;
}
