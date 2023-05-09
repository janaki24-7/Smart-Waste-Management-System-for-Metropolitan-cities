#include <Servo.h>
Servo servo;
const int trigPin = 9;
const int echoPin = 10;
int trigPin2 = 5;    
int echoPin2 = 6;   
int servoPin = 7;
int distance = 0;
int threshold = 4; // change this value to set the threshold distance
long duration, dist, average;   
long aver[3];   //array for average

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(servoPin, OUTPUT);
  Serial.begin(9600);
  servo.attach(servoPin);  
  pinMode(trigPin2, OUTPUT);  
  pinMode(echoPin2, INPUT);  
  servo.write(0);         //close cap on power on
  delay(100);
  servo.detach();
}

void measure() {  
 digitalWrite(10,HIGH);
 digitalWrite(trigPin2, LOW);
 delayMicroseconds(5);
 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(15);
 digitalWrite(trigPin2, LOW);
 pinMode(echoPin2, INPUT);
 duration = pulseIn(echoPin2, HIGH);
 dist = (duration/2) / 29.1;    //obtain distance
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  distance = pulseIn(echoPin, HIGH) / 58; // convert the time into distance

  for (int i=0;i<=2;i++) {   //average distance
    measure();               
   aver[i]=dist;            
    delay(10);              //delay between measurements
  }
 dist=(aver[0]+aver[1]+aver[2])/3;

 if ( dist<=30 && distance > threshold) {
  //Change distance as per your need

  Serial.print("Human Distance: ");
  Serial.println(dist);
  Serial.print("Dustbin Level: ");
  Serial.println(distance);
  servo.attach(servoPin);
  delay(1);
  servo.write(180);  
  delay(3000);       
  servo.detach();      
}
 if (dist>=60) {
  servo.attach(servoPin);
  delay(100);
  servo.write(90);    
  delay(1000);
  servo.detach();
 }

  if (distance < threshold ) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println("The dustbin is full");
  } 

  delay(500); // wait for half a second before taking another measurement
}