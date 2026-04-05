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
  pinMode(A0,INPUT);       

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop()
{
  int result = analogRead(A0);
  int enabled = digitalRead(7);

  Serial.print("Value=");
  Serial.println(result);

  lcd.setCursor(0,0);
  lcd.print("Value=");
  lcd.print(result);
  lcd.print("    ");

  lcd.setCursor(0,1);

  if(enabled == LOW){
    lcd.print("System OFF      ");

    digitalWrite(2,LOW); 
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);

    noTone(6);
  }
  else{
    if(result < 300){
      Serial.println("Low Temperature");

      lcd.print("Low Temp        ");

      digitalWrite(2,LOW); 

      digitalWrite(3,HIGH); 
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);

      tone(6,500);
      delay(200);
      noTone(6);
    }
    else if(result >= 300 && result <= 700){
      Serial.println("Medium Temperature");

      lcd.print("Medium Temp     ");

      digitalWrite(2,LOW);

      digitalWrite(3,LOW);
      digitalWrite(4,HIGH); 
      digitalWrite(5,LOW);

      noTone(6);
    }
    else{
      Serial.println("High Temperature");

      lcd.print("High Temp       ");

      digitalWrite(2,HIGH); 

      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,HIGH); 

      tone(6,500);
      delay(200);
      noTone(6);
    }
  }

  delay(1000);
}