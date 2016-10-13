
// Slightly modified Arduino PID library
// https://github.com/br3ttb/Arduino-PID-Library/

#ifndef PID_h
#define PID_h

#include "Arduino.h"
#include "Max6675.h"


class PID {
  public:
    #define DIRECT 0
    #define REVERSE 1
    PID(float, float, float, int);
    float updateMe(void);
    float getTemperature(void);
    void setSetpoint(float);
  
  private:
    void compute(void);
    void setOutputLimits(float, float);
    void setControllerDirection(int);
    void setTunings(float, float, float); 
    void setSampleTime(int);

    MAX6675 thermocouple;
  
    float kp;  // proportional
    float ki;  // integral
    float kd;  // derivative
    int controllerDirection;
    
    float myInput;  // pointer to the input           
    float myOutput; // pointer to the output
    float mySetpoint;  // pointer to the setpoint
    
    float iTerm, lastInput;
    float outMin, outMax;
    
    unsigned long sampleTime;
    unsigned long windowStartTime;
};


#endif

