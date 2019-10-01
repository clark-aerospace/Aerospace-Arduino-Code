

void preFlightLoop(){
  int i=0;
  do{//while(getSpeedfromAltitude()>5); //WHILE NOT GOING UP; //while speed is less than 5m/s
    statusReport('t',tempsensor.readTempF());//tell the temperature to the monitoring station
  } while(getSpeedfromAltitude()<5);
  Serial.println("ignition detected");
  delay(4500);//this should be the amount of time that the motor takes to burn
  //then we go onto preApogee loop...
}

