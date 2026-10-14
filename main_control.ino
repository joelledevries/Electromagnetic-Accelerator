unsigned long timeStart;
unsigned long timeStop;
long fet_delay = 100; //ms
int state = 0;

long pulse_factor = 100;
//-------coil 1------------------------------------------------------
const int ir_8 = 11;
const int ir_1 = 4;
const int fet_1 =  13;// the number of the LED pin
const long dSens_8_1 = 125; //mm
const long dCoil_1 = 67; //mm

//--------coil 2-----------------------------------------------------
const int ir_2 = 9;
const int ir_3 = 6;
const int fet_2 =  2;// the number of the LED pin
const long dSens_2_3 = 139; //mm
const long dCoil_2 = 53; //mm


//--------coil 3-----------------------------------------------------
const int ir_4 = 7;
const int ir_5 = 8;
const int fet_3 =  12;// the number of the LED pin
const long dSens_4_5 = 140; //mm
const long dCoil_3 = 52; //mm


//--------coil 4-----------------------------------------------------
const int ir_6 = 5;
const int ir_7 = 10;
const int fet_4 =  3;// the number of the LED pin
const long dSens_6_7 = 132; //mm
const long dCoil_4 = 60; //mm

void setup() {
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

  digitalWrite(fet_1, LOW);
  digitalWrite(fet_2, LOW);
  digitalWrite(fet_3, LOW);
  digitalWrite(fet_4, LOW);

  Serial.begin(9600);
}

void loop() {

  //--------coil 1-------------------------------------
  //start sensor
  if (digitalRead(ir_8) == 1 && state != ir_8) {
    timeStart = millis();
    state = ir_8;
    
  }

  //stop sensor
  if (digitalRead(ir_1)==1) {
    digitalWrite(fet_1,HIGH);

    if (state == ir_8) {
      timeStop = millis();
      fet_delay = pulseWidthMs(timeStart, timeStop, dSens_8_1, dCoil_1);
    }

    delay(fet_delay);
    digitalWrite(fet_1,LOW);
  }

  //--------coil 2-------------------------------------
  //start sensor
  if (digitalRead(ir_2) == 1 && state != ir_2) {
    timeStart = millis();
    state= ir_2;
  }

  //stop sensor
  if (digitalRead(ir_3)==1) {
    digitalWrite(fet_2,HIGH);

    if (state == ir_2) {
      timeStop = millis();
      fet_delay = pulseWidthMs(timeStart, timeStop, dSens_2_3, dCoil_2);
    }

    delay(fet_delay);
    digitalWrite(fet_2,LOW);
  }
  
  //--------coil 3-------------------------------------
  //start sensor
  if (digitalRead(ir_4) == 1 && state != ir_4) {
    timeStart = millis();
    state= ir_4;
  }

  //stop sensor
  if (digitalRead(ir_5)==1) {
    digitalWrite(fet_3,HIGH);

    if (state == ir_4) {
      timeStop = millis();
      fet_delay = pulseWidthMs(timeStart, timeStop, dSens_4_5, dCoil_3);
    }

    delay(fet_delay);
    digitalWrite(fet_3,LOW);
  }
  
//--------coil 4-------------------------------------
  //start sensor
  if (digitalRead(ir_6) == 1 && state != ir_6) {
    timeStart = millis();
    state= ir_6;
  }

  //stop sensor
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
