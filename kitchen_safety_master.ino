#define pir 2
#define flame1 3
#define flame2 4
#define gas 5
#define buzzer 6
#include "OneButton.h"
#include <Wire.h>
int pirs,fs1,fs2,gs;
int a,b,c,d,t=0;
//byte MasterReceive;
OneButton button(A1, true);
void setup(){
  Serial.begin(9600);
  Wire.begin(); 
  pinMode(pir, INPUT);
  pinMode(gas, INPUT);
  pinMode(flame1, INPUT);
  pinMode(flame2, INPUT);
  pinMode(buzzer, OUTPUT);
  button.attachDoubleClick(doubleclick);
}
void loop(){
  a=digitalRead(gas);
  b=digitalRead(pir);
  c=digitalRead(flame1);
  d=digitalRead(flame2);
  button.tick();  
 
  if(digitalRead(gas)==HIGH){
    gs=true;
    digitalWrite(buzzer,HIGH);
  }
   if(digitalRead(gas)==LOW){
    gs=false;
    digitalWrite(buzzer,LOW);
  }
  
  if(b==HIGH){
   pirs=true;
    
  }
   if(b==LOW){
    pirs=false;
  }
    if(c==HIGH){
    fs1=1;   
  }
   if(c==LOW){
    fs1=0;
  }  
    if(d==HIGH){
    fs2=1;   
  }
   if(d==LOW){
    fs2=0;
  }
  if(gs==true){
    button.tick();

  }


  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(pirs);             
  Wire.write(fs1);
  Wire.write(fs2);
  Wire.write(gs);
  Wire.endTransmission(); 
  delay(500);
}


// this function will be called when the button was pressed 2 times in a short timeframe.
void doubleclick() {
  digitalWrite(buzzer,LOW);
}
