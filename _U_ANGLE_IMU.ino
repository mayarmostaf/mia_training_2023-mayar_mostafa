#include <Wire.h>
#define IMU_address 0x68
#define pw_reg 0x6B
#define gyro_conf_reg 0x1B
#define gyro_zh_reg 0x47
#define delta_t 20
int16_t z_offset =0;
//timer
#include <Timer.h>
#include <Event.h>
//final yaw_velocity measured
int16_t yaw_velocity =0;
//measured final yaw angle 
int16_t yaw =0;
//yaw before making it in range of [0,360]
int16_t y_total=0;
Timer mytimer;
void setup() { 
Wire.begin();//starting i2c
init_IMU ();// intialize imu
gyro_conf ();// set gyro configuration
get_offset();//get the offset to be subtracted from readings at the begging
mytimer.every(delta_t,measure_yaw);//measure z angle reguraly
Serial.begin(9600);//starting seria commu 
}

void loop() {
//updating timer 
mytimer.update();
}
//func to intiate imu
void init_IMU (void){
 Wire.beginTransmission(IMU_address);
 Wire.write(pw_reg);
 Wire.write(0X00);
 Wire.endTransmission();
  
  }
//func to set gyro configuration
void gyro_conf (void){
 Wire.beginTransmission(IMU_address);
 Wire.write(gyro_conf_reg);
 Wire.write(0X18);
 Wire.endTransmission();
  }
//func to read the value in yaw register
 int16_t read_gyro_z (void){
     int16_t z =0;
     //sending required reg to read which is the z direction angular acc
     Wire.beginTransmission(IMU_address);
     Wire.write(gyro_zh_reg );
     Wire.endTransmission();
     //reguesting to read 2 bytes high and low byte of z direction angular acc
     Wire.requestFrom(IMU_address,2);
     //waitng to receive
     while(Wire.available()<2);
     //saving bytes received
     z = Wire.read()<<8 | Wire.read();//saving higher byte and shift it to give place to concatenate lower byte in lower place 
 }
//func to get offset
 void get_offset (void){
  int16_t m =0;
  for(int i=0; i<3000;i++){
    m=read_gyro_z();//read value 
    z_offset+=m;//accumlate read value
    }
    //get the mean of values
    z_offset /=3000;
    
  }
//func to calibrate the read value by subtracting the offset from it 
 int16_t z_calibrate (int16_t z_bef_c ){
     return z_bef_c - z_offset;
     } 
//func to scale the reading
int16_t  z_scaling (int16_t z_bef_s){
     return (z_bef_s*2000)/32786 ;
  }
//final measure for yaw
void measure_yaw_velocity(void){
  yaw_velocity=read_gyro_z();
  yaw_velocity= z_calibrate(yaw_velocity);
  yaw_velocity= z_scaling(yaw_velocity);
  }
void measure_yaw(void){
  measure_yaw_velocity();
  int16_t y_slice =yaw_velocity*delta_t ;//calculating angle increased or decreased in last 20 millisecs
  y_total +=y_slice;
  yaw=y_total%360;//making it in range [0,360]
  Serial.print("angle:");
 Serial.print(yaw);
}
