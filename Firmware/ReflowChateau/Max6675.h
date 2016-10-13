
// Slightly modified Adafruit's MAX6675 library
// https://github.com/adafruit/MAX6675-library

#ifndef MAX6675_h
#define MAX6675_h

#include "Arduino.h"


class MAX6675 {  
  public:
    MAX6675(int8_t SCLK, int8_t CS, int8_t MISO);
    float getTemperature(void);
  private:
    int8_t sclk, miso, cs;
    uint8_t spiRead(void);
};


#endif // MAX6675_h

