#include "lcd.h"
#include <unistd.h>
#include <iostream>

LCD::LCD(int addr) : i2c(addr){
    
//    i2c.i2cWrite(0x03);
//    i2c.i2cWrite(0x03);
//    i2c.i2cWrite(0x03);
//    i2c.i2cWrite(0x02);
    
    int ret = 0;
    ret += i2c.i2cWrite(LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE);
    ret += i2c.i2cWrite(LCD_DISPLAYCONTROL | LCD_DISPLAYON);
    ret += i2c.i2cWrite(LCD_CLEARDISPLAY);
    ret += i2c.i2cWrite(LCD_ENTRYMODESET | LCD_ENTRYLEFT);
    std::cout << "LCD Ret = " << ret << std::endl;
    usleep(200000);
}

void LCD::strobe(char data) {
    i2c.i2cWrite(data | En | LCD_BACKLIGHT);
    usleep(500);
    i2c.i2cWrite(((data & ~En) | LCD_BACKLIGHT));
    usleep(100);
}

int LCD::writeFourBits(char data){
    int ret = i2c.i2cWrite(data | LCD_BACKLIGHT);
    strobe(data);
    return ret;
}
    
int LCD::write(char data, char mode){
    int ret = writeFourBits(mode | (data & 0xF0));
    ret += writeFourBits(mode | ((data << 4) & 0xF0));
    return ret;
}

void LCD::backlight(bool isOn){
    int ret = 0;
    if (isOn) {
        ret += i2c.i2cWrite(LCD_BACKLIGHT);
    } else {
        ret += i2c.i2cWrite(LCD_NOBACKLIGHT);
    }
    std::cout << "backlight Ret = " << ret << std::endl;
}
    
void LCD::display(const std::string& data, unsigned int line) {
    int ret = 0;
    if (line == 1) {
        ret += write(0x80);
    } else if (line == 2) {
        ret += write(0xC0);
    }
    for (unsigned int i = 0; i < data.length(); i++) {
        ret += write(data[i], Rs);
    }
    std::cout << "display Ret = " << ret << std::endl;
}

void LCD::clear(){
    int ret = 0;
    ret += write(LCD_CLEARDISPLAY);
    ret += write(LCD_RETURNHOME);
    std::cout << "clear Ret = " << ret << std::endl;
}
