#include <Arduino.h> 
#include <Wire.h>

#define P(x)   Serial.print(x)
#define PL(x)  Serial.println(x)
#define PV(x)  P(#x); P("="); P(x)
#define PVL(x) P(#x); P("="); PL(x)

#define SDA D2  // D3
#define SCL D1 // D4

void setup() {
  Wire.begin(SDA, SCL);
 
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor

  PL("\nI2C Scanner");
}

void scan() {
  byte error, address;
  int nDevices;
 
  PL("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    switch (error) {
      case 0 :
        Serial.printf("I2C device found at address 0x%2X(hex) %d(dec)\n",address,address);
        nDevices++;
        break;
      case 4 :
        Serial.printf("Unknown I2C error at address 0x%2X(hex) %d(dec)\n",address,address);
        break;
      default :
 //       Serial.printf("Unknown I2C error %d at address 0x%2X(hex) %d(dec)\n",error,address,address);
        break;
    }
  }
  
  if (nDevices == 0)
    Serial.printf("%ld) No I2C devices found\n", millis()/1000);
  else
    PL("Finished\n");
}

void loop() {
  scan();
  delay(5000);           // wait 5 seconds for next scan
}
