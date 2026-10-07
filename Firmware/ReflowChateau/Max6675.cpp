
// Slightly modified Adafruit's MAX6675 library
// https://github.com/adafruit/MAX6675-library

#ifndef MAX6675_cpp
#define MAX6675_cpp

#include "Max6675.h"


/* Constructor- configure pins */
MAX6675::MAX6675(int8_t SCLK, int8_t CS, int8_t MISO) {
  sclk = SCLK;
  cs = CS;
  miso = MISO;
  pinMode(cs, OUTPUT);
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);
  digitalWriteFast(cs, HIGH);
}


/* Return the temperature in degrees celsius */
float MAX6675::getTemperature(void){
  uint16_t v;
  float lastTemp;
  digitalWriteFast(cs, LOW);
  v = spiRead();
  v <<= 8;
  v |= spiRead();
  digitalWriteFast(cs, HIGH);
  if (v & 0x4) {  
    // No thermocouple attached / open circuit. Returning a fixed sentinel
    // (previously 1000) fed bogus, wildly out-of-range values straight into
    // the graph/PID math. Fall back to the last known-good reading instead,
    // or 0 if we've never had a good reading yet.
    return lastTemp;
  }
  v >>= 3;
  lastTemp = v*0.25;  // convert from raw to celsius
  return lastTemp;
}


/* Determine the next byte on the SPI bus */
uint8_t MAX6675::spiRead(void){
  int i;
  uint8_t d = 0;
  for (i=7; i>=0; i--) {
    digitalWriteFast(sclk, LOW);
    if (digitalReadFast(miso)) {
      d |= (1 << i);
    }
    digitalWriteFast(sclk, HIGH);
  }
  return d;
}


#endif // MAX6675_cpp

