//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 10);  // CE, CSN

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

}
