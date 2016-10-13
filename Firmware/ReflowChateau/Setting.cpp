
#ifndef SETTING_cpp
#define SETTING_cpp

#include "Setting.h"

Setting::Setting(String setting, String units, float value, float minimum, float maximum,
float increment, int yLoc, ILI9341_t3 *ptr_tft, Adafruit_FT6206 *ptr_ctp) {
  this->setting = setting;
  this->units = units;
  this->value = value;
  this->maximum = maximum;
  this->minimum = minimum;
  this->increment = increment;
  this->yLoc = yLoc;
  this->ptr_tft = ptr_tft;
  this->ptr_ctp = ptr_ctp;
  
  boxColor = ptr_tft->color565(200, 200, 200);

  decrease = Button();
  increase = Button();
  decrease.set("<", 130, yLoc+3, 50, 36, 0, ptr_tft, ptr_ctp);
  increase.set(">", 185, yLoc+3, 50, 36, 0, ptr_tft, ptr_ctp);

  drawn = false;  
}

void Setting::drawMe(void){
  ptr_tft->fillRoundRect(0, yLoc, 240, 42, 4, boxColor);

  ptr_tft->setCursor(10, yLoc+4);
  ptr_tft->setTextColor(ILI9341_BLACK);
  ptr_tft->setTextSize(2);
  ptr_tft->println(setting);
  
  drawValue(ILI9341_RED);

  increase.drawMe();
  decrease.drawMe();
}



void Setting::drawValue(uint16_t color){
  ptr_tft->setTextColor(color);
  ptr_tft->setTextSize(2);
  ptr_tft->setCursor(10 , yLoc+23);
  if (increment < 0.1){
    ptr_tft->print(value);
  }
  else {
    ptr_tft->print((int) value);
  }

  ptr_tft->println(" " + units);
}


void Setting::updateMe(void){
  if (increase.updateMe()){
    if (areNearlyEqual(value, minimum)){
      decrease.setActive(true);
      decrease.drawMe();  
    }
    
    drawValue(boxColor);
    value += increment;
    drawValue(ILI9341_RED);
    
    if (areNearlyEqual(value, maximum)){
      increase.setActive(false);
      increase.drawMe();  
    }
  }
  
  else if (decrease.updateMe()){
    if (areNearlyEqual(value, maximum)){
      increase.setActive(true);
      increase.drawMe();  
    }
    
    drawValue(boxColor);
    value -= increment;
    drawValue(ILI9341_RED);
    
    if (areNearlyEqual(value, minimum)){
      decrease.setActive(false);
      decrease.drawMe();  
    }  
  }
  
  if (!drawn){
    drawMe();
    drawn = true;
  }
}

boolean Setting::areNearlyEqual(float a, float b){
  if (a > b-0.0001 && a < b+0.0001){
    return true;
  }
  return false;
}

float Setting::getValue(void){
  return value; 
}


#endif // SETTING_cpp

