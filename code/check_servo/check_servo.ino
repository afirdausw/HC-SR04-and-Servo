#include <Servo.h>

#define R_PIN1 2
#define L_PIN2 3

Servo R1, L2;

// Sensor 1
#define echoPin1 8
#define trigPin1 A0

// Sensor 2
#define echoPin2 9
#define trigPin2 A1

// Sensor 3
#define echoPin3 10
#define trigPin3 A2

int maximumRange = 12;
int minimumRange = 0;
long duration, distance;

int maximumRange2 = 12;
int minimumRange2 = 0;
long duration2, distance2;

int maximumRange3 = 12;
int minimumRange3 = 0;
long duration3, distance3;

void setup() {
  Serial.begin(9600);

  R1.attach(R_PIN1);
  L2.attach(L_PIN2);

  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);
}

void loop() {
  digitalWrite(trigPin1, LOW); delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);

  digitalWrite(trigPin2, LOW); delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);

  digitalWrite(trigPin3, LOW); delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);

  distance = duration / 58.2;
  distance2 = duration2 / 58.2;
  distance3 = duration3 / 58.2;

  Serial.print("Sensor 1 = "); Serial.print(distance); Serial.println(" cm");
  Serial.print("Sensor 2 = "); Serial.print(distance2); Serial.println(" cm");
  Serial.print("Sensor 3 = "); Serial.print(distance3); Serial.println(" cm");
  Serial.println("");


  if (distance == 0 && distance2 == 0 && distance3 == 0) {
    wheel_detach();
    delay(500);
  }
  else if (distance >= maximumRange) {
    maju();
  }
  else {
    wheel_detach();
    delay(500);

    if (distance2 <= maximumRange2) {
      wheel_detach();
      kiri();
    }
    else if (distance3 <= maximumRange3) {
      wheel_detach();
      kanan();
    }
    else if (distance <= maximumRange && distance2 <= maximumRange2 && distance3 <= maximumRange3) {
      wheel_detach();
      balik();
    }
    else {
      wheel_detach();
      kanan();
      //mundur();
    }
  }
  
  delay(200);

}

int maju() {
  R1.attach(R_PIN1);
  L2.attach(L_PIN2);

  Serial.println("Roda = Maju");
  R1.write(0);
  L2.write(180);
}

int mundur() {
  R1.attach(R_PIN1);
  L2.attach(L_PIN2);

  Serial.println("Roda = Mundur");

  R1.write(180);
  L2.write(0);

  delay(1000);
}

int kiri() {
  R1.attach(R_PIN1);
  L2.attach(L_PIN2);

  Serial.println("Roda = Belok kiri");

  R1.write(0);
  L2.write(0);

  delay(900);
}

int kanan() {
  R1.attach(R_PIN1);
  L2.attach(L_PIN2);

  Serial.println("Roda = Belok kanan");

  R1.write(180);
  L2.write(180);

  delay(900);
}

int balik() {
  Serial.println("Roda = Stop dan memutar");
  R1.detach();
  L2.detach();

  delay(200);

  R1.attach(R_PIN1);
  R1.write(180);
  delay(1800);
}

int wheel_detach() {
  R1.detach();
  L2.detach();
}
