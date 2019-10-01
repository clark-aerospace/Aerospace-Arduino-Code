#define brakemax 500

void preApogeeLoop(){
  int i=0;
  float Vspeed;
  do{//while(i<10); //WHILE VERTICAL SPEED IS > JUST BEFORE APOGEE
    //read altitude
      Vspeed = getSpeedfromAltitude();//normal functions
      if ((predictApogee(Vspeed, lastReadAltitude)-3048) > 1/(Vspeed+1))//if we are going to go over 1000 ft, raise the air brakes
        optimalBrakePos=1;//1=up 0=down
        else
        optimalBrakePos=0;
      //Serial.println(",\t,\t"+(String)BrakePos+",\t"+(String)optimalBrakePos+","+(String)Vspeed+","+(String)predictApogee(Vspeed, lastReadAltitude));//TEMPPRINT
      statusReport('B', BrakePos);
      statusReport('A', lastReadAltitude);
      
      bno.getEvent(&event);
      if ((abs(event.orientation.y-startOrientationY)>45)||(abs(event.orientation.x-startOrientationX)>45)){//if the rocket is tilted
        optimalBrakePos=0;
      }
      
      while (optimalBrakePos==0){//move brakes towards optimal position
        moveBrakeDown();
      }
      while (optimalBrakePos==1){
        moveBrakeUp();
      }
      
  } while(Vspeed>15);
    optimalBrakePos=0;
      while (optimalBrakePos>BrakePos){//move brakes to 0 near apogee
        moveBrakeDown();
      }
  //wait for apogee
  while (getSpeedfromAltitude()>(4));//wait until speed is less than 0 IE: wait until turnover
  Serial.println("Apogee detected at "+String(lastReadAltitude-groundAltitude)+" meters");//reporting apogee hight
  //then we go onto postApogeeLoop...
}

float predictApogee(float speed, float altitude){//predicts apogee in meters

//using the equation: Ymax=V^2/(2g)+Y
return (speed*speed/19.602)+(altitude-groundAltitude);

}


void moveBrakeUp(){//ends at 1,1 & HHHH
  digitalWrite(pwrA, LOW);
  digitalWrite(dirA, LOW);
  digitalWrite(pwrA, HIGH);
  while (digitalRead(maxswitch)==HIGH);//wait
  digitalWrite(pwrA, LOW);
  BrakePos=1;
}

void moveBrakeDown(){
  digitalWrite(pwrA, LOW);
  digitalWrite(dirA,HIGH);
  digitalWrite(pwrA, HIGH);
  while (digitalRead(minswitch)==HIGH);//wait
  digitalWrite(pwrA, LOW);
  BrakePos=0;
}

