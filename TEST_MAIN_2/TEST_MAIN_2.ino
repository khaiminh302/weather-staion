#include <Wire.h>

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
//-------------- khai bao cua mpu6050 ---------------
const int FLEX_PIN0 = A0; 
const int FLEX_PIN1 = A1;
const int FLEX_PIN2 = A2; 
const int FLEX_PIN3 = A3;
const int FLEX_PIN4 = A6; 

//KHAI BAO CAC GIA TRI KHAC
const float VCC = 5.0; // Measured voltage of Ardunio 5V line
const float R_DIV = 10000.0; // Measured resistance of 3.3k resistor

const float STRAIGHT_RESISTANCE_SMALL = 30000.0; // resistance when straight
const float BEND_RESISTANCE_SMALL = 90000.0; // resistance at 90 deg
const float STRAIGHT_RESISTANCE_BIG = 10500.0;
const float BEND_RESISTANCE_BIG = 20000.0;
// ------------------------------ khai bao cua Flex Sensor


void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN0, INPUT);
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);
  pinMode(FLEX_PIN3, INPUT);
  pinMode(FLEX_PIN4, INPUT);
  
  Wire.begin();
  setupMPU(); }// MPU



void loop() {
   recordAccelRegisters();
  recordGyroRegisters();

  delay(10);
  
  // Read the ADC, and calculate voltage and resistance from it
  int VRADC0 = analogRead(FLEX_PIN0);
  int VRADC1 = analogRead(FLEX_PIN1);
  int VRADC2 = analogRead(FLEX_PIN2);
  int VRADC3 = analogRead(FLEX_PIN3);
  int VRADC4 = analogRead(FLEX_PIN4);
 
    float VR0 = VRADC0 * VCC / 1023.0;
    float VR1 = VRADC1 * VCC / 1023.0;
    float VR2 = VRADC2 * VCC / 1023.0;
    float VR3 = VRADC3 * VCC / 1023.0;
    float VR4 = VRADC4 * VCC / 1023.0;
  
  float flexR0 = R_DIV * (VCC / VR0 - 1.0);
  float flexR1 = R_DIV * (VCC / VR1 - 1.0);
  float flexR2 = R_DIV * (VCC / VR2 - 1.0);
  float flexR3 = R_DIV * (VCC / VR3 - 1.0);
  float flexR4 = R_DIV * (VCC / VR4 - 1.0);


// co so du lieu
Serial.println("   Resistance: " + String(flexR0)+" "+String(flexR1)+" "+String(flexR2)+" "+String(flexR3)+" "+String(flexR4) +" Ohms" );
  
  if ((flexR0>=33000)&&(flexR0<=39000)&&(flexR1>=16000)&&(flexR1<=21000)&&(flexR2>=18000)&&(flexR2<=23000)&&(flexR3>=15000)&&(flexR3<=20000)&&(flexR4>=50000)&&(flexR4<=70000)) {
    Serial.print("A");}
  
  else   if ((flexR0>=34000)&&(flexR0<=40000)&&(flexR1>=9000)&&(flexR1<=14000)&&(flexR2>=8000)&&(flexR2<=13000)&&(flexR3>=7000)&&(flexR3<=12000)&&(flexR4>=24000)&&(flexR4<=30000)) {
    Serial.print("B");}
   
  else  if ((flexR0>=27000)&&(flexR0<=35000)&&(flexR1>=12000)&&(flexR1<=19000)&&(flexR2>=1300)&&(flexR2<=20000)&&(flexR3>=13000)&&(flexR3<=20000)&&(flexR4>=30000)&&(flexR4<=45000)) {
    Serial.print("C");}
  
  else  if ((flexR0>=28000)&&(flexR0<=34000)&&(flexR1>=8000)&&(flexR1<=15000)&&(flexR2>=17000)&&(flexR2<=25000)&&(flexR3>=14000)&&(flexR3<=210000)&&(flexR4>=50000)&&(flexR4<=65000)) {
    Serial.print("D");}
  
  else  if ((flexR0>=39000)&&(flexR0<=55000)&&(flexR1>=15000)&&(flexR1<=21000)&&(flexR2>=18000)&&(flexR2<=23000)&&(flexR3>=14000)&&(flexR3<=19000)&&(flexR4>=49000)&&(flexR4<=60000)) {
    Serial.print("E");}
  
  else if ((flexR0>=50000)&&(flexR0<=65000)&&(flexR1>=14000)&&(flexR1<=29000)&&(flexR2>=18000)&&(flexR2<=23000)&&(flexR3>=8000)&&(flexR3<=13000)&&(flexR4>=23000)&&(flexR4<=26000)) {
    Serial.print("G");}
  
  else if ((flexR0>=40000)&&(flexR0<=50000)&&(flexR1>=11000)&&(flexR1<=15000)&&(flexR2>=8000)&&(flexR2<=13000)&&(flexR3>=8000)&&(flexR3<=13000)&&(flexR4>=29000)&&(flexR4<=34000)) {
    Serial.print("H");}

  else if ((flexR0>=22000)&&(flexR0<=27000)&&(flexR1>=9000)&&(flexR1<=13000)&&(flexR2>=14000)&&(flexR2<=18000)&&(flexR3>=14000)&&(flexR3<=18000)&&(flexR4>=27000)&&(flexR4<=32000)) {
    Serial.print("I");}

  else if ((flexR0>=30000)&&(flexR0<=35000)&&(flexR1>=12000)&&(flexR1<=16000)&&(flexR2>=8000)&&(flexR2<=12000)&&(flexR3>=8000)&&(flexR3<=12000)&&(flexR4>=24000)&&(flexR4<=28000)) {
    Serial.print("K");}
    
   else if ((flexR0>=30000)&&(flexR0<=40000)&&(flexR1>=9000)&&(flexR1<=13000)&&(flexR2>=9000)&&(flexR2<=12000)&&(flexR3>=9000)&&(flexR3<=15000)&&(flexR4>=25000)&&(flexR4<=43000)) {
    Serial.print("H");}
    
   else if ((flexR0>=21000)&&(flexR0<=27000)&&(flexR1>=9000)&&(flexR1<=14000)&&(flexR2>=16000)&&(flexR2<=25000)&&(flexR3>=11000)&&(flexR3<=15000)&&(flexR4>=24000)&&(flexR4<=29000)) {
    Serial.print("");}
    
   else if ((flexR0>=21000)&&(flexR0<=27000)&&(flexR1>=9000)&&(flexR1<=14000)&&(flexR2>=16000)&&(flexR2<=25000)&&(flexR3>=11000)&&(flexR3<=15000)&&(flexR4>=24000)&&(flexR4<=29000)) {
    Serial.print("TOI YEU BAN");}
  
    
    
delay(100);}











void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData(){
  gForceX = accelX*100.0/ 16384.0;
  gForceY = accelY*100.0 / 16384.0; 
  gForceZ = accelZ*100.0 / 16384.0;
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
}

void printData() {
  Serial.print("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);
  Serial.print(" Accel (g)");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.println(gForceZ);}
















  

  

