// C++ code
//
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop()
{
 
  digitalWrite(2,HIGH);
  double A=analogRead(A0);
  Serial.print("A=");
  Serial.println(A);
  lcd.setCursor(2,0);
  lcd.print(A);
  
    
  double B=map(A,6,679,100,0);
  Serial.print("Particle Concentration=");
  Serial.println(B);
  lcd.setCursor(9,0);
  lcd.print("% of Conc=");
  lcd.setCursor(12,0);
  lcd.print(B);
  
  if(B<=40){
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    noTone(6);
    Serial.println("Normal Particle Concentration");
    lcd.setCursor(0,1);
    lcd.print("Normal Conc");
  }
  else if(B<40 && B<=70){
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    tone(6,500);
    delay(300);
    noTone(6);
    delay(300);
    Serial.println("Medium Particle Concentration");
    lcd.setCursor(0,1);
    lcd.print("Medium Conc");
  }
  else{
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    tone(6,500);
    delay(100);
    noTone(6);
    delay(100);
    Serial.println("High Particle Concentration");
    lcd.setCursor(0,1);
    lcd.print("High Conc");
  }
  Serial.println();
}
