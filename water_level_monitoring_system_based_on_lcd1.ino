#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  pinMode(2,OUTPUT);   
  pinMode(3,INPUT);    
  pinMode(4,OUTPUT);  
  pinMode(6,OUTPUT);  
  pinMode(7,OUTPUT);   
  
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
}

void loop()
{
  if(Serial.available()>0){
    String data=Serial.readString();
    data.trim();
    
    Serial.print("data=");
    Serial.println(data);
    
    if(data=="status"){
      Serial.println("Bluetooth Connected");
    }
    else if(data=="motor on"){
      digitalWrite(2,HIGH);
    }
    else if(data=="motor off"){
      digitalWrite(2,LOW);
    }
    else if(data=="led on"){
      digitalWrite(7,HIGH);
    }
    else if(data=="led off"){
      digitalWrite(7,LOW);
    }
    else if(data=="buzzer on"){
      tone(6,500);
    }
    else if(data=="buzzer off"){
      noTone(6);
    }
  }

  digitalWrite(4,LOW);
  delayMicroseconds(2);
  digitalWrite(4,HIGH);
  delayMicroseconds(10);
  digitalWrite(4,LOW);
  
  long timetaken = pulseIn(3,HIGH);
  int distance = timetaken * 0.034 / 2;
  
  int waterlevel = 200 - distance;   
  
  if(waterlevel < 0){
    waterlevel = 0;
  }
  
  if(waterlevel > 200){
    waterlevel = 200;
  }
  
  int levelpercent = map(waterlevel,0,200,0,100);
  
  Serial.print("Water Level=");
  Serial.println(waterlevel);
  
  Serial.print("Percent=");
  Serial.println(levelpercent);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Level=");
  lcd.print(waterlevel);
  lcd.print("cm");
  
  lcd.setCursor(0,1);
  lcd.print("Percent=");
  lcd.print(levelpercent);
  lcd.print("%");


  if(levelpercent <= 30){
    digitalWrite(2,HIGH);   
    digitalWrite(7,HIGH);  
    
    tone(6,500);
    delay(200);
    noTone(6);
    delay(200);
    lcd.setCursor(11,1);
    lcd.print("LOW");
    Serial.println("LOW LEVEL");
  }
  else if(levelpercent > 30 && levelpercent <= 70){
    digitalWrite(2,HIGH);   
    digitalWrite(7,HIGH);   
    noTone(6);
    lcd.setCursor(11,1);
    lcd.print("MID");
    Serial.println("MEDIUM LEVEL");
  }
  else{
    digitalWrite(2,LOW);    
    digitalWrite(7,LOW);    
    noTone(6);
    lcd.setCursor(11,1);
    lcd.print("HIGH"); 
    Serial.println("HIGH LEVEL");
  }
  Serial.println();
  delay(1000);
}