
void postApogeeLoop(){
  do{//while(true); //do untill reset
//    statusReport('T',bme.readTemperature());
//    statusReport("A", lastReadAltitude));
      Serial.println("S:"+ (String)getSpeedfromAltitude() +" A:" + (String)lastReadAltitude);
//    //relay that to monitoring station
  } while(true);
}
