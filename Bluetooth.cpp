#include "Bluetooth.hpp"

//#define USE_PIN // Uncomment this to use PIN during pairing. The pin is specified on the line below
const char *pin = "1234"; // Change this to more secure PIN.

String device_name = "8조아두이노";

BluetoothSerial SerialBT;

void bluetoothSetup()
{
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  //Serial.printf("The device with name \"%s\" and MAC address %s is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str(), SerialBT.getMacString()); // Use this after the MAC method is implemented
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif
}

void bluetoothLoop(std::string& location, int state, bool& init_flag)
{
  // size_t size;
  const uint8_t *buffer;
  char          data;

  buffer = reinterpret_cast<const uint8_t*>(&location[0]);
  if (state == WARNING && location.size() != 0)
  {
    SerialBT.write(buffer, location.size());
    SerialBT.write('\n');
  }
  delay(200);
  
  if (SerialBT.available())
  {
    data = SerialBT.read();
    Serial.write(data); // BT To serial monitor

    if (data == 'E')
      init_flag = true;
  }
}