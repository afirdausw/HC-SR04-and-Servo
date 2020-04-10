#include <Wire.h>
#include <MechaQMC5883.h>
#include <Servo.h>

#define R_PIN1 2
#define L_PIN2 3
#define led_s 6
#define led_u 7

MechaQMC5883 qmc;
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

// Sensor 4
#define echoPin4 11
#define trigPin4 4

// Sensor 5
#define echoPin5 12
#define trigPin5 5

int maximumRange = 7;
long duration, distance;

int maximumRange2 = 7;
long duration2, distance2;

int maximumRange3 = 7;
long duration3, distance3;

int maximumRange4 = 8;
long duration4, distance4;

int maximumRange5 = 8;
long duration5, distance5;

// 1 Kanan, 2 Kiri
int belok = 1;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  R1.attach(R_PIN1);
  L2.attach(L_PIN2);

  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);
  pinMode(echoPin5, INPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(trigPin5, OUTPUT);

  // define lampu
  pinMode(led_s, OUTPUT);
  pinMode(led_u, OUTPUT);

  qmc.init();
}

void loop() {
  cekArah();

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

  digitalWrite(trigPin4, LOW); delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);

  digitalWrite(trigPin5, LOW); delayMicroseconds(2);
  digitalWrite(trigPin5, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin5, LOW);
  duration5 = pulseIn(echoPin5, HIGH);

  distance = duration / 58.2;
  distance2 = duration2 / 58.2;
  distance3 = duration3 / 58.2;
  distance4 = duration4 / 58.2;
  distance5 = duration5 / 58.2;

  Serial.print("Sensor 1 = "); Serial.print(distance); Serial.println(" cm");
  Serial.print("Sensor 2 = "); Serial.print(distance2); Serial.println(" cm");
  Serial.print("Sensor 3 = "); Serial.print(distance3); Serial.println(" cm");
  Serial.print("Sensor 4 = "); Serial.print(distance4); Serial.println(" cm");
  Serial.print("Sensor 5 = "); Serial.print(distance5); Serial.println(" cm");
  Serial.println("");


  if (distance == 0 && distance2 == 0 && distance3 == 0 && distance4 == 0 && distance5 == 0) {
    wheel_detach();
    delay(500);
  }
  else if (distance2 <= maximumRange2 && distance <= maximumRange && distance3 > maximumRange3) {
    wheel_detach();
    kiri();
  }
  else if (distance3 <= maximumRange3 && distance <= maximumRange && distance2 > maximumRange2) {
    wheel_detach();
    kanan();
  }
  else if (distance4 <= maximumRange4 && distance >= maximumRange && distance5 >= maximumRange5) {
    wheel_detach();
    kiriDikit();
  }
  else if (distance5 <= maximumRange5 && distance >= maximumRange && distance4 >= maximumRange4) {
    wheel_detach();
    kananDikit();
  }
  else if (distance <= maximumRange && distance4 <= maximumRange4 && distance5 <= maximumRange5 && distance2 >= maximumRange2 && distance3 >= maximumRange3) {
    if (belok == 1){
      Serial.println("\nNilai Ganjil, Belok Kanan\n\n");
      
      kanan();
      maju();
      delay(2000);
      wheel_detach();
      kanan();
      maju();
      
      belok = 2;
    }
    else {
      Serial.println("\nNilai Genap, Belok Kiri\n\n");
      kiri();
      maju();
      delay(2000);
      wheel_detach();
      kiri();
      maju();
      
      belok = 1;
    }
  }
  else if (distance4 <= maximumRange4 && distance <= maximumRange && distance5 >= maximumRange5 && distance2 >= maximumRange2 && distance3 >= maximumRange3) {
    wheel_detach();
    kiri();
    maju();
    delay(1100);
    wheel_detach();
    kanan();
    maju();
    delay(2400);
    kanan();
    maju();
    delay(1100);
    wheel_detach();
    
    R1.attach(R_PIN1);
    L2.attach(L_PIN2);
    R1.write(0);
    L2.write(0);
    delay(700);
  }
  else if (distance5 <= maximumRange5 && distance <= maximumRange && distance4 >= maximumRange4 && distance2 >= maximumRange2 && distance3 >= maximumRange3) {
    wheel_detach();
    kanan();
    maju();
    delay(1100);
    wheel_detach();
    kiri();
    maju();
    delay(2400);
    kiri();
    maju();
    delay(1100);
    wheel_detach();
    
    R1.attach(R_PIN1);
    L2.attach(L_PIN2);
    R1.write(180);
    L2.write(180);
    delay(700);
  }
  else if (distance >= maximumRange) {
    maju();
  }
  else {
    wheel_detach();
    delay(500);

    if (distance <= maximumRange && distance2 <= maximumRange2 && distance3 <= maximumRange3) {
      balik();
    }
    else {
      if (belok == 1){
        kanan();
        maju();
        delay(2000);
        wheel_detach();
        kanan();
        maju();
        
        Serial.println("Nilai Ganjil, Belok Kanan");
        belok = 2;
      }
      else {
        kiri();
        maju();
        delay(2000);
        wheel_detach();
        kiri();
        maju();
        
        Serial.println("Nilai Genap, Belok Kiri");
        belok = 1;
      }
    }
  }

  delay(200);
}

int cekArah() {
  int x, y, z;
  qmc.read(&x, &y, &z);

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

int kiriDikit() {
  R1.attach(R_PIN1);
  L2.attach(L_PIN2);
  Serial.println("Roda = Belok kiri sedikit");
  R1.write(0);
  L2.write(0);
  delay(450);
}

int kanan() {
  R1.attach(R_PIN1);
  L2.attach(L_PIN2);
  Serial.println("Roda = Belok kanan");
  R1.write(180);
  L2.write(180);
  delay(900);
}

int kananDikit() {
  R1.attach(R_PIN1);
  L2.attach(L_PIN2);
  Serial.println("Roda = Belok kanan sedikit");
  R1.write(180);
  L2.write(180);
  delay(450);
}

int balik() {
  Serial.println("Roda = Stop dan memutar");
  R1.detach();
  L2.detach();
  delay(200);
  R1.attach(R_PIN1);
  L2.attach(L_PIN2);
  R1.write(180);
  L2.write(180);
  delay(1800);
}

int wheel_detach() {
  R1.detach();
  L2.detach();
}
