#define brakemax 500

void preApogeeLoop(){
  int i=0;
  float Vspeed;
  do{//while(i<10); //WHILE VERTICAL SPEED IS > JUST BEFORE APOGEE
    //read altitude
      Vspeed = getSpeedfromAltitude();//normal changes lastReadAltitude and returns a velocity in m and m/s.
      optimalBrakePos=(int)((predictApogee(Vspeed, lastReadAltitude)-3048));//if we are going to go over 1000 ft (ie: 3048 meters), raise the air brakes //this function is someone arbiturary and should be considered for improvement
      Serial.println(",\t,\t actual:"+(String)BrakePos+",\t optimal:"+(String)optimalBrakePos+" Vspeed:"+(String)Vspeed+" predicApog:"+(String)predictApogee(Vspeed, lastReadAltitude));//TEMPPRINT
      statusReport('B', BrakePos);
      statusReport('A', lastReadAltitude);

      if (optimalBrakePos>brakemax)
        optimalBrakePos=brakemax;
      if (optimalBrakePos<0)
        optimalBrakePos=0;

      
      bno.getEvent(&event);
      if ((abs(event.orientation.y-startOrientationY)>45)||(abs(event.orientation.x-startOrientationX)>45)){//if the rocket is tilted
        optimalBrakePos=0;
      }
      
      while (optimalBrakePos<BrakePos){//move brakes towards optimal position
        moveBrakeDown();
      }
      while (optimalBrakePos>BrakePos){
        moveBrakeUp();
      }
      
  } while(Vspeed>15);
    optimalBrakePos=0;
      while (optimalBrakePos>BrakePos){//move brakes to 0 near apogee
        Serial.println(",\t,\t actual:"+(String)BrakePos+",\t optimal:"+(String)optimalBrakePos+" Vspeed:"+(String)Vspeed+" predicApog:"+(String)predictApogee(Vspeed, lastReadAltitude));//TEMPPRINT
        moveBrakeDown();
      }
  //wait for apogee
  while (getSpeedfromAltitude()>(2));//wait until speed is less than 2 IE: wait until turnover // 2 is an arbuitraritly small number !=0 because If we waited for >0 then it would be too for max apogee
  Serial.println("Apogee detected at "+String(lastReadAltitude-groundAltitude)+" meters");//reporting apogee hight
  //then we go onto postApogeeLoop...
}

float predictApogee(float speed, float altitude){//predicts apogee in meters

//using the equation: Ymax=V^2/(2g)+Y
return (speed*speed/19.602)+(altitude-groundAltitude);

}


void moveBrakeUp(){//ends at 1,1 & HHHH
  if (digitalRead(maxswitch)==HIGH){
    delayMicroseconds(movespeed);
    digitalWrite(pwrA,LOW);
    digitalWrite(dirA,LOW);//(-1),1
    delayMicroseconds(movespeed);
    digitalWrite(pwrA,HIGH);//-1,1
    delayMicroseconds(movespeed);
    digitalWrite(pwrB,LOW);
    digitalWrite(dirB,LOW);//-1,(-1)
    delayMicroseconds(movespeed);
    digitalWrite(pwrB,HIGH);//-1,-1
    delayMicroseconds(movespeed);
    digitalWrite(pwrA,LOW);
    digitalWrite(dirA,HIGH);//(1),-1
    delayMicroseconds(movespeed);
    digitalWrite(pwrA,HIGH);//1,-1
    delayMicroseconds(movespeed);
    digitalWrite(pwrB,LOW);
    digitalWrite(dirB,HIGH);//1,(1)
    delayMicroseconds(movespeed);
    digitalWrite(pwrB,HIGH);//1,1
  }
  BrakePos++;
}

void moveBrakeDown(){
  if (digitalRead(minswitch)==HIGH){
    delayMicroseconds(movespeed);
    digitalWrite(pwrB,LOW);
    digitalWrite(dirB,LOW);//1,(-1)
    delayMicroseconds(movespeed);
    digitalWrite(pwrB,HIGH);//1,-1
    delayMicroseconds(movespeed);
    digitalWrite(pwrA,LOW);
    digitalWrite(dirA,LOW);//(-1),-1
    delayMicroseconds(movespeed);
    digitalWrite(pwrA,HIGH);//-1,-1
    delayMicroseconds(movespeed);
    digitalWrite(pwrB,LOW);
    digitalWrite(dirB,HIGH);//-1,(1)
    delayMicroseconds(movespeed);
    digitalWrite(pwrB,HIGH);//-1,1
    delayMicroseconds(movespeed);
    digitalWrite(pwrA,LOW);
    digitalWrite(dirA,HIGH);//(1),1
    delayMicroseconds(movespeed);
    digitalWrite(pwrA,HIGH);//1,1
  }
  BrakePos--;
}

