#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//#define R1 100000
//#define R2 10000
#define analogInput A0

float R1 = 100000.0; // resistance of R1 (100K) -see text!
float R2 = 10000.0; // resistance of R2 (10K) - see text!

int value;
float vin = 0, vout = 0;

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("DC Voltimetro!");
  Serial.println("Init OK");
}

void loop() {
  // put your main code here, to run repeatedly:
  obtenerVolaje();
}

void obtenerVolaje()
{
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0; // see text
  vin = vout / (R2/(R1+R2)); 
  Serial.println("Vout: " + String(vout));
  Serial.println("Vin: " + String(vin));
  if (vin<0.09 || isnan(vin)) {
    vin=0.0;//statement to quash undesired reading !
  }
  lcd.setCursor(0,1);
  lcd.print("V: ");
  lcd.print(String(vin));
  lcd.print(" V");
}
