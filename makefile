build-test: i2c.cpp i2cTest.cpp
	g++ -std=c++0x -Wall -o OutBin.bin i2c.cpp i2cTest.cpp

#build-bin: mcp3008Spi.h mcp3008Spi.cpp mcp3008SpiCh0.cpp
#	g++ -std=c++0x -Wall -o readSpiCh0mcp3008.bin mcp3008Spi.cpp mcp3008SpiCh0.cpp
