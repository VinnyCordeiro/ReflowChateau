
// Setting class which contains buttons to increment or decremement parameters of the reflow profile

#ifndef SETTING_h
#define SETTING_h

#include "ILI9341_t3.h"
#include "Adafruit_FT6206.h"
#include "Configuration.h"
#include "Button.h"


class Setting {  
  public:
    Setting(String, String, float, float, float, float, 
            int, ILI9341_t3*, Adafruit_FT6206*);
    void updateMe(void);
    void drawMe(void);
    float getValue(void);

  private:
    String setting;
    String units;
    float value;
    float maximum;
    float minimum;
    float increment;
    int yLoc;
    
    Button increase;
    Button decrease;
    
    uint8_t width;
    uint8_t height;
    
    uint16_t boxColor;
    
    ILI9341_t3* ptr_tft;
    Adafruit_FT6206* ptr_ctp;
    
    boolean drawn;
    void drawValue(uint16_t);
    boolean areNearlyEqual(float, float);
};


#endif // SETTING_h

