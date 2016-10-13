
// Draw and update the buttons on the LCD

#ifndef BUTTON_h
#define BUTTON_h

#include "ILI9341_t3.h"
#include "Adafruit_FT6206.h"
#include "Configuration.h"

class Button {  
  public:
    Button(void);
    void set(String, int, int, uint8_t, uint8_t, uint8_t, 
             ILI9341_t3*, Adafruit_FT6206*);
    void drawMe(void);
    void setActive(boolean);
    boolean updateMe(void);

  private:
    String name;
    int xLoc;
    int yLoc;
    uint8_t textSize;
    uint8_t width;
    uint8_t height;
    ILI9341_t3* ptr_tft;
    Adafruit_FT6206* ptr_ctp;
    
    boolean over;
    boolean active;
    boolean prevOver;
    
    void isOver(int, int);
};

#endif // BUTTON_h

