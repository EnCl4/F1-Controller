#include <Arduino.h>
#include <AS5600.h>

#define acelerador 14
#define freio 4
#define angulacao 15
#define gearUp 26
#define gearDown 34
//#define cluch 09
//#define DRS 10

AS5600L as5600;
float ang = 0;
bool flagA = false;
bool flagB = false;
void IRAM_ATTR handleA() { flagA = true; }
void IRAM_ATTR handleB() { flagB = true; }

void setup() {
  Serial.begin(115200);
  pinMode(angulacao, INPUT);
  pinMode(acelerador, INPUT);
  pinMode(freio, INPUT);
  pinMode(gearUp, INPUT);
  pinMode(gearDown, INPUT);
  Wire.begin();
  as5600.setAddress(0x36);
  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  //  default, just be explicit.

  //attachInterrupt(gearUp, handleA, RISING);
  //attachInterrupt(gearDown, handleB, RISING);
  ang = analogRead(angulacao);
  
}

void loop() {
  
  //Serial.println(ang);
  //.println(">r:" + String(analogRead(angulacao)));
  Serial.println(">a:" + String(analogRead(acelerador)));
  Serial.println(">b:" + String(analogRead(freio)));
  Serial.println(">gup:" + String(analogRead(gearUp)));
  Serial.println(">gud:" + String(analogRead(gearDown)));

  // Serial.print(">GetDirection:");
  // Serial.println(as5600.getDirection());
  // Serial.print(">ReadAngle:");
  // Serial.println(as5600.readAngle());
  Serial.print(">r:");
  Serial.println(as5600.rawAngle() * AS5600_RAW_TO_DEGREES);
}


// #include <Wire.h>

// // Set I2C bus to use: Wire, Wire1, etc.
// #define WIRE Wire

// void setup() {
//   WIRE.begin();

//   Serial.begin(9600);
//   while (!Serial)
//      delay(10);
//   Serial.println("\nI2C Scanner");
// }


// void loop() {
//   byte error, address;
//   int nDevices;

//   Serial.println("Scanning...");

//   nDevices = 0;
//   for(address = 1; address < 127; address++ )
//   {
//     // The i2c_scanner uses the return value of
//     // the Write.endTransmisstion to see if
//     // a device did acknowledge to the address.
//     WIRE.beginTransmission(address);
//     error = WIRE.endTransmission();

//     if (error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if (address<16)
//         Serial.print("0");
//       Serial.print(address,HEX);
//       Serial.println("  !");

//       nDevices++;
//     }
//     else if (error==4)
//     {
//       Serial.print("Unknown error at address 0x");
//       if (address<16)
//         Serial.print("0");
//       Serial.println(address,HEX);
//     }
//   }
//   if (nDevices == 0)
//     Serial.println("No I2C devices found\n");
//   else
//     Serial.println("done\n");

//   delay(5000);           // wait 5 seconds for next scan
// }