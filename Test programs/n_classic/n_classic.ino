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

void setup() {
   classic.begin();
  
	Serial.begin(9600);
 
  if(radio.begin()){
    Serial.println("NRF24 OK");
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

  radio.write(&classic, sizeof(classic));

  classic.printDebug();

}
