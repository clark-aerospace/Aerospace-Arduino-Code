const char DirectionPin=1;
const char BrakePin=4;
const char PWMPin=5;
const char ThermaFlagPin=2;
const char APIN=3;
const char BNOTPIN=7;

int currentAlt, currentSpeed, optimalSpeed;//actualySpeed should be adjusted to meet the optimal speed

volatile int brakePos=0;
bool brakeGoingUp=false;//true=up, false=down
int brakeSpd=0;

void interuptTest();//

void setup() {
  pinMode(DirectionPin,OUTPUT);
  pinMode(BrakePin,OUTPUT);
  pinMode(PWMPin,OUTPUT);
  
  pinMode(ThermaFlagPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(APIN), interruptTest, RISING);
  pinMode(BNOTPIN,INPUT);
  Serial.begin(9600);
}

char tempinput;
void loop() {
  
  //readdata
  Serial.print("WAITING FOR ALT AND VEL:");
  currentAlt=recieveOneChar();  //TEMP RECIEVE
  currentSpeed=recieveOneChar();//TEMP RECIEVE
  Serial.print(currentAlt); //START TEMPRINT
  Serial.print(":");
  Serial.print(currentSpeed);
  Serial.print("\n");       //END TEMPRINT
      
  optimalSpeed=getOptimalSpeed(currentAlt);//now we have the speed we should be at
  
  Serial.print(optimalSpeed); //Start tempprint
  Serial.print(":");
  Serial.print(currentSpeed);
  Serial.print("\n");         //end tempprint
  
  //set optimalBrakePos
  if (currentSpeed>optimalSpeed){
    movebrakesup(true);//movebrakes up
  }else{
    movebrakesup(false);//movebrakes down
  }
  brakeSpd=(abs(currentSpeed-optimalSpeed));

  //check motorpos
  
}

long recieveOneChar(){
  while (Serial.available()==0);//wait until Serial has something to read.
   return Serial.parseInt(); 
}//FOR TEMP READS

int getOptimalSpeed(int Alt){//plots the relationship between altitude and speed of the 'perfect' flight
  return ((-Alt/2)+50);
}

void interruptTest(){
  Serial.println("interrupted");
  if (brakeGoingUp)
  brakePos++;
  else
  brakePos--;
  Serial.print(brakePos);
}

void movebrakesup(boolean up){
  if (up){
  Serial.println("moving brakes up");
  brakeGoingUp=true;
  }
  else{
  Serial.println("moving brakes down");
  brakeGoingUp=false;
  }
}

