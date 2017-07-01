#!/usr/bin/python

import lcddriver
from time import*

lcd = lcddriver.lcd()
lcd.lcd_clear()

lcd.lcd_display_string("  Hello World",1)
lcd.lcd_display_string("Waterlevel 60cm",2)

#lcd.lcd_backlight('off')