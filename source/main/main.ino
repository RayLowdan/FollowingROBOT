// == encodeing utf-8 ==
// 參考自 https://github.com/vermaPrateek10/Human-Following-Robot.git

//import library
#include<NewPing.h>           
#include<Servo.h>             
#include<AFMotor.h>           

//init all pin
#define LEFT A5
#define RIGHT A1
#define TRIGGER_PIN A2
#define ECHO_PIN A3
#define MAX_DISTANCE 200

//globle var
unsigned int distance = 0;
unsigned int Right_Value = 0;
unsigned int Left_Value = 0;
int D=30;
int d = 5;
int FPS = 100;
  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//motor objects 
AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);

Servo myservo; //create servo object to control the servo:
int pos=0;     //variable to store the servo position:

void setup() {//init
  Serial.begin(9600); //initailize serial communication at 9600 bits per second:

//    myservo.attach(10); // servo attached to pin 10 of Arduino UNO
// {
// for(pos = 90; pos <= 180; pos += 1){    // goes from 90 degrees to 180 degrees:
//   myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
//   delay(15);                            //wait 15ms for the servo to reach the position:
//   } 
// for(pos = 180; pos >= 0; pos-= 1) {     // goes from 180 degrees to 0 degrees:
//   myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
//   delay(15);                            //wait 15ms for the servo to reach the position:
//   }
// for(pos = 0; pos<=90; pos += 1) {       //goes from 180 degrees to 0 degrees:
//   myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
//   delay(15);                            //wait 15ms for the servo to reach the position:
//   }
// }
//    pinMode(RIGHT, INPUT); //set analog pin RIGHT as an input:
//    pinMode(LEFT, INPUT);  //set analog pin RIGHT as an input:
//    stop();
}


void loop() {                             
  delay(1000/FPS);
  distance = sonar.ping_cm();
  debug_dis(true,distance);


  // IR value
  Right_Value = !digitalRead(RIGHT);
  Left_Value = !digitalRead(LEFT);
  
  //debug
  debug_IR(false,Right_Value,Left_Value);

  // int next action
  //  ===================================
  //  1       2        3         4      |
  //  front   right    left      stop   |
  //  ===================================
  int nextact = action(D,d,distance,Right_Value,Left_Value);


  switch(nextact){
    case 1 :
      front1();
      break;
    case 2 :
      turn_right();
      break;
    case 3 :
      turn_left();
      break;
    case 4 :
      stop();
      break;
    default:// when ERROR
      Serial.print("[system/ERROR]: action error");
      break;
  }
}

// define functions for motor
void turn_left(){
Motor1.setSpeed(150);
Motor1.run(BACKWARD);
Motor2.setSpeed(150);
Motor2.run(BACKWARD);
Motor3.setSpeed(150);
Motor3.run(FORWARD);
Motor4.setSpeed(150);
Motor4.run(FORWARD);
}

void turn_right(){
Motor1.setSpeed(150);
Motor1.run(FORWARD);
Motor2.setSpeed(150);
Motor2.run(FORWARD);
Motor3.setSpeed(150);
Motor3.run(BACKWARD);
Motor4.setSpeed(150);
Motor4.run(BACKWARD);
}

void back(){
Motor1.setSpeed(230); // back speed 230
Motor1.run(BACKWARD);  
Motor2.setSpeed(230);  
Motor2.run(BACKWARD);  
Motor3.setSpeed(230);  
Motor3.run(BACKWARD);  
Motor4.setSpeed(230);  
Motor4.run(BACKWARD); 
}


void front1(){
Motor1.setSpeed(150); // 150 speed
Motor1.run(FORWARD);  
Motor2.setSpeed(150);  
Motor2.run(FORWARD);  
Motor3.setSpeed(150);  
Motor3.run(FORWARD);  
Motor4.setSpeed(150);  
Motor4.run(FORWARD);  
}

void front2(){
Motor1.setSpeed(230); //230 speed
Motor1.run(FORWARD);  
Motor2.setSpeed(230);  
Motor2.run(FORWARD);  
Motor3.setSpeed(230);  
Motor3.run(FORWARD);  
Motor4.setSpeed(230);  
Motor4.run(FORWARD);  
}

void stop(){        //Stop all motor
Motor1.setSpeed(0);
Motor1.run(RELEASE);
Motor2.setSpeed(0);
Motor2.run(RELEASE);
Motor3.setSpeed(0);
Motor3.run(RELEASE);
Motor4.setSpeed(0);
Motor4.run(RELEASE);
}
void debug_dis(bool enable,int distance){
  if (enable){
    Serial.print("[system/DEBUG]: distance/");                   
    Serial.println(distance);                         // print the distance in serial monitor:
  }
}


void debug_IR(bool enable, int Right_Value, int Left_Value){                               //debug on 9600 bits
  if (enable){
    if (Right_Value == 1){
      Serial.println("[system/DEBUG]: RIGHT");     
    }
    if (Left_Value == 1){
      Serial.println("[system/DEBUG]: LEFT");   
    }
  }
}


int action(int D, int d,int distance,int Right_Value,int Left_Value){
if((distance > d) && (distance < D)){            //check wheather the ultrasonic sensor's value stays between 1 to 15.
  //Move Forward:
  return 1;
}else if((Right_Value==1) && (Left_Value==0)) {   //If the condition is 'true' then the statement below will execute:
  //Turn right                                                
  return 2;
}else if((Right_Value==0)&&(Left_Value==1)) {     //If the condition is 'true' then the statement below will execute:
  // turn left
  return 3;
}else if(distance > D || distance < d) {                          //If the condition is 'true' then the statement below will execute:
// stop
  return 4;
}}


// Motor1.setSpeed(230); //test FORWARD BACKWARD
// Motor1.run(FORWARD);  
// Motor2.setSpeed(230);  
// Motor2.run(FORWARD);  
// Motor3.setSpeed(230);  
// Motor3.run(FORWARD);  
// Motor4.setSpeed(230);  
// Motor4.run(FORWARD);  