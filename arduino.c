#include <Servo.h>
#include <SoftwareSerial.h>
#include <AFMotor.h>
SoftwareSerial BT(A0, A1);

Servo servo_1;
Servo servo_2;

int state;
int speed = 130;
int pos1 = 90;
int pos2 = 90;

int pump = 6;
int pwm = 5;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
void setup(){
servo_1.attach(10);
servo_2.attach(9);
servo_1.write(pos1); 
servo_2.write(pos2); 
motor1.setSpeed(150);
motor2.setSpeed(150);
motor3.setSpeed(200);
pinMode(pump, OUTPUT);

pinMode(pwm, OUTPUT);

// initialize serial communication at 9600 bits per second:
Serial.begin(9600);
BT.begin(9600); // Setting the baud rate of Software Serial Library 
 
 delay(1000);
 }

void loop(){
 
//if some date is sent, reads it and saves in state
if(BT.available() > 0){     
state = BT.read(); 
Serial.println(state);
if(state > 15){speed = state;}      
}
  
   // if the state is '1' the DC motor will go forward
     if (state == 1){forword();Serial.println("Forward!");}

// if the state is '2' the motor will Backword
else if (state == 2){backword();Serial.println("Backword!");}
    
// if the state is '3' the motor will turn left
else if (state == 3){turnLeft();Serial.println("Turn LEFT");}
    
// if the state is '4' the motor will turn right
else if (state == 4){turnRight();Serial.println("Turn RIGHT");}
    
// if the state is '5' the motor will Stop
else if (state == 5) {stop();Serial.println("STOP!");}    

else if (state == 6) {Serial.println("lift");  if(pos1<180){pos1 = pos1+1;}} 
else if (state == 7) {Serial.println("right"); if(pos1>0){pos1 = pos1-1;}} 
else if (state == 8) {Serial.println("up");    if(pos2>0){pos2 = pos2-1;}}  
else if (state == 9) {Serial.println("down");  if(pos2<180){pos2 = pos2+1;}} 

else if (state == 10){Serial.println("pump on"); motor3.run(FORWARD); } 
else if (state == 11){Serial.println("pump off"); motor3.run(RELEASE); } 

servo_1.write(pos1); 
servo_2.write(pos2); 

analogWrite(pwm, speed);
delay(30);
}


void stop(){
  motor1.run(RELEASE);  
  motor2.run(RELEASE);  
}

void forword(){
   motor1.run(FORWARD);
   motor2.run(FORWARD);
}

void backword(){
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);       
}


void turnRight(){
     motor1.run(BACKWARD);      
    motor2.run(FORWARD);  
}

void turnLeft(){
     motor1.run(FORWARD);      
    motor2.run(BACKWARD);   
}
