#include <string>
#include "i2c.h"

/**
 * This is the LCD control class, using 4bit mode
 * There is always one Byte sent down on i2c, containing data or commands in the upper 4bits.
 * The lower 4bit are used for D3=backlight, D2=Enable, D1=Read/Write and D0=DataInstructionSet(RS)
 * One data or command Byte is therefore split in two writes (first upper 4bits, then lower 4bits)
 */

class LCD {
  public:
    LCD(int addr, bool doInit =true);
    
  private:
  
    Pi2c i2c;
    bool isBacklightOn;

    /**
     * Init the diplay, reset function for power up, set 4bit interface
     */
    int init();

    /**
     * Set enable pulse with right timing
     */
    int strobe(char data);

    /**
     * Write data char to i2c bus
     */
    int write(char data);

    /**
     * Writes upper 4bits (lower 4bits reserved for controls)
     */
    int writeUpperFourBits(char data, char mode =0);

    /**
     * Writes lower 4bits
     */
    int writeLowerFourBits(char data, char mode =0);

    /**
     * Write one Byte in two steps (upper and lower 4bits)
     */
    int writeByte(char data, char mode =0);
    
  public:
    /**
     * Switch backlingt on
     */
    int backlightOn();

    /**
     * Switch backlingt off
     */
    int backlightOff();

    /**
     * Write string to display (if too long, tail is cut off)
     * line = 1 (upper line), line = 2 (lower line)
     */
    int display(const std::string& data, unsigned int line);

    /**
     * Clear display
     */
    int clear();
};
