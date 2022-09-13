#include <Arduino.h>
#include <U8x8lib.h>
#include<Wire.h>

const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;


U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);




void setup(void)
{
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
  
  u8x8.begin();
  u8x8.setPowerSave(0);

}

char buff[16];
void loop(void)
{
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  

  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  

  itoa(GyX,buff,10);
  u8x8.drawString(0,1,"GyX ");
  u8x8.drawString(5,1,buff);

  itoa(GyY,buff,10);
  u8x8.drawString(0,2,"GyY ");
  u8x8.drawString(5,2,buff);

  itoa(GyZ,buff,10);
  u8x8.drawString(0,3,"GyZ ");
  u8x8.drawString(5,3,buff);


  itoa(AcX,buff,10);
  u8x8.drawString(0,5,"AcX ");
  u8x8.drawString(5,5,buff);

  itoa(AcY,buff,10);
  u8x8.drawString(0,6,"AcY ");
  u8x8.drawString(5,6,buff);

  itoa(AcZ,buff,10);
  u8x8.drawString(0,7,"AcZ ");
  u8x8.drawString(5,7,buff);

}
