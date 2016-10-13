
// Draw a little "Duke ECE" screensaver to bounce around the display

#ifndef SCREENSAVER_h
#define SCREENSAVER_h

#include "ILI9341_t3.h"
#include "Adafruit_FT6206.h"
#include "Configuration.h"


class Screensaver {
  public:
    Screensaver(ILI9341_t3*, Adafruit_FT6206*);
    void drawMe(void);

  private:
    ILI9341_t3* ptr_tft;
    Adafruit_FT6206* ptr_ctp;
};

#endif // SCREENSAVER_h

