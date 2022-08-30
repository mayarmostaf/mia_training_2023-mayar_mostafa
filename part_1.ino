#include <Timer.h>
#include <Event.h>
unsigned long myTime = 0;
unsigned long angle_L = 0;
unsigned long angle_R = 0;
//left_encoder
int A_L =18;
int B_L =19;
//right_encoder
int A_R =20;
int B_R =21;
//LEFT_MOTOR CONNECTIONS
int EN_L=2;//ENABLE PIN OF DRIVER
int input_1_L=3;
int input_2_L=4;
//LEFT_MOTOR CONNECTIONS
int EN_R=5;
int input_1_R=6;
int input_2_R=7;
//SWITCH_CONTROL
int sw=8;
long long count_L=0;
long long count_R=0;
void ISR_A_L (void);
void ISR_B_L (void);
void IS_A_R (void);
void ISR_B_R (void);
void setup() {
pinMode(A_L,INPUT_PULLUP); 
pinMode(B_L,INPUT_PULLUP);
pinMode(A_R,INPUT_PULLUP);
pinMode(B_R,INPUT_PULLUP);
pinMode(EN_L,OUTPUT); 
pinMode(EN_R,OUTPUT);
pinMode(input_1_L,OUTPUT);
pinMode(input_2_L,OUTPUT);
pinMode(input_1_R,OUTPUT);
pinMode(input_2_R,OUTPUT);
pinMode(sw,INPUT);
attachInterrupt(A_L,ISR_A_L,CHANGE);
attachInterrupt(B_L,ISR_B_L,CHANGE);
attachInterrupt(A_R,IS_A_R,CHANGE);
attachInterrupt(B_R,ISR_B_R,CHANGE);
// Turn off motors - Initial state
digitalWrite(input_1_L, LOW);
digitalWrite(input_2_L, LOW);
digitalWrite(input_1_R, LOW);
digitalWrite(input_2_R, LOW);
}

void loop() {
//check switch state 
if(digitalRead(sw)){
//LEFT_CONTROL
   while(count_L<400){//400 COUNT IS EQUIVALENT TO 60 DEGREE
   // Turn on motor left
    analogWrite(EN_L, 100);//low speed
    digitalWrite(input_1_L, HIGH);
    digitalWrite(input_2_L, LOW);
    }
    while(count_L>400){
   // Turn on motor left
    analogWrite(EN_L, 100);//low speed OPPOSITE DIRECTION
    digitalWrite(input_1_L, LOW);
    digitalWrite(input_2_L, HIGH);
    }
    analogWrite(EN_L,0);//STOP_MOTOR
    digitalWrite(input_1_L, LOW);
    digitalWrite(input_2_L, LOW);
 //RIGHT_CONTROL
   while(count_R<600){//600 COUNT IS EQUIVALENT TO 90 DEGREE
   // Turn on motor left
    analogWrite(EN_R, 100);//low speed
    digitalWrite(input_1_R, HIGH);
    digitalWrite(input_2_R, LOW);
    }
    while(count_R>600){
   // Turn on motor left
    analogWrite(EN_R, 100);//low speed OPPOSITE DIRECTION 
    digitalWrite(input_1_R, LOW);
    digitalWrite(input_2_R, HIGH);
    }
    analogWrite(EN_L,0);//STOPMOTOR
    digitalWrite(input_1_R, LOW);
    digitalWrite(input_2_R, LOW); 
  }
else if(digitalRead(sw)==0){
//LEFT_CONTROL
   while(count_L<400){//400 COUNT IS EQUIVALENT TO 60 DEGREE
   // Turn on motor left
    analogWrite(EN_L, 100);//low speed
    digitalWrite(input_1_L, HIGH);
    digitalWrite(input_2_L, LOW);
    }
    while(count_L>400){
   // Turn on motor left
    analogWrite(EN_L, 100);//low speed OPPOSITE DIRECTION
    digitalWrite(input_1_L, LOW);
    digitalWrite(input_2_L, HIGH);
    }
    analogWrite(EN_L,0);//STOP_MOTOR
    digitalWrite(input_1_L, LOW);
    digitalWrite(input_2_L, LOW);
 //RIGHT_CONTROL
   while(count_R<0){//0 COUNT IS EQUIVALENT TO 0 DEGREE
   // Turn on motor left
    analogWrite(EN_R, 100);//low speed
    digitalWrite(input_1_R, HIGH);
    digitalWrite(input_2_R, LOW);
    }
    while(count_R>0){
   // Turn on motor left
    analogWrite(EN_R, 100);//low speed OPPOSITE DIRECTION 
    digitalWrite(input_1_R, LOW);
    digitalWrite(input_2_R, HIGH);
    }
    analogWrite(EN_L,0);//STOPMOTOR
    digitalWrite(input_1_R, LOW);
    digitalWrite(input_2_R, LOW);  
  }
// calculate angle every 0.5 sec
    if(millis()-myTime >500){
    angle_L=(count_L%2400)/2400*360;
    angle_R=(count_R%2400)/2400*360;
    }
}
void ISR_A_L (void){
 if(digitalRead(A_L)!= digitalRead(B_L))
  count_L++;
  else
  count_L--;
  }
void ISR_B_L (void){
  if(digitalRead(A_L) == digitalRead(B_L))
  count_L++;
  else
  count_L--;
  }
void IS_A_R (void){
  if(digitalRead(A_R)!= digitalRead(B_R))
  count_R++;
  else
  count_R--;}
void ISR_B_R (void){
  if(digitalRead(A_R) == digitalRead(B_R))
  count_R++;
  else
  count_R--;
  }
