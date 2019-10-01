//In this program the serial monitor will alternate between asking for speed and direction
//the motor will continue to move while it asks for input

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

void setup() {
  pinMode(DirectionPin,OUTPUT);
  digitalWrite(DirectionPin, HIGH);
  pinMode(BrakePin,OUTPUT);
  digitalWrite(BrakePin,LOW);
  pinMode(PWMPin,OUTPUT);
  analogWrite(PWMPin,0);
  

  
  pinMode(ThermaFlagPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(APIN), interruptTest, RISING);
  pinMode(BNOTPIN,INPUT);
  
  Serial.begin(9600);
}

void loop() {
Serial.println("give move speed 0 - 255");
analogWrite(PWMPin,recieveOneChar());
Serial.println("move direction? 0=forward - 1=back");
if (recieveOneChar()==0)
digitalWrite(DirectionPin, HIGH);
else
digitalWrite(DirectionPin, LOW);
}

long recieveOneChar(){
  while (Serial.available()==0);//wait until Serial has something to read.
   return Serial.parseInt();
}//FOR TEMP READS

void interruptTest(){}
