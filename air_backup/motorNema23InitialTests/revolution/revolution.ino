#include <AccelStepper.h>
#include <elapsedMillis.h>
#include <Adafruit_NeoPixel.h>


#define dirPin1 12
#define stepPin1 13
#define motorInterfaceType 1

#define RXD2 16
#define TXD2 17

AccelStepper stepper1 = AccelStepper(motorInterfaceType, stepPin1, dirPin1);
elapsedMillis printTime;
int motorSpeed = 106;
int stepCount = 0;
boolean resetSent = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Started the sender (white board");
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(500);
  stepper1.setSpeed(motorSpeed);
}

void loop() {
  if (printTime >= 2000) {
    stepCount++;
    delay(10);
    
    printTime = 0;
    float mSpeed = stepper1.speed();
    Serial.print(mSpeed);
    Serial.print("  ");
    Serial.println(stepper1.currentPosition());
    resetSent = false;
    
    if (stepCount == 30) { // reset motor to initial position
      if (resetSent == false){
        Serial2.write("reset\n");
        resetSent = true;
      }
      
      stepCount = 0;
      stepper1.moveTo(0);
      stepper1.runToPosition();
      delay(1000);
      printTime = 0;
      stepper1.setCurrentPosition(0);
      stepper1.setSpeed(motorSpeed);
    } else {
      if (stepCount == 1) {
        Serial2.write("1\n");
      }
      if (stepCount == 2) {
        Serial2.write("2\n");
      }
      if (stepCount == 3) {
        Serial2.write("3\n");
      }
      if (stepCount == 4) {
        Serial2.write("4\n");
      }
      if (stepCount == 5) {
        Serial2.write("5\n");
      }
      if (stepCount == 6) {
        Serial2.write("6\n");
      }
      if (stepCount == 7) {
        Serial2.write("7\n");
      }
      if (stepCount == 8) {
        Serial2.write("8\n");
      }
      if (stepCount == 9) {
        Serial2.write("9\n");
      }
      if (stepCount == 10) {
        Serial2.write("10\n");
      }
      if (stepCount == 11) {
        Serial2.write("11\n");
      }
      if (stepCount == 12) {
        Serial2.write("12\n");
      }
      if (stepCount == 13) {
        Serial2.write("13\n");
      }
      if (stepCount == 14) {
        Serial2.write("14\n");
      }
      if (stepCount == 15) {
        Serial2.write("15\n");
      }
      if (stepCount == 16) {
        Serial2.write("16\n");
      }
      if (stepCount == 17) {
        Serial2.write("17\n");
      }
      if (stepCount == 18) {
        Serial2.write("18\n");
      }
      if (stepCount == 19) {
        Serial2.write("19\n");
      }
      if (stepCount == 20) {
        Serial2.write("20\n");
      }
      if (stepCount == 21) {
        Serial2.write("21\n");
      }
      if (stepCount == 22) {
        Serial2.write("22\n");
      }
      if (stepCount == 23) {
        Serial2.write("23\n");
      }
      if (stepCount == 24) {
        Serial2.write("24\n");
      }
      if (stepCount == 25) {
        Serial2.write("25\n");
      }
      if (stepCount == 26) {
        Serial2.write("26\n");
      }
      if (stepCount == 27) {
        Serial2.write("27\n");
      }
      if (stepCount == 28) {
        Serial2.write("28\n");
      }
      if (stepCount == 29) {
        Serial2.write("29\n");
      }
      if (stepCount == 30) {
        Serial2.write("30\n");
      }
    }
  }
  stepper1.runSpeed();
}



//  stepper1.moveTo(1600);
//  stepper1.runToPosition();
//
//  delay(1000);
//  
//  stepper1.moveTo(0);
//  stepper1.runToPosition();
//  delay(1000);
