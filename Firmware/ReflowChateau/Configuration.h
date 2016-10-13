
// Define the pin numbers and other constants

#ifndef CONFIGURATION_h
#define CONFIGURATION_h

/***************************************************************************
 *                              PID Behavior                               *
 ***************************************************************************/
#define SCREEN_SAVER_LIMIT 30000 // Turn on the 

/***************************************************************************
 *                              PID Behavior                               *
 ***************************************************************************/
#define TEMP_UPDATE_INTERVAL 200 // The interval between heater updates, in milliseconds.
#define TEMP_PID_Kp 25.0   // (P)roportional gain
#define TEMP_PID_Ki 8.0   // (I)ntegral gain
#define TEMP_PID_Kd 80.0   // (D)erivative gain

/***************************************************************************
 *                        Location of the F-J Logo                         *
 ***************************************************************************/
#define FJ_X 55
#define FJ_Y 80

/***************************************************************************
 *                           Store 2D Points                               *
 ***************************************************************************/
struct Point {
  float x;
  float y;
};

/***************************************************************************
 *                                 Pins                                    *
 ***************************************************************************/
#define THERMOCOUPLE_SCLK 2
#define THERMOCOUPLE_CS 3
#define THERMOCOUPLE_MISO 4
#define BOTTOM_ELEMENT 6
#define TOP_ELEMENT 7
#define TFT_DC 9
#define TFT_CS 10
   
#endif // CONFIGURATION_h

