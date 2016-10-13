
#ifndef BUTTON_cpp
#define BUTTON_cpp

#include "Button.h"


Button::Button(void) {
  over = false;
  prevOver = false;
  active = true;
}


void Button::set(String name, int xLoc, int yLoc, uint8_t width, uint8_t height, 
               uint8_t textSize, ILI9341_t3* ptr_tft, Adafruit_FT6206* ptr_ctp) {
  this->name = name;
  this->xLoc = xLoc;
  this->yLoc = yLoc;
  this->width = width;
  this->height = height;
  this->textSize = textSize;
  this->ptr_tft = ptr_tft;
  this->ptr_ctp = ptr_ctp;
}


void Button::drawMe(void){  
  uint16_t color;
  if (active){
    if (over){
      color =  ptr_tft->color565(160, 160, 160);
    }
    else {
      color = ptr_tft->color565(130, 130, 130);
    }
  }
  else{
    color =  ptr_tft->color565(180, 180, 180);
  }
  ptr_tft->fillRoundRect(xLoc, yLoc, width, height, 4, color);
  
  if (active){
    if (name.equals(">")){
      ptr_tft->fillTriangle(xLoc+width/3, yLoc+height/4, xLoc+width/3, yLoc+height*3/4, 
                            xLoc+width*2/3, yLoc+height/2, ILI9341_BLACK);
    }
    else if (name.equals("<")){
      ptr_tft->fillTriangle(xLoc+width*2/3, yLoc+height/4, xLoc+width*2/3, yLoc+height*3/4, 
                            xLoc+width*1/3, yLoc+height/2, ILI9341_BLACK);
    }
    else {
      ptr_tft->setTextSize(textSize);
      ptr_tft->setCursor(xLoc+(width-(5.65*textSize)*name.length())/2, yLoc+(height-(7*textSize))/2);
      ptr_tft->setTextColor(ILI9341_BLACK);
      ptr_tft->println(name);
    }
  }
}


void Button::setActive(boolean newActive){
  if (active != newActive){
    active = newActive;
    drawMe(); 
  }
}  


boolean Button::updateMe(void){
  if (!active){
    return false;
  }
  boolean pressed = false;
  boolean touched = ptr_ctp->touched();
  if (touched){
    TS_Point p = ptr_ctp->getPoint();
    p.x = map(p.x, 0, 240, 240, 0);
    p.y = map(p.y, 0, 320, 320, 0);
    isOver(p.x, p.y);
  }
  if (prevOver){
    if (!touched && over){
      over = false;
      drawMe();
      pressed = true;
    }
    else if (touched && !over){
      drawMe();
    }
  }
  prevOver = over;
  return pressed;
}


void Button::isOver(int x, int y){
  if (x >= xLoc && x <= xLoc+width && y >= yLoc && y <= yLoc+height){
    if (!over){
      over = true;
      drawMe();
    }
  }
  else{
    over = false; 
  }
}

#endif // BUTTON_cpp

