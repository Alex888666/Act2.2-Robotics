#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
int analogPin = A0;
float temp = 0;
float volt = 0;
int adc = 0;
const int Lectura = 7;
float Lect [Lectura];
int i = 0;
float media = 0;
float total  = 0;

float sort_desc(const void *cmp1, const void *cmp2)
{
  float a = *((float *)cmp1);
  float b = *((float *)cmp2);
  if (a > b){
    return -1;
  }
  else if (a < b){
    return 1;
  }
  else {
    return 0;
  }
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1, 0);
  delay(1000); 
  Serial.begin(9600);
}

void loop() {
  delay(400);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.setCursor(6,1);
  adc = (analogRead(analogPin));
  volt = adc*(5.000/1023.000);
  temp = volt*10;
  total = total - Lect[i];
  Lect[i] = temp;
  total = total + Lect[i];
  i += 1;
  
  if (i >= Lectura) {
    i = 0;
  }

  media = total/Lectura;
  Serial.println(volt);
  qsort(Lect, Lectura, sizeof(Lect[0]), sort_desc);
  lcd.print(Lect[(Lectura-1)/2]);
  lcd.setCursor(12,1);
  lcd.print("C");
  lcd.setCursor(0,0);
  lcd.print("Volt: ");
  lcd.setCursor(6,0);
  lcd.print(volt);
  lcd.setCursor(11,0);
  lcd.print("V");
}
