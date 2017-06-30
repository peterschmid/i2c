#include "lcd.h"
#include "i2c.h"

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

void LCD::strobe(void* data, int lenth);
void LCD::writeFourBits(void* data, lenth);
    
void LCD::write(char data);
void LCD::backlight();
    
void LCD::display(string str);
void LCD::clear()



   # clocks EN to latch command
   def lcd_strobe(self, data):
      self.lcd_device.write_cmd(data | En | LCD_BACKLIGHT)
      sleep(.0005)
      self.lcd_device.write_cmd(((data & ~En) | LCD_BACKLIGHT))
      sleep(.0001)

   def lcd_write_four_bits(self, data):
      self.lcd_device.write_cmd(data | LCD_BACKLIGHT)
      self.lcd_strobe(data)

   # write a command to lcd
   def lcd_write(self, cmd, mode=0):
      self.lcd_write_four_bits(mode | (cmd & 0xF0))
      self.lcd_write_four_bits(mode | ((cmd << 4) & 0xF0))
      
   #turn on/off the lcd backlight
   def lcd_backlight(self, state):
      if state in ("on","On","ON"):
         self.lcd_device.write_cmd(LCD_BACKLIGHT)
      elif state in ("off","Off","OFF"):
         self.lcd_device.write_cmd(LCD_NOBACKLIGHT)
      else:
         print("Unknown State!")

   # put string function
   def lcd_display_string(self, string, line):
      if line == 1:
         self.lcd_write(0x80)
      if line == 2:
         self.lcd_write(0xC0)
      if line == 3:
         self.lcd_write(0x94)
      if line == 4:
         self.lcd_write(0xD4)

      for char in string:
         self.lcd_write(ord(char), Rs)

   # clear lcd and set to home
   def lcd_clear(self):
      self.lcd_write(LCD_CLEARDISPLAY)
      self.lcd_write(LCD_RETURNHOME)
