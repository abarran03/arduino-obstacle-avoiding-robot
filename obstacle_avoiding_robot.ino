/**
  First vesion of an obstacle avoiding robot
  @author Allan Barrantes
**/

/** Pins declaration */
// Pins declaration for ultrasonic sensor
int trigPin = 12;
int echoPin = 13;
long cm, duration;

// Pins declaration for motor 1
const int controlPin1M2 = 9;
const int controlPin2M2 = 10;
const int enablePin1 = 11;

int motorEnabledM1 = 1;
int motorSpeedM1 = 250;
int motorDirectionM1 = 0;

// Pins declaration for motor 2
const int controlPin1M1 = 5;
const int controlPin2M1 = 4;
const int enablePin2 = 3;

int motorEnabledM2 = 1;
int motorSpeedM2 = 250;
int motorDirectionM2 = 0;
const int led = 2;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led,OUTPUT);
  //Define inputs and outputs motor 1
  pinMode(controlPin1M1, OUTPUT);
  pinMode(controlPin2M1, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  //Define inputs and outputs motor 2
  pinMode(controlPin1M2, OUTPUT);
  pinMode(controlPin2M2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  //Define general inputs and outputs  
  digitalWrite(enablePin1, LOW);
  digitalWrite(enablePin2, LOW);
  digitalWrite(led,HIGH);
}

// The left motor starts to work, while the right one is turning off 
void turnLeft(){
    digitalWrite(controlPin1M2, HIGH);
    digitalWrite(controlPin2M2, LOW);
    digitalWrite(controlPin1M1, LOW);
    digitalWrite(controlPin2M1, HIGH);
}

// The right motor starts to work, while the left one is turning off 
void turnRight(){
   digitalWrite(controlPin1M2, LOW);
   digitalWrite(controlPin2M2, HIGH);
   digitalWrite(controlPin1M1, HIGH);
   digitalWrite(controlPin2M1, LOW);

}

//  pause motor to next movement
void pauseMotors(){
    digitalWrite(controlPin1M2, HIGH);
    digitalWrite(controlPin2M2, LOW);
    digitalWrite(controlPin1M1, HIGH);
    digitalWrite(controlPin2M1, LOW);  
}

// Send a signal to move both motors forward
void moveForward(){
     analogWrite(enablePin1, motorSpeedM1);
     analogWrite(enablePin2, motorSpeedM2);
}

// Send a signal to stop both motors
void stopIt(){
     analogWrite(enablePin1, 0);
     analogWrite(enablePin2, 0); 
}

// Get a distance by the ultrasonic sensor in centimeters
long getDistance(){
  long cmD = 0.0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cmD = (duration/2) / 29.1;
  Serial.print(cmD);
  Serial.print("cm");
  return cmD;
}

// main loop function 
void loop() {
  // get distance by the ultrasonic sensor
  cm = getDistance();
  delay(100);
  // if the obstacle is 20cm the robot avoids it
  if(cm > 20.0){
      digitalWrite(led,HIGH);
      Serial.println("lets go");
      pauseMotors();
      moveForward();
  } else{
      turnLeft();  
      moveForward();
  }
}
