#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
//#include <Adafruit_MCP9808.h>
//#include <math.h>
//12 & 11 for , 9 & 8 for
#define rx_RAD 9
#define tx_RAD 8


#define rx_GPS 11
#define tx_GPS 12


//Temp& pressure BME280
//   ===========
//   Connect SCL to analog 5
//   Connect SDA to analog 4
//   Connect VDD to 3-5V DC
//   Connect GROUND to common ground

SoftwareSerial Radio(rx_RAD, tx_RAD);//rx tx
SoftwareSerial GPSSerial(rx_GPS, tx_GPS);
Adafruit_GPS GPS(&GPSSerial);
//Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

unsigned long checktime;
char test;
//typedef union {
//  double value;
//  byte bytes[8];
//} doubleUnion;
//
//typedef union {
//  double value;
//  byte bytes[4];
//} longIntUnion;

struct DataStruct{
 char STR[3] = {'S','T','R'};
 double lat=0;
 double lon=0;
 long alt = 0;
 long acx = 0;
 long acy = 0;
 long acz = 0;
 long rox = 0;
 long roy = 0;
 long roz = 0;
 long row = 0;
 long aba = 0;
 long tpl = 0;
 long tav = 0;
 long tam = 0;
 char pdp[1]={0};
 long tep = 0;
 char END[3]= {'E','N','D'};
} Data;

byte startcode[3]={'B','E','G'};
void setup() {
  Radio.begin(57600);
  GPS.begin(9600);
  Serial.begin(57600);
  //Serial.println(sizeof(Data));
//  Serial.print(sizeof(double));
//  Serial.print(sizeof(long double));
//  Serial.print(sizeof(unsigned long));
  //GPS settup
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);

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
//  if (tempsensor.begin(0x18)) {
//    tempsensor.setResolution(3);
//  }

// 
//  while (!Serial) {// wait for serial port to connect.
//  }
//  //Serial.println("connected");
////  boolean looptest=true;
////  while (looptest)
////    if (Radio.find("SEND"))
////      looptest=false;
//
// checktime = millis(); 
// 
}

void loop() {
  delay(50);
//  //Serial.print(Serial.available());
//  readGPS();
//  readData();
//  if(millis()-checktime>=500){
    writeData();
//    checktime=millis();
//  }
  }
//
//void readGPS() {
//  do{
//  GPS.read();
//  GPS.parse(GPS.lastNMEA());
//  if (GPS.newNMEAreceived()) {
//    if (!GPS.parse(GPS.lastNMEA())){
//    }
//  }
//  Serial.write('c');
//  //Serial.println("S "+(String)GPS.satellites);
//  }while (!GPS.fix);
//  
//    Data.lon = (double) (GPS.longitudeDegrees);
//    Data.lat = (double) (GPS.latitudeDegrees);
    
    //Serial.print(Data.lon,4);
    //Serial.print(" ");
    //Serial.println(Data.lat,4);
    //Serial.println((String)GPS.satellites);
}
//void readtemp(){
//  doubleUnion temp;
//    temp.value = (double) tempsensor.readTempF();
//    for (int i = 0; i < 8; i++) 
//      Radio.write(temp.bytes[i]);
//  
//}

//void readData(){//gps lat[4] and long[4] are already recorded
//  Serial.write(startcode,3);
//  Data.alt=Serial.parseInt();
//  Data.acx=Serial.parseInt();
//Serial.readBytes(Data.alt, 4);
//Serial.readBytes(Data.acx, 4);
//Serial.readBytes(Data.acy, 8);
//Serial.readBytes(Data.acz, 8);
//Serial.readBytes(Data.rox, 8);
//Serial.readBytes(Data.roy, 8);
//Serial.readBytes(Data.roz, 8);
//Serial.readBytes(Data.row, 8);
//Serial.readBytes(Data.aba, 8);
//Serial.readBytes(Data.tpl, 8);
//Serial.readBytes(Data.tav, 8);
//Serial.readBytes(Data.tam, 8);
//Serial.readBytes(Data.pdp, 1);
//Serial.readBytes(Data.tep, 4);
}

void writeData(){
byte test[8]=Serial.read(4);
Serial.write(test,4);
//test=(Radio.write((byte*)&Data,111));

}


