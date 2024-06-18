#include <string>
#include "esp32-hal.h"
#include "Gps.hpp"

static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void gpsSetup()
{
  ss.begin(GPSBaud);

	Serial.println(F("DeviceExample.ino"));
	Serial.println(F("A simple demonstration of TinyGPSPlus with an attached GPS module"));
	Serial.print(F("Testing TinyGPSPlus library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
	Serial.println(F("by Mikal Hart"));
	Serial.println();
}

std::string gpsLoop()
{
  std::string gps_info;
  int r;

  // ###latitude:xxxx,longitude:$$$$###
  while (ss.available())
  {
    r = ss.read();
    // Serial.write(r);
    if (gps.encode(r))
    {
      // Serial.print(F("Location: "));
      if (gps.location.isValid())
      {
        gps_info = "###latitude:";
        gps_info += std::to_string(gps.location.lat());
        gps_info += ",";
        gps_info += "longtitude:";
        gps_info += std::to_string(gps.location.lng());
        gps_info += "###";
      }
      else
      {
        Serial.println(F("INVALID"));
        gps_info = "INVALID";
      }
    }
  }
  if (Serial.available())
    ss.write(Serial.read());

  return gps_info;
}

// std::string gpsLoop()
// {
//   std::string gps_info;

//   // This sketch displays information every time a new sentence is correctly encoded.
// 	while (ss.available() > 0) {
//     Serial.println("in ss.available()");
//     gps_info += "can available";
// 		if (gps.encode(ss.read())) {
// 			displayInfo();
//       Serial.println("can read!");
//       gps_info = std::to_string(gps.location.lat()) + "," + std::to_string(gps.location.lng());
      
//       break;
// 		}

//     if (millis() > 5000 && gps.charsProcessed() < 10)
//     {
//       Serial.println(F(", No GPS detected: check wiring."));
//       // while(true);
//       // delay(100);
//       gps_info += "No GPS detected: check wiring.\n";
// 	  }
// 	}

//   return gps_info;
// }

void displayInfo()
{
	Serial.print(F("Location: ")); 
	if (gps.location.isValid()) {
		Serial.print(gps.location.lat(), 6);
		Serial.print(F(","));
		Serial.print(gps.location.lng(), 6);
	} else {
		Serial.print(F("INVALID"));
	}

	Serial.print(F("  Date/Time: "));
	if (gps.date.isValid()) {
		Serial.print(gps.date.month());
		Serial.print(F("/"));
		Serial.print(gps.date.day());
		Serial.print(F("/"));
		Serial.print(gps.date.year());
	} else {
		Serial.print(F("INVALID"));
	}

	Serial.print(F(" "));
	if (gps.time.isValid()) {
		if (gps.time.hour() < 10) Serial.print(F("0"));
		Serial.print(gps.time.hour());
		Serial.print(F(":"));
		if (gps.time.minute() < 10) Serial.print(F("0"));
		Serial.print(gps.time.minute());
		Serial.print(F(":"));
		if (gps.time.second() < 10) Serial.print(F("0"));
		Serial.print(gps.time.second());
		Serial.print(F("."));
		if (gps.time.centisecond() < 10) Serial.print(F("0"));
		Serial.print(gps.time.centisecond());
	} else {
		Serial.print(F("INVALID"));
	}

	Serial.println();
}