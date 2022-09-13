//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(10, 9);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
   Serial.begin(9600);
   
  if(radio.begin()){
    Serial.println("INIT OK");
  }
  
 
}


void loop()
{
      Serial.println("SENDING");
   //Send message to receiver
  const char text[] = "Hello World";
 // radio.write(&text, sizeof(text));
  
  delay(1000);


}
