#include "lcd.h"
#include <unistd.h>

// commands
#define LCD_CLEARDISPLAY   0x01
#define LCD_RETURNHOME     0x02
#define LCD_ENTRYMODESET   0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT    0x10
#define LCD_FUNCTIONSET    0x20
#define LCD_SETCGRAMADDR   0x40
#define LCD_SETDDRAMADDR   0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT           0x00
#define LCD_ENTRYLEFT            0x02
#define LCD_ENTRYSHIFTINCREMENT  0x01
#define LCD_ENTRYSHIFTDECREMENT  0x00

// flags for display on/off control
#define LCD_DISPLAYON  0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON   0x02
#define LCD_CURSOROFF  0x00
#define LCD_BLINKON    0x01
#define LCD_BLINKOFF   0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE  0x00
#define LCD_MOVERIGHT   0x04
#define LCD_MOVELEFT    0x00

// flags for function set
#define LCD_8BITMODE  0x10
#define LCD_4BITMODE  0x00
#define LCD_2LINE     0x08
#define LCD_1LINE     0x00
#define LCD_5x10DOTS  0x04
#define LCD_5x8DOTS   0x00

// flags for backlight control
#define LCD_BACKLIGHT   0x08
#define LCD_NOBACKLIGHT 0x00

// modes
#define En 0b00000100 // Enable bit
#define Rw 0b00000010 // Read/Write bit
#define Rs 0b00000001 // Register select bit

LCD::LCD(int addr, bool doInit) : i2c(addr), isBacklightOn(true){
    if (doInit) {
        init();
    }
}

int LCD::init(){
    int ret = 0;
    usleep(40000); // wait time >40ms
    ret += writeLowerFourBits(0x03);
    usleep(5000); // wait time >4.1ms
    ret += writeLowerFourBits(0x03);
    usleep(200); // wait time >100us
    ret += writeLowerFourBits(0x03);
    // set 4 bit mode
    ret += writeLowerFourBits(0x02);
    // set function
    ret += writeByte(LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE);
    ret += writeByte(LCD_DISPLAYCONTROL | LCD_DISPLAYON);
    ret += writeByte(LCD_CLEARDISPLAY);
    ret += writeByte(LCD_ENTRYMODESET | LCD_ENTRYLEFT);
    usleep(200000);
    return ret;
}

int LCD::strobe(char data) {
    // tc = 400ns, tpw min = 150ns
    int ret = i2c.i2cWrite(data | En);
    usleep(500);
    ret += i2c.i2cWrite(data & ~En);
    usleep(100);
    return ret;
}

int LCD::write(char data){
    if (isBacklightOn) {
        data = data | LCD_BACKLIGHT;
    }
    int ret = i2c.i2cWrite(data);
    ret += strobe(data);
    return ret;
}

int LCD::writeUpperFourBits(char data, char mode){
    return write((mode & 0x0F) | (data & 0xF0));
}

int LCD::writeLowerFourBits(char data, char mode){
    return writeUpperFourBits(data << 4, mode);
}

int LCD::writeByte(char data, char mode){
    int ret = writeUpperFourBits(data, mode);
    ret += writeLowerFourBits(data, mode);
    return ret;
}

int LCD::backlightOn(){
    isBacklightOn = true;
    //write strait to i2c, no need for strobe
    return i2c.i2cWrite(LCD_BACKLIGHT);
}

int LCD::backlightOff(){
    isBacklightOn = false;
    //write strait to i2c, no need for strobe
    return i2c.i2cWrite(LCD_NOBACKLIGHT);
}
    
int LCD::display(const std::string& data, unsigned int line) {
    int ret = 0;
    if (line == 1) {
        ret += writeByte(0x80);
    } else if (line == 2) {
        ret += writeByte(0xC0);
    } else {
        // exit with error
        return -1;
    }
    for (unsigned int i = 0; i < data.length(); i++) {
        ret += writeByte(data[i], Rs);
    }
    return ret;
}

int LCD::clear(){
    int ret = 0;
    ret += writeByte(LCD_CLEARDISPLAY);
    ret += writeByte(LCD_RETURNHOME);
    return ret;
}
