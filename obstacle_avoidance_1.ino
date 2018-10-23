#include <Servo.h>
Servo h_servo,v_servo;//horizontal servo on 10

//Ultrasonic Pins
const int trigPin = 8;
const int echoPin = 12;


int temp,temp1,pos,i,obj,crazy=0;
const long interval = 1000;
unsigned long previousMillis = 0; 
unsigned long currentMillis=0; 
bool flag=false;
//int pos=0;

//Motor Pins lm1 stands for left motor 1 and accordingly
int lm2=3;
int lm1=5;
int rm1=6;
int rm2=11;


long duration;
int distance;

void setup() 
{
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  
  pinMode(lm1,OUTPUT);
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);

  h_servo.attach(10);
  v_servo.attach(9);
  h_servo.write(55); 

  
  Serial.begin(9600); 
}

void loop() 
{
  ultrasonic();
  if(distance<=5)
  {
    stop1();
    start_servo();
    Serial.println("First condition");
  }
  else //if(distance>=5)
  {
    forward();
    Serial.println("else condition");
  }

}

void start_servo()
{
  Serial.println("Entered servo");
  ultrasonic();
   for (pos = 45; pos <= 105; pos += 1) 
    {    
      h_servo.write(pos);             
      delay(45);                       
    }
    
    ultrasonic();
    if(distance>=5)
    {
      left_turn();delay(1000);h_servo.write(55);
    }
    else
    {
      for (pos = 100; pos >= 0; pos -= 1) 
    {    
      h_servo.write(pos);             
      delay(75);                       
    }
      ultrasonic();
      if(distance>=5)
    {
      right_turn();
      delay(1000);h_servo.write(55);
    }
    else
    left_turn();delay(2000);//Making a Turn Over
      
    }
    
    
    
    Serial.println("Rotating horizontal servo");            
      ultrasonic();      
  }
  
  

void forward()
{
  ultrasonic();
  if (distance>=5)
  {
  digitalWrite(lm1,HIGH);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  digitalWrite(lm2,LOW);
  Serial.println("Straight");
  }
}
void right_turn()
{
  digitalWrite(lm1,HIGH);
  digitalWrite(rm2,HIGH);
  digitalWrite(rm1,LOW);
  digitalWrite(lm2,LOW);
  Serial.println("Right turn");
}

void left_turn()
{
  digitalWrite(rm1,HIGH);
  digitalWrite(lm2,HIGH);
  digitalWrite(lm1,LOW);
  digitalWrite(rm2,LOW);
  Serial.println("Left turn");
}

void stop1()
{
  digitalWrite(lm1,LOW);
  digitalWrite(rm2,LOW);
  digitalWrite(rm1,LOW);
  digitalWrite(lm2,LOW);
  delay(500);
  Serial.println("Stopped");
}


void ultrasonic()
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);// Reads the echoPin, returns the sound wave travel time in microseconds
distance = (duration/2) / 29.1;
/*
Serial.print("Distance=");
Serial.println(distance);*/

}
