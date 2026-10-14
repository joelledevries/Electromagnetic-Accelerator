/*
=====================================================================================
PROJECT: Electromagnetic accelerator
COURSE:  Module 3 Project - Applied Physics (University of Twente)
AUTHOR:  Joëlle de Vries
DESCRIPTION: 
This code controls an electromagnetic accelerator with 4 coils. It uses pairs of infrared 
sensors to detect the position of a ball and turns the coil on and off respectively. 
The sensors are positioned in such a way that the coil gets turned off when the ball is exactly 
in the middle of the coil.
 =====================================================================================
 */


//-------coil 1 configuration------------------------------------------------------
const int ir_8 = 11; //start sensor
const int ir_1 = 4; //stop sensor
const int fet_1 =  13;// the number of the LED pin
const long dSens_8_1 = 125; //distance between start and stop sensor in mm
const long dCoil_1 = 67; //distance from stop sensor to distance of coil in mm

//--------coil 2 configuration-----------------------------------------------------
const int ir_2 = 9; //start sensor
const int ir_3 = 6; //stop sensor
const int fet_2 =  2;// the number of the LED pin
const long dSens_2_3 = 139; //distance between start and stop sensor in mm
const long dCoil_2 = 53; //distance from stop sensor to distance of coil in mm


//--------coil 3 configuration-----------------------------------------------------
const int ir_4 = 7; //start sensor
const int ir_5 = 8; //stop sensor
const int fet_3 =  12;// the number of the LED pin
const long dSens_4_5 = 140; //distance between start and stop sensor in mm
const long dCoil_3 = 52; //distance from stop sensor to distance of coil in mm


//--------coil 4 configuration-----------------------------------------------------
const int ir_6 = 5; //start sensor
const int ir_7 = 10; //stop sensor
const int fet_4 =  3;// the number of the LED pin
const long dSens_6_7 = 132; //distance between start and stop sensor in mm
const long dCoil_4 = 60; //distance from stop sensor to distance of coil in mm

void setup() {
  //MOSFET fate pins input and output
  pinMode(fet_1, OUTPUT);
  pinMode(fet_2, OUTPUT);
  pinMode(fet_3, OUTPUT);
  pinMode(fet_4, OUTPUT);
  pinMode(ir_1, INPUT);
  pinMode(ir_2, INPUT);
  pinMode(ir_3, INPUT);
  pinMode(ir_4, INPUT);
  pinMode(ir_5, INPUT);
  pinMode(ir_6, INPUT);
  pinMode(ir_7, INPUT);
  pinMode(ir_8, INPUT);
  //make sure all coils are off
  digitalWrite(fet_1, LOW);
  digitalWrite(fet_2, LOW);
  digitalWrite(fet_3, LOW);
  digitalWrite(fet_4, LOW);
}

void loop() {

  //--------coil 1 controller-------------------------------------
  //turn on coil when sensor is detecting
  if (digitalRead(ir_1)==1) {
    digitalWrite(fet_1,HIGH);
  }

  //turn off coil when sensor is detecting
  if (digitalRead(ir_2)==1) {
    digitalWrite(fet_1,LOW);
    timeStart = millis();
  }

  //--------coil 2-------------------------------------
  if (digitalRead(ir_3)==1) {
    digitalWrite(fet_2,HIGH);
  }

  if (digitalRead(ir_4)==1) {
    digitalWrite(fet_2,LOW);
  }
  //--------coil 3-------------------------------------
  if (digitalRead(ir_5)==1) {
    digitalWrite(fet_3,HIGH);
  }

  if (digitalRead(ir_6)==1) {
    digitalWrite(fet_3,LOW);
  }

  //--------coil 4-------------------------------------
  if (digitalRead(ir_7)==1) {
    digitalWrite(fet_4,HIGH);
  }

  if (digitalRead(ir_8)==1) {
    digitalWrite(fet_4,LOW);
  }
