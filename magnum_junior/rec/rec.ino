//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//create an RF24 object
RF24 radio(9, 10);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

struct controller_state {
  int a0;
  int a1;
  int a2;
  int a3;
}controller;

void setup()
{
  while (!Serial);
    Serial.begin(9600);

  if(radio.begin()){
    Serial.println("INIT OK");
  }
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  
  //Read the data if available in buffer
  if (radio.available())
  {

    radio.read(&controller, sizeof(controller));
    Serial.println(controller.a0);
    Serial.println(controller.a1);
    Serial.println(controller.a2);
    Serial.println(controller.a3);
  }
}
