#include <SoftwareSerial.h> 
SoftwareSerial blueTooth(2,3); 
int piezoPin= 8;
int ledPin= 9;

void setup() 
{
  Serial.begin(9600);
  blueTooth.begin(9600);
  pinMode(piezoPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

int stopMode=0;
int   freq[ ] = {440/2, 494/2, 262, 294, 330, 349, 392};

void loop()
{
  if(stopMode == 1) return;
  if (!blueTooth.available()){
    return;
  }
  
  int cmd= blueTooth.read();
  Serial.print(cmd);  Serial.print(' ');
  if(cmd == 0)  return;
  if(cmd == 99){
    noTone(piezoPin);
    digitalWrite(ledPin, LOW);
    return;
  }

  // 10-도, 11-레, 12-미, ...
  cmd -= 10;
  if(cmd < 0 || cmd >= 21){
    stopMode=1;
    return;
  }
  
  int frequency= freq[cmd%8];
  if(cmd/7 == 0) frequency /= 2;
  if(cmd/7 == 2) frequency *= 2;
  tone(piezoPin, frequency);
  digitalWrite(ledPin, HIGH); 
}
