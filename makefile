build-test: i2c.cpp i2cTest.cpp
	g++ -std=c++0x -Wall -o OutBin.bin i2c.cpp i2cTest.cpp

build-lcd: i2c.cpp lcd.cpp lcdTest.cpp
	g++ -std=c++0x -Wall -o LCD.bin i2c.cpp lcd.cpp lcdTest.cpp

build-water: i2c.cpp lcd.cpp lcdWater.cpp
	g++ -std=c++0x -Wall -o LcdWater.bin i2c.cpp lcd.cpp lcdWater.cpp

build-init: i2c.cpp lcd.cpp lcdInit.cpp
	g++ -std=c++0x -Wall -o LcdInit.bin i2c.cpp lcd.cpp lcdInit.cpp

build-temp: i2c.cpp lcd.cpp lcdTemp.cpp
	g++ -std=c++0x -Wall -o LcdTemp.bin i2c.cpp lcd.cpp lcdTemp.cpp

build-any: i2c.cpp lcd.cpp lcdAny.cpp
	g++ -std=c++0x -Wall -o LcdAny.bin i2c.cpp lcd.cpp lcdAny.cpp
