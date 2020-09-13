#include <Wire.h>

#define MPU 0x68  // I2C address of the MPU-6050

byte toSend[6] = {50, 100, 150, 200, 1, 1};
byte package[8];

double AcX,AcY,AcZ;
byte Pitch, Roll;

void setup() {
  init_MPU(); // Inizializzazione MPU6050
  Serial.begin(115200);
}

void loop() {
  FunctionsMPU(); // Acquisisco assi AcX, AcY, AcZ.
  Roll = (byte)FunctionsPitchRoll(AcX, AcY, AcZ) + 90;   //Calcolo angolo Roll
  Pitch = (byte)FunctionsPitchRoll(AcY, AcX, AcZ) + 90;  //Calcolo angolo Pitch*/
  byte incoming;
  incoming = Serial.read();
  switch(incoming){
    case 'A':
      //Serial.write(Roll);
      
      Serial.write((byte)(millis()/1000));
    break;
    case 'B':
      Serial.write((byte)(millis()/1000)+1);
      //Serial.write(Pitch);
    break;
    case 'C':
      Serial.write((byte)(millis()/1000)+2);
    break;
    case 'D':
      Serial.write((byte)(millis()/1000)+3);
    break;
  }
}
void serial_flush_buffer()
{
  while (Serial.read() >= 0); // do nothing
}
void init_MPU(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  delay(1000);
}
void FunctionsMPU(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
}
double FunctionsPitchRoll(double A, double B, double C){
  double DatoA, DatoB, Value;
  DatoA = A;
  DatoB = (B*B) + (C*C);
  DatoB = sqrt(DatoB);
  
  Value = atan2(DatoA, DatoB);
  Value = Value * 180/3.14;
  
  return (int)Value;
}
