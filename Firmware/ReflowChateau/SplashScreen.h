
// Draw the FJ logo upon startup

#ifndef SPLASHSCREEN_h
#define SPLASHSCREEN_h

#include "ILI9341_t3.h"
#include "Adafruit_FT6206.h"
#include "Configuration.h"


 // Array of points which comprise the FJ logo
static const uint8_t fj[]  = {8,   167,  1,    37,   35,   51,   38,   185,
                              1,   37,   103,  0,    136,  11,   35,   51,
                              38,  144,  37,   100,  72,   83,   72,   127,
                              35,  51,   136,  11,   134,  54,   37,   100,
                              72,  127,  72,   83,   105,  68,   104,  111,
                              38,  185,  38,   144,  104,  111,  103,  149};

class SplashScreen {  
  public:
    SplashScreen(int, int, ILI9341_t3*, Adafruit_FT6206*);
    void drawMe(void);

  private:
    int xLoc;
    int yLoc;
    ILI9341_t3* ptr_tft;
    Adafruit_FT6206* ptr_ctp;
};


#endif // SPLASHSCREEN_h

