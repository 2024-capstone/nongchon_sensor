# ifndef GPS_HPP
# define GPS_HPP

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <string>

/*
   This sample sketch demonstrates the normal use of a TinyGPSPlus (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
 */

void displayInfo();
void gpsSetup();
std::string gpsLoop();

# endif