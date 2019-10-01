//TANK 2
#include<IRremote.h>
int rec = 4;

#define button 8
long int normalAttk = 2863311521;        //AAAAAA1
long int doubleDmg = 3722304977;        //DDDDDDD1
long int medkit = 3435973825;           //CCCCCCC1
long int freeze = 4294967281;           //FFFFFFF1
long int oneShot = 3149642673;          //BBBBBBB1

long int tdoubleDmg = 3722304989;        //DDDDDDDD  power=1
long int tmedkit = 3435973836;           //CCCCCCCC  power=2
long int tfreeze = 4294967295;           //FFFFFFFF  power=3
long int toneShot = 3149642683;          //BBBBBBBB  power=4

IRsend irsend;
IRrecv IRrec(rec);
decode_results results;
int health = 100;
int power = 0;
int flag = 0;

unsigned long startM;
unsigned long currentM;

int led1 = 9;     
int led2 = 10;    
int led3 = 11;    
int led4 = 12;    
int led5 = 13;    

void setup() {
  Serial.begin(9600);
  IRrec.enableIRIn();
  pinMode(button, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
}

void loop()
{
  if (digitalRead(button) == 1)       //D8 of arduino is connected to D4 of nodeMCU
  {
    switch (power) {
      //Normal shoot
      case 0:
        //digitalWrite(LED_BUILTIN, HIGH);
        irsend.sendNEC(0xAAAAAAA2, 32);
        Serial.print("NormalAttk Sent");
        break;
      //Double Power
      case 1:
        irsend.sendNEC(0xDDDDDDD2, 32);
        Serial.print("Double Power Sent");
        break;
      //MEDKIT
      case 2:
        health += 20;
        Serial.print("Medkit Used");
        break;
       //OneShotKill
      case 4:
        irsend.sendNEC(0xBBBBBBB2, 32);
        Serial.print("Oneshot Sent");
        flag=0;
        break;
      default:
      Serial.print("Default Case");
      break;
    }
    IRrec.enableIRIn();
  }
  else
  {
    delay(100);
    ///freeze and health
    if (health > 0 && power != 3) {
      if (IRrec.decode(&results)) {
        if (results.value == normalAttk) {
          health -= 10;
          Serial.print("NormalAttk");
        }
        else if (results.value == doubleDmg) {
          health -= 20;
          Serial.print("DoubleDmg");
        }
        else if (results.value == oneShot) {
          if(health >40) health=40;
          else health=0;
          Serial.print("OneShot");
        }
        else if (results.value == tdoubleDmg) {
          startM = millis();
          power = 1;
          flag = 1;
          Serial.print("Double dmg power");
        }
        else if (results.value == tmedkit) {
          startM = millis();
          power = 2;
          flag = 1;
          Serial.print("MedKit power");
        }
        else if (results.value == tfreeze) {
          startM = millis();
          power = 3;
          flag = 1;
          Serial.print("freeze power");
        }
        else if (results.value == toneShot) {
          startM = millis();
          power = 4;
          flag = 1;
          Serial.print("One shot power");
        }
        Serial.print(power+" "+flag);
        IRrec.resume();
      }
      currentM = millis();
      if ((currentM <= startM + 45000) && (flag == 1)) {
        flag = 0;
        power = 0;
      }
    }
  }
  if (health>80) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    }
  else if (health <=80 && health > 60) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }
  else if (health <= 60 && health > 40) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }
  else if (health <= 40 && health >20) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }
  else if (health <= 20 && health > 0) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }
    Serial.println("Health"+health);

}
