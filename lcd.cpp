#include "lcd.h"
#include "i2c.h"
#include <unistd.h>

LCD::LCD(int addr){
    Pi2c i2c(addr);
    
    write(0x03);
    write(0x03);
    write(0x03);
    write(0x02);
    
    write(LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE);
    write(LCD_DISPLAYCONTROL | LCD_DISPLAYON);
    write(LCD_CLEARDISPLAY);
    write(LCD_ENTRYMODESET | LCD_ENTRYLEFT);
    usleep(200000);
}

void LCD::strobe(char data) {
    i2c.write(data | En | LCD_BACKLIGHT);
    usleep(500);
    i2c.write(((data & ~En) | LCD_BACKLIGHT));
    usleep(100);
}

void LCD::writeFourBits(char data){
    i2c.write(data | LCD_BACKLIGHT);
    strobe(data);
}
    
void LCD::write(char data, char mode =0){
    writeFourBits(mode | (cmd & 0xF0));
    writeFourBits(mode | ((cmd << 4) & 0xF0));
}

void LCD::backlight(bool isOn){
    if (isOn) {
        i2c.write(LCD_BACKLIGHT);
    } else {
        i2c.write(LCD_NOBACKLIGHT);
    }
}
    
void LCD::display(const string& data, int line) {
    if (line == 1) {
        write(0x80);
    } else if (line == 2) {
        write(0xC0);
    }
    for (int i = 0; i < data.length(); i++) {
        write(data[i], Rs);
    }
}

void LCD::clear(){
    write(LCD_CLEARDISPLAY);
    write(LCD_RETURNHOME);
}
