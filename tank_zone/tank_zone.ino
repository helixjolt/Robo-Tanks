//TANK ZONE
#include<IRremote.h>
int rec = 4;
IRsend irsend;
IRrecv IRrec(rec);
decode_results results;

int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;

int ir=3;

long power;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IRrec.enableIRIn();
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IRrec.decode(&results)) {
    power = random(1, 5);
    Serial.print(power);
    switch (power) {
      case 1:
        irsend.sendNEC(0xDDDDDDDD, 32);
        RGB_color(187,128,7);
        delay(5000);
        RGB_color(0,0,0);
        Serial.print("DoubleDmg to Tanks");
        IRrec.resume();
        break;
      case 2:
        irsend.sendNEC(0xCCCCCCCC, 32);
        RGB_color(0,255,0);
        delay(5000);
        RGB_color(0,0,0);
        Serial.print("Medkit to Tanks");
        IRrec.resume();
        break;
      case 3:
        irsend.sendNEC(0xFFFFFFFF, 32);
        RGB_color(72,202,217);
        delay(5000);
        RGB_color(0,0,0);
        Serial.print("Freeze to Tanks");
        IRrec.resume();
        break;
      case 4:
        irsend.sendNEC(0xBBBBBBBB, 32);
        RGB_color(255,0,0);
        delay(5000);
        RGB_color(0,0,0);
        Serial.print("OneShot to Tanks");
        IRrec.resume();
        break;
    }
      IRrec.enableIRIn();

  }
  //Serial.print("loop\n");
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
