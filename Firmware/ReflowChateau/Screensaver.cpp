
#ifndef SCREENSAVER_cpp
#define SCREENSAVER_cpp

#include "Screensaver.h"
#include "Arduino.h"


Screensaver::Screensaver(ILI9341_t3 *ptr_tft, Adafruit_FT6206 *ptr_ctp) {
  this->ptr_tft = ptr_tft;
  this->ptr_ctp = ptr_ctp;
}


void Screensaver::drawMe(void){
  ptr_tft->fillScreen(ILI9341_BLACK);
  
  int x = 120;
  int y = 160;
  int dx = (int) random(2, 6);
  int dy = (int) random(2, 6);  
  ptr_tft->setTextSize(1);    

  while (!ptr_ctp->touched()){
    x += dx;
    y += dy;
    ptr_tft->setCursor(x, y);
    ptr_tft->setTextColor(ILI9341_BLUE);
    ptr_tft->println("Duke ECE");
    if (x <= 1 || x >= 190){
      dx *= -1; 
    }
    if (y <= 1 || y >= 310){
      dy *= -1; 
    }    
    delay(30);  
    ptr_tft->fillRect(x, y, 48, 7, ILI9341_BLACK);
  }
}

#endif // SCREENSAVER_cpp

