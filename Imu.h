# ifndef IMU_HPP
# define IMU_HPP

#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif



#define OUTPUT_READABLE_YAWPITCHROLL
#define INTERRUPT_PIN 12  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 2 // (Arduino is 13, Teensy is 11, Teensy++ is 6)

#define ERROR 0
#define WARNING 1
#define SAFE 2


void dmpSetup();
int dmpLoop();

# endif