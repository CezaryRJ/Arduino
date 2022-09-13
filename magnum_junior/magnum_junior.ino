//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Arduino.h>
#include <U8x8lib.h>


//create an RF24 object
RF24 radio(10, 9);  // CE, CSN

//screen
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);




//address through which two modules communicate.
const byte address[6] = "00001";

//calibration
//

int offset0 = 411;
int offset1 = 329;
int offset2 = 0;
int offset3 = 544;

int deadzone1 = 0;
int deadzone2 = 0;
int deadzone3 = 0;
int deadzone4 = 0;

int valuerange0 = 175; //limit values to range from -175 to 175 


struct controller_state {
  int a0 = 0;
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
}controller;

char buff[8];

void setup()
{
  
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);   



  Serial.begin(9600);

  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
   
  if(radio.begin()){
  
      u8x8.drawString(0,0,"INIT OK");
      digitalWrite(2,LOW);

      Serial.println("INIT OK");

      radio.openWritingPipe(address);
      radio.stopListening();
  }
  else{
      u8x8.drawString(0,0,"INIT FAILED");
  }

  Serial.println("TEST");

}

void loop()
{
  
  Serial.println("SENDING");
  
  controller.a0 = analogRead(A1) - offset0;

  if(controller.a0 < valuerange0 * -1){
    controller.a0 = valuerange0 * -1;
  }
  else if(controller.a0 > valuerange0){
    controller.a0 = valuerange0;
  }
  
  itoa(controller.a0 ,buff,10);
  padString(buff);
  u8x8.drawString(0,2,buff);


  controller.a1 = analogRead(A2) - offset1;
  itoa(controller.a1,buff,10);
  padString(buff);
  u8x8.drawString(0,3,buff);

  controller.a2 = analogRead(A3) - offset2;
  itoa(controller.a2,buff,10);
  padString(buff);
  u8x8.drawString(0,4,buff);

  controller.a3 = analogRead(A6) - offset3;
  itoa(controller.a3,buff,10);
  padString(buff);
  u8x8.drawString(0,5,buff);

  if(radio.write(&controller, sizeof(controller))){
      u8x8.drawString(0,6,"RECEIVER OK    ");
  }else{
       u8x8.drawString(0,6,"RECEIVER ERROR");
  }

}

void padString(char inn[]){
  for(int i = strlen(inn); i<6;i++){
    inn[i] = ' ';
  }
  inn[7] = '\0';

  
}




  
