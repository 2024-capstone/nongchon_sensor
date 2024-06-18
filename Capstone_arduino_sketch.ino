
#include "Imu.h"
#include "Gps.hpp"
#include "Bluetooth.hpp"

int state;
std::string location;
bool init_flag;

void setup() {
  // put your setup code here, to run once:
  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif

  Serial.begin(9600);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately

  dmpSetup();
  gpsSetup();
  bluetoothSetup();

  // configure LED for output
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  init_flag = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  state = dmpLoop(); // bool 값 리턴 받고 (safe, warning)

  if (init_flag && state == SAFE)
  {
    init_flag = false;
  }

  if (state != ERROR)
  {
    if (!init_flag)
    {
      location = gpsLoop(); // if (warning)
      bluetoothLoop(location, state, init_flag); // 그대로 여기에 넣고 전송
    }
    else 
    {
      Serial.println("init_flag on!");
    }
  }
  else 
  {
    Serial.println("Error!");
  }
}
