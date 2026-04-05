#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  pinMode(2,OUTPUT);      
  pinMode(3,OUTPUT);     
  pinMode(4,OUTPUT);       
  pinMode(5,OUTPUT);       
  pinMode(6,OUTPUT);      
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP); 
  pinMode(A0,INPUT);      

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop()
{
  int en = digitalRead(7);
  int flood = digitalRead(8);
  int heat = analogRead(A0);

  Serial.print("Heat=");
  Serial.println(heat);

  if(en == LOW){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("System OFF");

    digitalWrite(2,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    noTone(3);

    delay(1000);
    return;
  }

  lcd.clear();

  if(flood == HIGH){
    lcd.setCursor(0,0);
    lcd.print("FLOOD ALERT");

    digitalWrite(2,HIGH);

    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);

    tone(3,500);
    delay(200);
    noTone(3);
    delay(200);
  }

  else if(heat > 500){
    lcd.setCursor(0,0);
    lcd.print("HIGH TEMP");

    digitalWrite(2,HIGH);

    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);

    tone(3,500);
    delay(200);
    noTone(3);
    delay(200);
  }

  else if(heat >= 200 && heat <= 500){
    lcd.setCursor(0,0);
    lcd.print("MEDIUM TEMP");

    digitalWrite(2,LOW);

    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);

    noTone(3);
  }

  else{
    lcd.setCursor(0,0);
    lcd.print("SAFE");

    digitalWrite(2,LOW);

    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);

    noTone(3);
  }

  delay(1000);
}