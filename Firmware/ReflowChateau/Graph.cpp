
#ifndef GRAPH_cpp
#define GRAPH_cpp

#include "Graph.h"
#include "Arduino.h"


Graph::Graph(void) {
}


void Graph::set(float startTemp, float preheat, float soakTemp, float soakTime, float rampUp, 
                float peakTemp, float peakTime, ILI9341_t3* ptr_tft, Adafruit_FT6206* ptr_ctp) {
  
  this->ptr_tft = ptr_tft;
  this->ptr_ctp = ptr_ctp;
  
  points[0] = (Point) {0, startTemp};
  points[1] = (Point) {(soakTemp-startTemp)/preheat, soakTemp};
  points[2] = (Point) {points[1].x + soakTime, soakTemp};
  points[3] = (Point) {points[2].x + (peakTemp-soakTemp)/rampUp, peakTemp};
  points[4] = (Point) {points[3].x + peakTime, peakTemp};
  points[5] = (Point) {points[4].x + (startTemp-peakTemp)/(-2*preheat), 25}; // 25 C is roughly room temp
  lastTime = -1;
  lastTemp = -1;
}


void Graph::drawLines(void){
  uint16_t hLineColor = ptr_tft->color565(127, 127, 127);
  for (int i = 0; i < 6; i++){
    ptr_tft->drawFastHLine(0, 70+50*i, 240, hLineColor);
  } 
  uint16_t setpointLineColor = ptr_tft->color565(100, 122, 255);
  for (int i = 0; i < 5; i++){
    Point p0 = pointToDisplay(points[i]);
    Point p1 = pointToDisplay(points[i+1]);
    ptr_tft->drawLine(p0.x, p0.y, p1.x, p1.y, setpointLineColor);
  }    
}


float Graph::getSetpoint(float time){
  for (int i = 0; i < 5; i++){
    if (time >= points[i].x && time < points[i+1].x){
      return floatMap(time, points[i].x, points[i+1].x, points[i].y, points[i+1].y);
    }
  }
  return 0;
}


void Graph::printValues(float time, float temp){
  ptr_tft->setTextSize(2);    
  if (lastTime == -1){
    ptr_tft->setTextColor(ILI9341_RED);  
    ptr_tft->setCursor(115, 17);
    ptr_tft->print("Time:");
    ptr_tft->setCursor(115, 40);
    ptr_tft->print("Temp:");
  }
  else {
    ptr_tft->setTextColor(ILI9341_BLACK);  
    ptr_tft->setCursor(180, 17);
    ptr_tft->print((int) lastTime);
    ptr_tft->setCursor(180, 40);
    ptr_tft->print((int) lastTemp);
  } 
  ptr_tft->setTextColor(ILI9341_RED);  
  ptr_tft->setCursor(180, 17);
  ptr_tft->print((int) time);
  ptr_tft->setCursor(180, 40);
  ptr_tft->print((int) temp);
  lastTime = time;
  lastTemp = temp;
}


float Graph::floatMap(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


float Graph::plotLine(float time, float temp){
  if (lastTime != -1){
    ptr_tft->drawLine(lastTime/2, -lastTemp+320, time/2, -temp+320, ILI9341_RED);
  }
  if (time > (points[5].x + points[4].x)/2){
    openDoor();
  }
}


void Graph::openDoor(){
  ptr_tft->setTextSize(2);     
  ptr_tft->setTextColor(ILI9341_WHITE);  
  ptr_tft->setCursor(36, 300);
  ptr_tft->print("Open the door!");
}


Point Graph::pointToDisplay(Point display){ // convert real point to point for display
  return (Point) {display.x/2, -display.y+320};
}


#endif // GRAPH_cpp

