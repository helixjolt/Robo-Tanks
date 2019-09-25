//TANK ZONE
#include<IRremote.h>
int rec = 4;
IRsend irsend;
IRrecv IRrec(rec);
decode_results results;

int led1 = 9; //RED OneShot
int led2 = 10; //Orange DoubleDamage
int led3 = 11; //Green Medkit
int led4 = 12; //Blue Freeze
long power;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IRrec.enableIRIn();

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IRrec.decode(&results)) {
    power = random(1, 5);
    switch (power) {
      case 1:
        irsend.sendNEC(0xDDDDDDDD, 32);
        digitalWrite(led2, HIGH);
        delay(5000);
        digitalWrite(led2, LOW);
        Serial.print("DoubleDmg to Tanks");
        break;
      case 2:
        irsend.sendNEC(0xCCCCCCCC, 32);
        digitalWrite(led3, HIGH);
        delay(5000);
        digitalWrite(led3, LOW);
        Serial.print("Medkit to Tanks");
        break;
      case 3:
        irsend.sendNEC(0xFFFFFFFF, 32);
        digitalWrite(led4, HIGH);
        delay(5000);
        digitalWrite(led4, LOW);
        Serial.print("Freeze to Tanks");
        break;
      case 4:
        irsend.sendNEC(0xBBBBBBBB, 32);
        digitalWrite(led1, HIGH);
        delay(5000);
        digitalWrite(led1, LOW);
        Serial.print("OneShot to Tanks");
        break;
    }
    IRrec.resume();
  }
}
