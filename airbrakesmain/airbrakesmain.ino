//Values for calibration:
//======================
//change these before your flight for best results
#define groundAltitude 3900 //this should be the altitude of the launchpad in feet; used for calculating Pressure at sea level for the BME055

void preFlightLoop();//declaritive functions
void preApogeeLoop();
void postApogeeLoop();

//for pin values
#define movespeed 800
#define dirA 7
#define dirB 8
#define pwrA 9
#define pwrB 10
#define minswitch 6
#define maxswitch 11
//IMU - BNO 055
//Temp& pressure BME280
//   ===========
//   Connect SCL to analog 5
//   Connect SDA to analog 4
//   Connect VDD to 3-5V DC
//   Connect GROUND to common ground
const char DirectionPin=1;
const char BrakePin=4;
const char PWMPin=5;
const char ThermaFlagPin=2;
const char APIN=3;
const char BNOTPIN=7;

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MCP9808.h>

  Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
  Adafruit_BNO055 bno;
long startOrientationX,startOrientationY,startOrientationZ;
  Adafruit_BME280 bme;
int pressureAtSea=1015.5;
float lastReadAltitude=groundAltitude;
unsigned long lastReadTime=0;
int optimalBrakePos, BrakePos;
sensors_event_t event;

unsigned long startTime=0;//for the reset switch //this in umimplimented but is planed to be used with a button so that simulations can be reset

#include <SoftwareSerial.h>
SoftwareSerial bluetooth(11,5);

void setup() {
  boolean bmeOK=false,bnoOK=false,mcpOK=false;
  BrakePos=0;
  Serial.begin(9600);
 //connect BLUETOOTH to possible payload
  //settup all important sensors
 //settup bme:

    if (bme.begin()) {
      bmeOK=true;
    }else{
        statusReport('E',1);
    }
    //pressureAtSea=(int)(bme.readPressure()+(groundAltitude/1000)*33.8639);//33.8639 is the conversion rate between inch of murcury to millibars
    //statusReport("pressureAtSea calculated:"+String(pressureAtSea)+"milibar");
 //settup bno:
 if (bno.begin()){
   uint8_t sys, gyro, accel, mag;
    sys = gyro = accel = mag = 0;
    while (gyro!=3){//while the gyroscope is not calibrated: wait //The BNO055 will calibrate its gyroscope after sitting still long enough
      bno.getCalibration(&sys, &gyro, &accel, &mag);
      //Serial.println("calibrating gyro...");//TEMPPRINT
    }
    bno.getEvent(&event);
    startOrientationX=event.orientation.x;//these values are going to be subtracted from the any rocket sensor reading so that
    startOrientationY=event.orientation.y;//the sensors will read relative to vertical (the initial rocket orientation)
    startOrientationZ=event.orientation.z;
    bnoOK=true;
  }else{
    statusReport('E',1);
    startOrientationX=0;
    startOrientationY=0;
    startOrientationZ=0;
  }
  //mcp settup   
  //  A2 A1 A0 address
  //  0  0  0   0x18  this is the default address
  //  0  0  1   0x19
  //  0  1  0   0x1A
  //  0  1  1   0x1B
  //  1  0  0   0x1C
  //  1  0  1   0x1D
  //  1  1  0   0x1E
  //  1  1  1   0x1F
  if (tempsensor.begin(0x18)) {
    tempsensor.setResolution(3);
    mcpOK=true;
  }else{
    statusReport('E',1);
  }

  pinMode(dirA,OUTPUT);
  pinMode(dirB,OUTPUT);
  pinMode(pwrA,OUTPUT);
  pinMode(pwrB,OUTPUT);//2 tied to 6; 4 tied to 8
  digitalWrite(dirA,HIGH);//HHLL
  digitalWrite(dirA,HIGH);
  digitalWrite(pwrB,HIGH);
  digitalWrite(pwrB,HIGH);
  pinMode(13, INPUT);
  pinMode(minswitch, INPUT);
  pinMode(maxswitch, INPUT);
  if (bmeOK&&bnoOK&&mcpOK){
    statusReport('E',0);
  }
}



void loop() {
//while (digitalRead(13)==LOW){}//wait until button to start //TEMPPRINT
//delay(10);
//startTime=millis();//temp
preFlightLoop();
preApogeeLoop();
postApogeeLoop();
}

float fakeAltRead(){//for debug and demo purposes entierly temp returns an altitude
  int initialV=275;//275 puts us at 3858 meters (over 10,000 feet)
  if ((millis()-startTime)<2000)//is set to start after 2 seconds
    return (float)groundAltitude;
  float testtime = (((millis()-startTime)-2000)/1000.0);//equal to the seconds after starttime; the 2000 is to acount for the 2 second delay before launch
  Serial.print((String)(testtime)+",");//TEMPPRINT
  Serial.println((String)(groundAltitude+(initialV*testtime)-(4.9*testtime*testtime)));//TEMPPRINT
  return (float)(groundAltitude+(initialV*testtime)-(4.9*testtime*testtime));
}

float getSpeedfromAltitude(){//this function will get the speed from the BME280 altitude sense; changes lastReadAltitude and lastReadTime; m/s
  float altRead = fakeAltRead();  //gets altitude in meters //goes to 3858 m above sea level
  unsigned long timeRead=(millis()-startTime);    //gets time in millisecond
  unsigned long changeInTime=timeRead-lastReadTime;
  float changeInAltitude=(altRead-lastReadAltitude);
  lastReadTime=timeRead;
  lastReadAltitude=altRead;
  //Serial.println("A: "+(String)(changeInAltitude));
  //Serial.println("S: "+(String)(changeInAltitude/((changeInTime)/1000.0)));
  return (changeInAltitude/((changeInTime)/1000.0)); //returns the speed in vertical meters per second //1000 is the conversion from millisecond to second
}

//STR [][][][][][][] END
void statusReport(char type, int data){//this is the function that sends data via bluetooth

}




