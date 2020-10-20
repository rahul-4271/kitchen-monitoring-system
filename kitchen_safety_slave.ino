#include <LiquidCrystal.h>
#include <Wire.h>
#define led 6
unsigned int timer = 10;
int w,x,y,z,k=0,k1=0,k2=0,val ;


LiquidCrystal lcd(12,11,10,9,8,7);

void setup() {
 pinMode(led, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
    
  Wire.onReceive(receiveEvent);

 
  lcd.begin(16,2); 
  Serial.begin(9600); 
}

void receiveEvent(int bytes) {
  w = Wire.read();
  x = Wire.read();    // read one character from the I2C
  y = Wire.read();
  z = Wire.read();
}


void loop() {
  lcd.clear();
  if(w==0 && x==0 && y==0){
    k1=0;
    lcd.print("KITCHEN IS SAFE");
  }
  if(w==1 && x==0 && y==0 ){
    lcd.print("KITCHEN IS SAFE");
    lcd.setCursor(0,1);
    lcd.print("ROOM IS OCCUPIED");
  }
    if(w==1 && (x==1 || y==1) ){//&& k2==1
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("STOVE IS ON");
    lcd.setCursor(0,1);
  lcd.print("ROOM IS OCCUPIED");
  }
  if((x==1 || y==1)){

           
if(w==0)
{
  timer= timer-1;
  k1=1;
}
else if(w==1)
{
  timer = 10;
  k=0;
  k1=0;
  k2=0;
}
//else
if(timer==0)
{
  k=2;
  k2=1;
}

  }
//  lcd.setCursor(0,0);

  Serial.print(w); 
  Serial.print(x);
  Serial.print(z);
  Serial.print(y);
if (z==1){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAS IS LEAKING");
  lcd.setCursor(0,1);
  lcd.print("CHECK YOUR KITCHEN");
  delay(200);
  for (int positionCounter = 0; positionCounter < 3; positionCounter++) {
    lcd.scrollDisplayLeft();   
    delay(100);
  }
  for (int positionCounter = 0; positionCounter < 3; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(100);
  }
}
 if ( k1==1){
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("STOVE IS ON");
    lcd.setCursor(0,1);
  lcd.print("ROOM IS EMPTY");
 }
  if ( k2==1){
    lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("!!DANGER!!");
    lcd.setCursor(0,1);
  lcd.print("STOVE IS ON");
 }
 if ( k==2){//timer==0&& x==1 && y==1&&
  digitalWrite(led, HIGH);
val='1';
 }
//  if (timer!=0&& x==1 && y==1){
//  digitalWrite(led, LOW);
//  
// }  
if ( k!=2){
  digitalWrite(led, LOW);
val='0';
}
 delay(500);

}
//void requestEvent()                                //This Function is called when Master wants value from slave
//{
//  Wire.write(val);    
//}
