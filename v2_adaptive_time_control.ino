/*
=====================================================================================
PROJECT: Electromagnetic accelerator
COURSE: Module 3 Project - Applied Physics (University of Twente)
AUTHOR: Joëlle de Vries
DESCRIPTION: 
This code controls an electromagnetic accelerator with 4 coils. It uses pairs of infrared 
sensors to detect the position of a ball, calculates the time if takes to pass both sensors
and adjusts the time the coil is turned on. This is all done to maximize the speed of the ball 
in the accelerator.
=====================================================================================
 */

unsigned long timeStart;
unsigned long timeStop;
long fet_delay = 100; //default pulse width in ms
int state = 0; // initial state of the current sensor the ball passes

long pulse_factor = 100; 

//-------coil 1 configuration------------------------------------------------------
const int ir_8 = 11; //start sensor
const int ir_1 = 4; //stop sensor
const int fet_1 =  13; //coil
const long dSens_8_1 = 125; //distance between start and stop sensor in mm
const long dCoil_1 = 67; //distance from stop sensor to distance of coil in mm

//--------coil 2 configuration-----------------------------------------------------
const int ir_2 = 9; //start sensor
const int ir_3 = 6; //stop sensor
const int fet_2 =  2; //coil
const long dSens_2_3 = 139; //distance between start and stop sensor in mm
const long dCoil_2 = 53; //distance from stop sensor to distance of coil in mm


//--------coil 3 configuration-----------------------------------------------------
const int ir_4 = 7; //start sensor
const int ir_5 = 8; //stop sensor
const int fet_3 =  12; //coil
const long dSens_4_5 = 140; //distance between start and stop sensor in mm
const long dCoil_3 = 52; //distance from stop sensor to distance of coil in mm


//--------coil 4 configuration-----------------------------------------------------
const int ir_6 = 5; //start sensor
const int ir_7 = 10; //stop sensor
const int fet_4 =  3; //coil
const long dSens_6_7 = 132; //distance between start and stop sensor in mm
const long dCoil_4 = 60; //distance from stop sensor to distance of coil in mm

void setup() {
  //set gate pins at inputs and outputs
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
  // makes sure all coils are turned off
  digitalWrite(fet_1, LOW);
  digitalWrite(fet_2, LOW);
  digitalWrite(fet_3, LOW);
  digitalWrite(fet_4, LOW);

  Serial.begin(9600);
}

void loop() {

  //--------coil 1 controller-------------------------------------
  //record timestamp when ball passes start sensor
  if (digitalRead(ir_8) == 1 && state != ir_8) {
    timeStart = millis();
    state = ir_8;
    
  }

  //trigger coil and calculates pulse width when ball passes stop sensor
  if (digitalRead(ir_1)==1) {
    digitalWrite(fet_1,HIGH); //turn coil on

    if (state == ir_8) {
      timeStop = millis();
      fet_delay = pulseWidthMs(timeStart, timeStop, dSens_8_1, dCoil_1);
    }

    delay(fet_delay); //keep coil on for calculated duration
    digitalWrite(fet_1,LOW); //turn coil off
  }

  //--------coil 2 controller-------------------------------------
  if (digitalRead(ir_2) == 1 && state != ir_2) {
    timeStart = millis();
    state= ir_2;
  }

  if (digitalRead(ir_3)==1) {
    digitalWrite(fet_2,HIGH);

    if (state == ir_2) {
      timeStop = millis();
      fet_delay = pulseWidthMs(timeStart, timeStop, dSens_2_3, dCoil_2);
    }

    delay(fet_delay);
    digitalWrite(fet_2,LOW);
  }
  
  //--------coil 3 controller-------------------------------------
  if (digitalRead(ir_4) == 1 && state != ir_4) {
    timeStart = millis();
    state= ir_4;
  }

  if (digitalRead(ir_5)==1) {
    digitalWrite(fet_3,HIGH);

    if (state == ir_4) {
      timeStop = millis();
      fet_delay = pulseWidthMs(timeStart, timeStop, dSens_4_5, dCoil_3);
    }

    delay(fet_delay);
    digitalWrite(fet_3,LOW);
  }
  
//--------coil 4 controller-------------------------------------
  if (digitalRead(ir_6) == 1 && state != ir_6) {
    timeStart = millis();
    state= ir_6;
  }

  if (digitalRead(ir_7)==1) {
    digitalWrite(fet_4,HIGH);

    if (state == ir_6) {
      timeStop = millis();
      fet_delay = pulseWidthMs(timeStart, timeStop, dSens_6_7, dCoil_4);
    }

    delay(fet_delay);
    digitalWrite(fet_4,LOW);
  }
  
}


/*
function calculates pulse width in ms to control fet

Args: 
  long t1   -start timestamp [ms]
  long t2   -stop timestamp [ms]
  long xS  -distance from start sensor to stop sensor [mm]
  long xC  -distance from stop sensor to center coil [mm]
  
Returns:
  long fetOnTime   -   pulsewidth [ms]
*/
long pulseWidthMs(long t1, long t2, long xS, long xC) {
  long dt = t2 - t1;
  //long v = xS / dt;
  long fetOnTime = (pulse_factor/100) * (xC * dt / xS);
  //.Serial.print("x = ");
  Serial.print(xS);
  Serial.print(",");
  //Serial.print("; dt = ");
  Serial.println(dt);
  return fetOnTime;
}
