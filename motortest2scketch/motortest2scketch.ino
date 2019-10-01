//   Connections
//   BNO055
//   ===========
//   Connect SCL to analog 5
//   Connect SDA to analog 4
//   Connect VDD to 3-5V DC
//   Connect GROUND to common ground

//   Connections
//   LMD18200
//   ==========
const char DirectionPin=1;
const char BrakePin=4;
const char PWMPin=5;
const char ThermaFlagPin=2;

//    Connections
//    NOE2
//    =========
const char APIN=3;
const char BNOTPIN=7;

int actualBrakePos=0, optimalBrakePos;

#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


long startOrientationX;
sensors_event_t event;
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  pinMode(DirectionPin,OUTPUT);
  digitalWrite(DirectionPin, HIGH);
  pinMode(BrakePin,OUTPUT);
  digitalWrite(BrakePin,LOW);
  pinMode(PWMPin,OUTPUT);
  analogWrite(PWMPin,0);
  
  
  pinMode(ThermaFlagPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(APIN), posInterrupt, CHANGE);
  pinMode(BNOTPIN,INPUT);
  
  Serial.begin(9600);
  Serial.println("ready?");

  if(!bno.begin()){
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
    delay(1000);
  
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0; //for the gyrosettup
  while (gyro!=3){//while the gyroscope is not calibrated: wait
    bno.getCalibration(&system, &gyro, &accel, &mag);
    delay(1000);
    Serial.print(gyro);
    Serial.println("calibrating gyro...");//TEMPPRINT
  }
  bno.getEvent(&event);
  startOrientationX=event.orientation.x;
  delay(1000);
  Serial.println("ready to start!");
  
}

void loop() {
  Serial.println("were would you like to go? max 255");
  optimalBrakePos=getOrientation();//the orientation is going the be interpreted as optimal motor position
  if (optimalBrakePos==actualBrakePos){
    analogWrite(PWMPin,0);//IE: stop motor
    digitalWrite(BrakePin,HIGH);//apply brakes
    return;
  }
  if (optimalBrakePos>actualBrakePos){
   digitalWrite(BrakePin,LOW);//without brakes
   digitalWrite(DirectionPin, HIGH);//go forward
   analogWrite(PWMPin,128);//with medium speed
   return;
  }
  else{//IE optimalBrakePos<actualBrakePos
   digitalWrite(BrakePin,LOW);//without brakes
   digitalWrite(DirectionPin, LOW);//go backwards
   analogWrite(PWMPin,128);//medioum speed
   return; 
  }

}

//long recieveOneChar(){
//  while (Serial.available()==0);//wait until Serial has something to read.
//   return Serial.parseInt(); 
//}//FOR TEMP READS

int getOrientation(){
  sensors_event_t event;
  bno.getEvent(&event);
  Serial.println(event.orientation.x);
  return event.orientation.x;
}

void posInterrupt(){//win APIN is triggered it must mean that the motor is moving
  if (digitalRead(DirectionPin) == HIGH){//double check that digitalRead works on output pins
      actualBrakePos++;//also: check if high direction= up brakes or down brakes
    }else{//IE directoinPin==LOW
      actualBrakePos--;
    }
  }
