//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <NintendoExtensionCtrl.h>


//create an RF24 object
RF24 radio(9, 10);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";


ClassicController classic;

struct controller_state {
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

void setup() {
   classic.begin();
  
	Serial.begin(9600);
 
  if(radio.begin()){
    
      Serial.println("NRF24 OK");
      
      //set the address
      radio.openWritingPipe(address);
      //Set module as transmitter
      radio.stopListening();

  }else{
     Serial.println("NRF24 ERROR");
  }
 
	if(classic.connect()) {
		Serial.println("CONTROLLER OK");
	}else{
    Serial.println("CONTROLLER ERROR");
	}
 
}


void loop() {

	classic.update(); 

  controller.dpadLeft = classic.dpadLeft();
  controller.dpadUp = classic.dpadUp();
  controller.dpadDown = classic.dpadDown();
  controller.dpadRight = classic.dpadRight();

  controller.buttonA = classic.buttonA();
  controller.buttonB = classic.buttonB();
  controller.buttonX = classic.buttonX();
  controller.buttonY = classic.buttonY();

  controller.buttonPlus = classic.buttonPlus();
  controller.buttonMinus = classic.buttonMinus();
  controller.buttonHome = classic.buttonHome();

  controller.buttonL = classic.buttonL();
  controller.buttonR = classic.buttonR();

  controller.buttonZL = classic.buttonZL();
  controller.buttonZR = classic.buttonZR();

  
  controller.leftJoyX = classic.leftJoyX();
  controller.leftJoyY = classic.leftJoyY();

  controller.rightJoyX = classic.rightJoyX();
  controller.rightJoyY = classic.rightJoyY();

  radio.write(&controller, sizeof(controller));

}
