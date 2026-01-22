#include <Wire.h>
#include <SPI.h>
#include <RF24.h>
#include <MPU6050.h>

// NRF24L01 pins
RF24 radio(7, 8);   // CE = D7, CSN = D8

// MPU6050 object
MPU6050 mpu;

void setup() {
  Wire.begin();
  mpu.initialize();

  radio.begin();
  radio.setChannel(108);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(false);
  radio.disableCRC();

  radio.openWritingPipe(0xE8E8F0F0E1LL);
  radio.stopListening();
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  char cmd = 'S';   // default STOP

  // ===== CORRECTED GESTURE LOGIC =====
  // Your MPU orientation:
  // X-axis → Forward / Backward
  // Y-axis → Left / Right

  if (ax >  6000)        cmd = 'B';   // backward
  else if (ax < -6000)   cmd = 'F';   // forward
  else if (ay >  6000)   cmd = 'L';   // left
  else if (ay < -6000)   cmd = 'R';   // right
  else                   cmd = 'S';   // stop
  // ==================================

  radio.write(&cmd, sizeof(cmd));
  delay(100);
}
