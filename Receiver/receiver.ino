#include <SPI.h>
#include <RF24.h>

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENA 9
#define ENB 10

RF24 radio(7, 8);   // CE = D7, CSN = D8

unsigned long lastTime = 0;
char cmd = 'S';

void stopM() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  analogWrite(ENA, 160);
  analogWrite(ENB, 160);

  radio.begin();
  radio.setChannel(108);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(false);
  radio.disableCRC();

  radio.openReadingPipe(0, 0xE8E8F0F0E1LL);
  radio.startListening();

  stopM();
}

void loop() {
  // ---------- receive command ----------
  if (radio.available()) {
    radio.read(&cmd, sizeof(cmd));
    lastTime = millis();
  }

  // ---------- failsafe (signal lost) ----------
  if (millis() - lastTime > 500) {
    stopM();
    return;
  }

  // ---------- motor control ----------
  if (cmd == 'F') {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  }
  else if (cmd == 'B') {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  }
  else if (cmd == 'L') {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  }
  else if (cmd == 'R') {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  }
  else {
    stopM();
  }
}
