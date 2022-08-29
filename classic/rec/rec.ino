//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <NintendoExtensionCtrl.h>

//create an RF24 object
RF24 radio(9, 10);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";


struct Cstate {
  boolean dpadLeft;
  boolean dpadUp;
  boolean dpadDown;
  boolean dpadRight;

  boolean buttonA;
  boolean buttonB;
  boolean buttonX;
  boolean buttonY;

  boolean buttonPlus;
  boolean buttonMinus;
  boolean buttonHome;

  boolean buttonL;
  boolean buttonR;

  boolean buttonZL;
  boolean buttonZR;

  int leftJoyX;
  int leftJoyY;

  int rightJoyX;
  int rightJoyY;
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
    Serial.println(controller.leftJoyY);
    Serial.println(controller.leftJoyX);
  }
}
