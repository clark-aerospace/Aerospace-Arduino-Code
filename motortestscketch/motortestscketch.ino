
//open up the serial monitor and give the motor a position to go to.
//the motor will go to that position and stop
//test going forward and backwards

#define dirA 7
#define dirB 8
#define pwrA 9
#define pwrB 10


#define movespeed 800 //change the speed here, there exists a minumum for most motors

void setup() {
  pinMode(dirA,OUTPUT);
  pinMode(dirB,OUTPUT);
  pinMode(pwrA,OUTPUT);
  pinMode(pwrB,OUTPUT);//2 tied to 6; 4 tied to 8
  digitalWrite(dirA,HIGH);//HHLL
  digitalWrite(dirA,HIGH);
  digitalWrite(pwrB,HIGH);
  digitalWrite(pwrB,HIGH);
  Serial.begin(9600);
  Serial.println("settup successful");
}

long motorPos=0;
long motorTarget;
void loop() {
  Serial.println("Done");
  motorTarget=recieveOneChar();
  Serial.print("moving to position:");
  Serial.print(motorTarget);
  Serial.print("\n");
  while (motorPos<motorTarget)
    moveMotorUp();
  while (motorPos>motorTarget)
    moveMotorDown();
}
    
long recieveOneChar(){
  while (Serial.available()==0);//wait until Serial has something to read.
   return Serial.parseInt(); 
}//FOR TEMP READS

void moveMotorUp(){//ends at 1,1 & HHHH
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
  motorPos++;
}

void moveMotorDown(){
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
  motorPos--;
}
