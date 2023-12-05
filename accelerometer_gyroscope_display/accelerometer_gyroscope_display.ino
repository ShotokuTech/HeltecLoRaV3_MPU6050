#include<Wire.h>

#include "HT_SSD1306Wire.h"

SSD1306Wire  factory_display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED); // addr , freq , i2c group , resolution , rst

extern TwoWire Wire1;

int sdaPin = 41;
int sclPin = 42;

const int MPU=0x68; 
float AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void VextON(void)
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, LOW);
}

void VextOFF(void) //Vext default OFF
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, HIGH);
}

void  setup(){
	VextON();
	delay(100);
	factory_display.init();
	factory_display.clear();
  factory_display.setFont(ArialMT_Plain_10);
  factory_display.setTextAlignment(TEXT_ALIGN_LEFT);
	factory_display.display();

	pinMode(LED ,OUTPUT);
	digitalWrite(LED, LOW);

  Wire1.begin(sdaPin,sclPin,400000);
  Wire1.beginTransmission(MPU);
  Wire1.write(0x6B);  
  Wire1.write(0);    
  Wire1.endTransmission(true);
  Serial.begin(9600);
}
void  loop(){
  Wire1.beginTransmission(MPU);
  Wire1.write(0x3B);  
  Wire1.endTransmission(false);
  Wire1.requestFrom(MPU,12,true);  
  AcX=Wire1.read()<<8|Wire1.read();    
  AcY=Wire1.read()<<8|Wire1.read();  
  AcZ=Wire1.read()<<8|Wire1.read();  
  GyX=Wire1.read()<<8|Wire1.read();  
  GyY=Wire1.read()<<8|Wire1.read();  
  GyZ=Wire1.read()<<8|Wire1.read();

  factory_display.clear();
  factory_display.display();
  factory_display.setTextAlignment(TEXT_ALIGN_LEFT);  
  factory_display.drawString(0, 0, "AcX");
  factory_display.drawString(0, 10, "AcY");
  factory_display.drawString(0, 20, "AcZ");
  factory_display.drawString(30, 0, String(AcX,0));
  factory_display.drawString(30, 10, String(AcY,0));
  factory_display.drawString(30, 20, String(AcZ,0));
  factory_display.drawString(0, 30, "GyX");
  factory_display.drawString(0, 40, "GyY");
  factory_display.drawString(0, 50, "GyZ");
  factory_display.drawString(30, 30, String(GyX,0));
  factory_display.drawString(30, 40, String(GyY,0));
  factory_display.drawString(30, 50, String(GyZ,0));
  factory_display.display();

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = ");  Serial.println(AcZ); 
  
  Serial.print("Gyroscope: ");
  Serial.print("X  = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  delay(333);
}