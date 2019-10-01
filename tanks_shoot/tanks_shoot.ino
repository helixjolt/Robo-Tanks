#include<IRremote.h>
int rec = 4;
int led1 = 9;
int led2 = 10;
int led3 = 11;
int led4 = 12;
int led5 = 13;
#define button 8
long int TEMP = 2863311530;
IRsend irsend;
IRrecv IRrec(rec);
decode_results results;
int health = 20;
void setup() {
  Serial.begin(9600);
  IRrec.enableIRIn();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(button, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(button,HIGH);
  //pinMode(10,OUTPUT);
  //analogWrite(10,255);
  //lcd.backlight();
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
}
void loop()
{
  if (digitalRead(button) == 1)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    irsend.sendNEC(0xBBBBBBBB, 32);
    Serial.println("in if");
    IRrec.enableIRIn();
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("in else");
    delay(100);
    if (IRrec.decode(&results))
    {
      if (results.value == TEMP)
      { //check for infrared signal
        if (health != 0)
        {
          Serial.println(results.value, HEX );
          delay(100);
          //print ir hex code
          Serial.println("in");
          health -= 4;
        }
        else
        {
          exit(0);
        }
        delay(100);
        //reduce health by 1
        IRrec.resume();
      }
    }
  }
  if (health < 20 && health >= 16) {
    digitalWrite(led1, LOW);
  }
  else if (health < 16 && health >= 12) {
    digitalWrite(led2, LOW);
  }
  else if (health < 12 && health >= 8) {
    digitalWrite(led3, LOW);
  }
  else if (health < 8 && health >= 4) {
    digitalWrite(led4, LOW);
  }
  else if (health < 4 && health >= 0) {
    digitalWrite(led5, LOW);
  }
}
