
// Slightly modified Arduino PID library
// https://github.com/br3ttb/Arduino-PID-Library/

#ifndef PID_cpp
#define PID_cpp

#include "Arduino.h"
#include "PID.h"
#include "Configuration.h"


PID::PID(float kp, float ki, float kd, int controllerDirection)
:thermocouple(THERMOCOUPLE_SCLK, THERMOCOUPLE_CS, THERMOCOUPLE_MISO){
  PID::setOutputLimits(0, TEMP_UPDATE_INTERVAL);
  sampleTime = TEMP_UPDATE_INTERVAL;
  PID::setControllerDirection(controllerDirection);
  PID::setTunings(kp, ki, kd);
  windowStartTime = 0;
  pinMode(BOTTOM_ELEMENT, OUTPUT);
  pinMode(TOP_ELEMENT, OUTPUT);
}


/* Update the output to the PID */
void PID::compute(void){
  // Compute the error variables
  float error = mySetpoint - myInput;
  iTerm += (ki * error);
  iTerm = constrain(iTerm, outMin, outMax); 
  float dInput = (myInput - lastInput);
  // compute the output
  myOutput = kp * error + iTerm- kd * dInput;
  myOutput = constrain(myOutput, outMin, outMax);
  lastInput = myInput;  // store the input for the next call to compute
}


float PID::getTemperature(void){
  if (millis() - windowStartTime >= sampleTime){
    myInput = thermocouple.getTemperature();  
    PID::compute();
    windowStartTime = millis();
  }
  return myInput; 
}


float PID::updateMe(void){
  // turn on the heater if it is time during the window
  digitalWrite(BOTTOM_ELEMENT, myOutput >= millis() - windowStartTime);
  digitalWrite(TOP_ELEMENT, myOutput >= millis() - windowStartTime);
  // update the temperature and output every sampleTime milliseconds
  if (millis() - windowStartTime >= sampleTime){
    myInput = thermocouple.getTemperature();  
    PID::compute();
    windowStartTime = millis();
  } 
  return myInput;
}


void PID::setSetpoint(float newSetpoint){
  mySetpoint = newSetpoint;
}


void PID::setTunings(float p, float i, float d){
  if (p < 0 || i < 0 || d < 0){
    return;
  }
  float sampleTimeInSec = ((float)sampleTime)/1000;  
  kp = p;
  ki = i*sampleTimeInSec;
  kd = d/sampleTimeInSec;
  if(controllerDirection == REVERSE){
    kp*=-1;
    ki*=-1;
    kd*=-1;
  }
}


void PID::setSampleTime(int newSampleTime){
  if (newSampleTime <= 0){
    return; 
  }
  float ratio  = (float) newSampleTime / (float) sampleTime;
  ki*=ratio;
  kd/=ratio;
  sampleTime = (unsigned long) newSampleTime;
}


void PID::setOutputLimits(float newMin, float newMax){
  if(newMin >= newMax){
    return;
  }
  outMin = newMin;
  outMax = newMax;
  myOutput = constrain(myOutput, outMin, outMax);
  iTerm = constrain(iTerm, outMin, outMax);
}


void PID::setControllerDirection(int newDirection){
   if(newDirection !=controllerDirection){
      kp *= -1;
      ki *= -1;
      kd *= -1;
   }   
   controllerDirection = newDirection;
}

#endif

