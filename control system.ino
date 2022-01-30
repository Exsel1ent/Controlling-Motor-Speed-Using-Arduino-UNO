// Motor A connections
#include <Wire.h>
int enA = 5;
int in1 = 4;
int in2 = 3;
//int buzz = 1;
long countdown_time = 120, initialsecond = 0, spd[4], RPM = 0,countdowntime_seconds = 0, selisih = 0, starttime = 0;
float value = 0;
float rev = 0;
long rpm;
int oldtime = 0;
int time;
int pwmStorage = 0;


void isr() {
  rev++;
}

void setup() {
   Serial.begin(9600);
 Serial.println("CLEARDATA");
 Serial.println("LABEL,Time,Started Time,Register value");
 Serial.println("RESETTIMER");
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //pinMode(buzz, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  pwmStorage = 3000; // Read number of RPM
   int potValue = pwmStorage; 
   RPM = pwmStorage;
  float pwmOutput = map(potValue, 0, 13000, 0 , 255); // Map the potentiometer value from 0 to 255
  analogWrite(enA, pwmOutput );
  //digitalWrite(buzz, LOW);
  initialsecond = 0;
  starttime = countdown_time-2;
  //Serial.print("time   ");
  //Serial.println(starttime);
        attachInterrupt(digitalPinToInterrupt (2), isr, RISING); //interrupt pin
        
}

void loop() {
  if (countdowntime_seconds >= 0) {
if (initialsecond == 0) {
      initialsecond = millis() / 1000;
    }
    countdowntime_seconds = countdown_time - (millis() / 1000) + initialsecond;
      long countdown_minute = (countdowntime_seconds / 60);
      long counddown_sec = countdowntime_seconds % 60;
     Serial.println(countdowntime_seconds);
     

//tachometer
delay(1000);
detachInterrupt(digitalPinToInterrupt(2));    
  time = millis() - oldtime;    
  //Serial.print(time);
  //Serial.print("  ");
  rpm = (rev / (time*2.1)) * 60000;   
  int sensorValue = rpm;
  Serial.print("DATA,TIME,TIMER,");
  Serial.println(sensorValue);
  Serial.print("time   ");
  Serial.println(starttime);
  Serial.println(countdowntime_seconds);
Serial.println(selisih);

         
  rev = 0;
  //Serial.println(rpm);
  //Serial.println(rpm);
   attachInterrupt(digitalPinToInterrupt (2), isr, RISING);
   oldtime = millis(); 

      //ketentuan motor
       if (countdowntime_seconds % 2 == 0 && starttime > countdowntime_seconds ) {
         
        selisih = RPM - rpm;             
        //close loop 
       
         if (selisih >= 3000){
        //defide = selisih/1000; 
        pwmStorage = pwmStorage + 2000;  
        }
         if (selisih <= -3000){
        //defide = selisih/1000;
        pwmStorage = pwmStorage - 2000;  
        }
         if (selisih >= 1000 && selisih < 3000){
        //defide = selisih/1000; 
        pwmStorage = pwmStorage + 1000;  
        }
         if (selisih <= -1000 && selisih > -3000){
        //defide = selisih/1000;
        pwmStorage = pwmStorage - 1000;  
        }
         if (selisih >= 400 && selisih < 1000){
        //defide = selisih/100;
        pwmStorage = pwmStorage + 200;  
        }
         if (selisih <= -400 && selisih > -1000){
        //defide = selisih/100;
        pwmStorage = pwmStorage - 200;  
        }
         if (selisih >= 100 && selisih < 400){
        //defide = selisih/100;
        pwmStorage = pwmStorage + 100;  
        }
         if (selisih <= -100 && selisih > -400){
        //defide = selisih/100;
        pwmStorage = pwmStorage - 100;  
        }
         if (selisih >= 40 && selisih < 100){
        //defide = selisih/10;
        pwmStorage = pwmStorage + 20;    
        }
         if (selisih <= -40 && selisih > -100){
        //defide = selisih/10;
        pwmStorage = pwmStorage - 20;    
        }
        if (selisih >= 10 && selisih < 40){
        //defide = selisih/100;
        pwmStorage = pwmStorage + 10;  
        }
         if (selisih <= -10 && selisih > -40){
        //defide = selisih/100;
        pwmStorage = pwmStorage - 10;  
        }
         if (selisih >= 1 && selisih < 10){
        pwmStorage = pwmStorage + selisih;    
        }
         if (selisih <= -1 && selisih > -10){
        pwmStorage = pwmStorage - selisih;    
        }
        if (selisih == 0){ 
        pwmStorage = pwmStorage;
        }  
        //loop RPM
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);        
        int potValue = pwmStorage; // Read number of RPM
        float pwmOutput = map(potValue, 0, 13000, 0 , 255); // Map the potentiometer value from 0 to 255
        analogWrite(enA, pwmOutput );       
       }
}
   if (countdowntime_seconds == 0) {
   
      digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
   int potValue = 0000; // Read potentiometer value
  float pwmOutput = map(potValue, 0, 13000, 0 , 255); // Map the potentiometer value from 0 to 255
  analogWrite(enA, pwmOutput );
}  
}
