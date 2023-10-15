#include <Servo.h>
Servo servo;

//wheel
#define motorLeftFront 24
#define motorLeftBack 22
#define motorRightFront 26
#define motorRightBack 28

//servo motor
#define servoPin 30

//ultrasonic
#define trigPin 32
#define echoPin 34
long duration;
int distance;


//flame
int flameLed = 42;
#define flamePin 36
#define buzzerPin 38
int flameDetection;


//smoke
int smokeLed = 40;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A0;
int sensorThres = 300;

//water
int waterLed = 44;
#define waterPin 46
const int RELAY_PIN = A1;

void setup() { 
  servo.attach(servoPin);
  servo.write(0);
  Serial.begin(9600);


  pinMode(motorLeftFront,OUTPUT);
  pinMode(motorLeftBack,OUTPUT);
  pinMode(motorRightFront,OUTPUT);
  pinMode(motorRightFront,OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(flamePin,INPUT);
  pinMode(flameLed, OUTPUT);
  pinMode(buzzerPin,OUTPUT);

  pinMode(smokeLed, OUTPUT);
  pinMode(smokeA0, INPUT);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(waterLed, OUTPUT);
  pinMode(waterPin, INPUT);

}

void loop() {
  //ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");

  if(distance >8)
  {
    analogWrite(motorLeftFront,150);
    digitalWrite(motorLeftBack,LOW);

    analogWrite(motorRightFront,150);
    digitalWrite(motorRightBack,LOW);
  }
  else
  {
    digitalWrite(motorLeftFront,LOW);
    analogWrite(motorLeftBack,150);

    digitalWrite(motorRightFront,LOW);
    analogWrite(motorRightBack,150);
  }

  flameDetection=digitalRead(flamePin);
  if(flameDetection==LOW)
  {
   digitalWrite(flameLed, HIGH);
   digitalWrite(waterLed, HIGH);
   digitalWrite(RELAY_PIN, HIGH);
   //digitalWrite(waterLed, HIGH);
   tone(buzzerPin, 1000);
   delay(500);
   //servo.write(90);
  }else
  {
    digitalWrite(flameLed, LOW);
    digitalWrite(waterLed, LOW);
    digitalWrite(RELAY_PIN, LOW);
    noTone(buzzerPin); 
  }

  //smoke
  int analogSensor = analogRead(smokeA0);
  if(analogSensor > sensorThres)
  {
    digitalWrite(smokeLed, HIGH);
  }
  else
  {
    digitalWrite(smokeLed, LOW);
  }
}
