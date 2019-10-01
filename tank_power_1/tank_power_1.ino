//TANK 1
#include<IRremote.h>
int rec = 4;

#define button 8
long int normalAttk = 2863311522;        //AAAAAA2
long int doubleDmg = 3722304978;        //DDDDDDD2
long int medkit = 3435973826;           //CCCCCCC2
long int freeze = 4294967282;           //FFFFFFF2
long int oneShot = 3149642674;          //BBBBBBB2

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
        irsend.sendNEC(0xAAAAAAA1, 32);
        Serial.println("NormalAttk Sent");
        delay(100);
        break;
      //Double Power
      case 1:
        irsend.sendNEC(0xDDDDDDD1, 32);
        Serial.println("Double Power Sent");
        delay(100);
        break;
      //MEDKIT
      case 2:
        health += 20;
        Serial.println("Medkit Used");
        delay(100);
        break;
       //OneShotKill
      case 4:
        irsend.sendNEC(0xBBBBBBB1, 32);
        Serial.println("Oneshot Sent");
        delay(100);
        flag=0;
        break;
      default:
      Serial.println("Default Case");
      delay(100);
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
          health =health-10;
          Serial.println("NormalAttk");
          Serial.println(health);
          delay(100);
        }
        else if (results.value == doubleDmg) {
          health -= 20;
          Serial.println("DoubleDmg");
          delay(100);
        }
        else if (results.value == oneShot) {
          if(health >40) health=40;
          else health=0;
          Serial.println("OneShot");
          delay(100);
        }
        else if (results.value == tdoubleDmg) {
          startM = millis();
          power = 1;
          flag = 1;
          Serial.println("Double dmg power");
          delay(100);
        }
        else if (results.value == tmedkit) {
          startM = millis();
          power = 2;
          flag = 1;
          Serial.println("MedKit power");
          delay(100);
        }
        else if (results.value == tfreeze) {
          startM = millis();
          power = 3;
          flag = 1;
          Serial.println("freeze power");
          delay(100);
        }
        else if (results.value == toneShot) {
          startM = millis();
          power = 4;
          flag = 1;
          Serial.println("One shot power");
          delay(100);
        }
        //Serial.println(power+" "+flag);
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
}
