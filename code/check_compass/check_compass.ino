#include <Wire.h>
#include <MechaQMC5883.h>

#define led_s 6
#define led_u 7

MechaQMC5883 qmc;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(led_s, OUTPUT);
  pinMode(led_u, OUTPUT);
  qmc.init();
}

void loop() {
  int x, y, z;
  qmc.read(&x, &y, &z);

  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.print(z);
  Serial.println();

  if (y > 1500 && y < 1900 && x < 600) {
    digitalWrite(led_s, HIGH);
    Serial.println("SELATAN");
  } else {
    digitalWrite(led_s, LOW);
  }

  if (x > 600 && x < 1250 && y < 0) {
    digitalWrite(led_u, HIGH);
    Serial.println("UTARA");
  } else {
    digitalWrite(led_u, LOW);
  }
  delay(500);
}

