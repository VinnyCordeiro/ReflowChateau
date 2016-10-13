
#ifndef SPLASHSCREEN_cpp
#define SPLASHSCREEN_cpp

#include "SplashScreen.h"

SplashScreen::SplashScreen(int xLoc, int yLoc, ILI9341_t3 *ptr_tft, 
                           Adafruit_FT6206 *ptr_ctp) {
  this->xLoc = xLoc;
  this->yLoc = yLoc;
  this->ptr_tft = ptr_tft;
  this->ptr_ctp = ptr_ctp;
}


void SplashScreen::drawMe(void){
  ptr_tft->fillScreen(ILI9341_BLACK);  

  int16_t color0 = ptr_tft->color565(140, 143, 138);
  int16_t color1 = ptr_tft->color565(204, 204, 204);

  ptr_tft->setTextColor(color1);  
  ptr_tft->setTextSize(4);  
  ptr_tft->setCursor(52, 15);
  ptr_tft->println(F("Reflow"));
  ptr_tft->setTextSize(3);  
  ptr_tft->setCursor(60, 48);
  ptr_tft->println(F("Chateau"));

  for (int i = 0; i < 48; i+=8){
    int16_t color;
    // select the color according to the face
    // dark grey
    if (i/8 <= 2){
     color = color0;
    }    
    else {
      color = color1;
    }
    ptr_tft->fillTriangle(fj[i+0]+xLoc, fj[i+1]+yLoc, fj[i+2]+xLoc,
                          fj[i+3]+yLoc, fj[i+4]+xLoc, fj[i+5]+yLoc, color);
    ptr_tft->fillTriangle(fj[i+0]+xLoc, fj[i+1]+yLoc, fj[i+4]+xLoc,
                          fj[i+5]+yLoc, fj[i+6]+xLoc, fj[i+7]+yLoc, color);
  }
  
  ptr_tft->setTextColor(color0);  
  ptr_tft->setTextSize(2);  
  ptr_tft->setCursor(xLoc+4, yLoc+200);
  ptr_tft->println(F("willfj.com"));
  ptr_tft->setTextSize(1);
  ptr_tft->setCursor(xLoc+13, yLoc+220);
  ptr_tft->println(F("touch to continue"));
  
  while (!ptr_ctp->touched());
}


#endif // SPLASHSCREEN_cpp

