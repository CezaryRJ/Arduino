//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(10, 9);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

//239 = up 
//223 = down
//191 = left
//127 = right 

void setup()
{
  while (!Serial);
    Serial.begin(9600);
  
  if(radio.begin()){
    Serial.println("INIT OK");
  }

  radio.openReadingPipe(0, address);
  
  radio.startListening();

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
}

byte inn = 0;
void loop()
{
 if (radio.available())
  {
    
    radio.read(&inn, sizeof(inn));
    Serial.println(inn);
  }

  if(inn == 239){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);

    Serial.println("FORWARD");
    
  }
  else if (inn == 223){
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);

    Serial.println("BACK");
    
  }else if(inn == 127){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);

    Serial.println("LEFT");
    
  }else if (inn == 191){
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);

    Serial.println("RIGHT");
    
  }else{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  
}
