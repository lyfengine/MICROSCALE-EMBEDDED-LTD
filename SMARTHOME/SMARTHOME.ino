#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
#include <SPI.h>
#include <Adafruit_CC3000.h>
#include <BlynkSimpleCC3000.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#define SAMSUNG
#define SEND_SAMSUNG 

IRsend irsend;
// Power ON/OFF
const unsigned int S_pwr[68] PROGMEM ={4600,4350,700,1550,650,1550,650,1600,650,450,650,450,650,450,650,450,700,400,700,1550,650,1550,650,1600,650,450,650,450,650,450,700,450,650,450,650,450,650,1550,700,450,650,450,650,450,650,450,650,450,700,400,650,1600,650,450,650,1550,650,1600,650,1550,650,1550,700,1550,650,1550,650};
// source
const unsigned int S_scr[68] PROGMEM ={4600,4350,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,400,700,400,700,1550,700,400,700,450,650,450,650,450,700,400,700,400,700,400,700,450,650,1550,700,1500,700,1550,650,1550,700,1500,700,1550,700,1500,700};
// channel up
const unsigned int S_pup[68] PROGMEM ={4600,4350,700,1500,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,450,650,450,700,400,700,400,700,400,700,400,700,1550,700,400,700,400,700,1550,650,450,700,400,700,400,700,1550,650,450,650,1600,650,1550,650,450,700,1500,700,1500,700,1550,650};
// channel down
const unsigned int S_pdown[68] PROGMEM ={4650,4300,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,1550,700,400,700,450,650,400,700,1550,700,1500,700,1550,700,1500,700,400,700,1550,650,1550,700,1500,700};
// volume up
const unsigned int S_vup[68] PROGMEM ={4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,450,650,1550,700,1500,700,1550,700,1500,700,1550,650};
// volume down
const unsigned int S_vdown[68] PROGMEM ={4600,4350,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,450,650,1550,700,400,700,400,700,450,700,400,700,400,700,400,700,1550,700,400,700,1500,700,1500,700,1550,700,1500,700};
 // mute
 const unsigned int* const cmd[] PROGMEM = {S_pwr, S_scr, S_pup, S_pdown, S_vup, S_vdown};
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
int R = 0;
int G= 0;
int B= 0;
int PinPIR = 2; // choose the input pin (for PIR sensor)
int PinSEC = 23; // choose the input pin (for PIR sensor)
int PinLDR = 8; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status
int light=0;
char auth[] = "896907932ed641dbb539a7ac700afe41";

void setup()
{
  Serial.begin(9600);
  pinMode(PinPIR, INPUT); // declare sensor as input
  pinMode(PinSEC, OUTPUT); // declare sensor as input
  Blynk.begin(auth, "Microscale Embedded Ltd", "Microscale1234", WLAN_SEC_WPA2);
}
BLYNK_WRITE(5)
{
  if(param.asInt()>0);
     irsend.sendRaw((unsigned int*)pgm_read_word(&(cmd[0])),68,38);
}
BLYNK_WRITE(6)
{
  if(param.asInt()>0);
     irsend.sendRaw((unsigned int*)pgm_read_word(&(cmd[1])),68,38);
}
BLYNK_WRITE(7)
{
  if(param.asInt()>0);
     irsend.sendRaw((unsigned int*)pgm_read_word(&(cmd[5])),68,38);
}
BLYNK_WRITE(8)
{
  if(param.asInt()>0);
     irsend.sendRaw((unsigned int*)pgm_read_word(&(cmd[3])),68,38);
}
BLYNK_WRITE(9)
{
  if(param.asInt()>0);
     irsend.sendRaw((unsigned int*)pgm_read_word(&(cmd[2])),68,38);
}
BLYNK_WRITE(3)
{
  if(param.asInt()>0);
     irsend.sendRaw((unsigned int*)pgm_read_word(&(cmd[4])),68,38);
}
BLYNK_WRITE(4)
{
  R=param[0].asInt();
  G=param[1].asInt();
  B=param[2].asInt();
  analogWrite(6,R);
  analogWrite(5,G);
  analogWrite(9,B);
}


void loop()
{
val = digitalRead(PinPIR); // read input value
  if (val == HIGH)
  {
    if (pirState == LOW)
    {
      analogWrite(6,R);
      analogWrite(5,G);
      analogWrite(9,B);
      Blynk.virtualWrite(10, HIGH);
    }
  }
  else
  {
    if (pirState == HIGH)
    {
      analogWrite(6,0);
      analogWrite(5,0);
      analogWrite(9,0);
      Blynk.virtualWrite(10, LOW);
    }
  }
 light=analogRead(PinLDR);//read LDR
if (light<100)//check darkness level
{
  Blynk.virtualWrite(2, HIGH);//notify d app
  digitalWrite(PinSEC,HIGH);//Trigger security light
}
else
{
  Blynk.virtualWrite(2, LOW);//notify d app
  digitalWrite(PinSEC,LOW);//off security light
}
  Blynk.run();
}

