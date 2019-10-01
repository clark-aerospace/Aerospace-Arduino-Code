#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Adafruit_MCP9808.h>

#define rx_GPS 11
#define tx_GPS 12

SoftwareSerial GPSSerial(rx_GPS, tx_GPS);
Adafruit_GPS GPS(&GPSSerial);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  GPSSerial.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  Serial.println("testing");
    delay(1000);
  // Ask for firmware version
  GPSSerial.println(PMTK_Q_RELEASE);
}

void loop() {
  do{
    GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())){
    }
  }
  Serial.println((String)GPS.satellites);
  }while (!GPS.fix);
  Serial.println((String)GPS.latitude+"\t"+(String)GPS.longitude);
}

