#include <Sim800L.h>
#include <SoftwareSerial.h>

#define RX  10
#define TX  11

Sim800L GSM(RX, TX);

const int dryContact = 2; // the number of the dryContact pin

int contactState = 1;         // variable for reading the dry contact status
int past = 0;

void setup(){
  GSM.begin(4800);
  Serial.begin(9600);
  pinMode(dryContact, INPUT);
  digitalWrite (dryContact, HIGH); // enable internal pullup
}

void loop(){
  while (contactState == 0 && past == 0) {
    GSM.sendSms("9260417281","Dry Contact detected");
    past = 1;
    contactState = digitalRead(dryContact);
    delay(1);
  }

  while (contactState == 0 && past == 1) {
    // Do Nothing unless dry contact is released
    contactState = digitalRead(dryContact);
    delay(1);
  }

  past = 0;
  
  delay(100);
  contactState = digitalRead(dryContact);
}
