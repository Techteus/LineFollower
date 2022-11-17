#include "CodeItself6.h"



/*
>>>>>>>>>>>>>>>     DEFINE SECTION     <<<<<<<<<<<<<<< 
*/

// Important values to be utilized later in
#define RUNTIME 22000                                 // Defines the time the line follower must go over the circuit
#define kP 0.10                                       // Defines the value of the constant for Proportional
#define kD 2.25                                       // Defines the value of the constant for Derivative
#define FULL_ON 254                                   // Speed when on a straight line



/*
>>>>>>>>>>>>>>>     ENGINE SETUP     <<<<<<<<<<<<<<<
*/

DCMotorController rightEngine = DCMotorController(6,2,4);  //Set pins for the engines (enable, in1, in2);
DCMotorController leftEngine  = DCMotorController(3,5,7);  //Set pins for the engines (enable, in1, in2);
  
void GeneralFunctions::testEngines(){
  //Goes forward
  while(millis()<1000){
    wheelsController(200,200);
  }
  //Goes backward
  while(millis()<2000){
    wheelsController(-200,-200);
  }
  //Goes right
  while(millis()<3000){
    wheelsController(-200,200);
  }
  //Goes left
  while(millis()<4000){
    wheelsController(200,-200);
  }
  //Stay still
  while(millis()<5000){
    wheelsController(0,0);
  }
}

void GeneralFunctions::wheelsController(int leftPower, int rightPower){
  leftEngine.write(leftPower);
  rightEngine.write(rightPower);
}



/*
>>>>>>>>>>>>>>>     QTR SENSORS SETUP     <<<<<<<<<<<<<<<
*/

QTRSensors qtrA;
const uint8_t sensorCount = 6;                        // Num of sensors
uint16_t sensors[sensorCount];                        // Array of sensors
uint16_t arraySensor[]{A0,A1,A2,A3,A4,A5};            // for Raw values reading

void GeneralFunctions::setSensors (){
  qtrA.setTypeAnalog();
  qtrA.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, sensorCount);
  for (uint16_t i=0;i<50;i++){
    qtrA.calibrate();
    delay(10);
  }
}

void GeneralFunctions::getSensorValues(){
  for(int i=0;i<sensorCount;i++){
    // This sequence prints the sensor max values attatched to its sensor
    Serial.print(analogRead(arraySensor[i])); 
    Serial.print(" | ");
  }
  Serial.println("\n");
  delay(1000);
}

void GeneralFunctions::getPosition(){
  // receives position based on the position of sensor over the line
  uint16_t position = qtrA.readLineWhite(sensors); 
  for(uint8_t i=0;i<sensorCount;i++){
    Serial.print(sensors[i]);
    Serial.print('\t');
  }
  Serial.println(position);
  delay(250);
}



/*
>>>>>>>>>>>>>>>     PID: GETTING ERROR, MAKING THE CALCULUS, RUNNING     <<<<<<<<<<<<<<< 
*/

void GeneralFunctions::followTheWhiteLine(){
  // allocates previous error
  static int previousError=0;
  //gets position
  uint16_t position = qtrA.readLineWhite(sensors); 
  //defines the value of the error based on a calculus
  //error goes rom 0 to 5000, our goal is to set the robot
  //right at the two middle sensors, which would be 2500
  //at this point, we have no error, so error should equal to 0
  //that's why we subtract position from 2500
  int error = position - 2500;
  //the value that's gon' be put on the wheels, the pwm value
  int speed = (kP*error)+kD*(error-previousError);
  previousError=error;
  if(error<-2300){
    wheelsController(-FULL_ON, FULL_ON);
  }else if(error>2300){
    wheelsController(FULL_ON, -FULL_ON);
  }else{
    int leftEngineSpeed = FULL_ON - speed;
    int rightEngineSpeed = FULL_ON + speed;
    if(leftEngineSpeed>254){
       leftEngineSpeed = 254;
    }else if(leftEngineSpeed<1){
       leftEngineSpeed = 1;
    }
    if(rightEngineSpeed>254){
       rightEngineSpeed = 254;
    }else if(rightEngineSpeed<1){
       rightEngineSpeed = 1;
    }
    wheelsController(leftEngineSpeed, rightEngineSpeed);
  }
}
