#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUTTON1 7 //lewo
#define BUTTON2 6 //prawo
#define BUTTON3 5 //enter
#define BUTTON4 4 //ilosc

#define RELAY1 11 //woda
#define RELAY2 10 //malina
#define RELAY3 9 //jablko
#define RELAY4 8 //pomarancza

#define MAX_DRINK 7 //4 drinki + plukanie + nalewanie + oproznianie
#define MAX_ILOSC 5 //wielokrotność 50 ml, w tym przypadku max 6*50ml
#define SHOT 50 

int mode = 0;
int ilosc = 1;
int x = 1;
bool isFilled = 0;

String skladnik1 = "Woda";
String skladnik2 = "Malina";
String skladnik3 = "Jablko";
String skladnik4 = "Pomarancza";

LiquidCrystal_I2C lcd(0x27, 20 ,4);

void setup() {
 pinMode(BUTTON1,INPUT_PULLUP); //button 1 (lewo)
 pinMode(BUTTON2,INPUT_PULLUP); //button 2 (prawo)
 pinMode(BUTTON3,INPUT_PULLUP); //button 3 (enter)
 pinMode(BUTTON4,INPUT_PULLUP); //button 4 (ilosc)

 pinMode(RELAY1,OUTPUT); //relay 1
 pinMode(RELAY2,OUTPUT); //relay 2
 pinMode(RELAY3,OUTPUT); //relay 3
 pinMode(RELAY4,OUTPUT); //relay 4

 digitalWrite(RELAY1,HIGH);
 digitalWrite(RELAY2,HIGH);
 digitalWrite(RELAY3,HIGH);
 digitalWrite(RELAY4,HIGH);

 Serial.begin(9600);

 lcd.init();
 lcd.clear();
 lcd.backlight();

 lcd.setCursor(7,1);
 lcd.print("Barman");
 delay(1500);
}

void loop() {
 if(mode == 0){
    lcd.setCursor(8,0);
    lcd.print("MENU");
    lcd.setCursor(0,1);
    lcd.print("<-");
    lcd.setCursor(5,1);
    lcd.print("Drink nr 1");
    lcd.setCursor(18,1);
    lcd.print("->");
    lcd.setCursor(0,2);
    lcd.print("Ilosc: ");
    lcd.print(ilosc*SHOT);
    lcd.print(" ml");
    lcd.setCursor(0,3);
    lcd.print("-");
    lcd.print(skladnik1);
    lcd.setCursor(6,3);
    lcd.print("-");
    lcd.print(skladnik2);
  }

 else if(mode == 1){
    lcd.setCursor(8,0);
    lcd.print("MENU");
    lcd.setCursor(0,1);
    lcd.print("<-");
    lcd.setCursor(5,1);
    lcd.print("Drink nr 2");
    lcd.setCursor(18,1);
    lcd.print("->");
    lcd.setCursor(0,2);
    lcd.print("Ilosc: ");
    lcd.print(ilosc*SHOT);
    lcd.print(" ml");
    lcd.setCursor(0,3);
    lcd.print("-");
    lcd.print(skladnik1);
    lcd.setCursor(6,3);
    lcd.print("-");
    lcd.print(skladnik3);
  }

 else if(mode == 2){
    lcd.setCursor(8,0);
    lcd.print("MENU");
    lcd.setCursor(0,1);
    lcd.print("<-");
    lcd.setCursor(5,1);
    lcd.print("Drink nr 3");
    lcd.setCursor(18,1);
    lcd.print("->");
    lcd.setCursor(0,2);
    lcd.print("Ilosc: ");
    lcd.print(ilosc*SHOT);
    lcd.print(" ml");
    lcd.setCursor(0,3);
    lcd.print("-");
    lcd.print(skladnik1);
    lcd.setCursor(6,3);
    lcd.print("-");
    lcd.print(skladnik4);
  }

 else if(mode == 3){
    lcd.setCursor(8,0);
    lcd.print("MENU");
    lcd.setCursor(0,1);
    lcd.print("<-");
    lcd.setCursor(5,1);
    lcd.print("Drink nr 4");
    lcd.setCursor(18,1);
    lcd.print("->");
    lcd.setCursor(0,2);
    lcd.print("Ilosc: ");
    lcd.print(ilosc*SHOT);
    lcd.print(" ml");
    lcd.setCursor(0,3);
    lcd.print("-");
    lcd.print(skladnik1);
  }

 else if(mode == 4){
    lcd.setCursor(8,0);
    lcd.print("MENU");
    lcd.setCursor(0,1);
    lcd.print("<-");
    lcd.setCursor(6,1);
    lcd.print("Plukanie");
    lcd.setCursor(18,1);
    lcd.print("->");
    lcd.setCursor(0,2);
    lcd.print("Plukanie woda");
    lcd.setCursor(0,3);
    lcd.print("wszystkich rurek");
  }

 else if(mode == 5){
    lcd.setCursor(8,0);
    lcd.print("MENU");
    lcd.setCursor(0,1);
    lcd.print("<-");
    lcd.setCursor(5,1);
    lcd.print("Napelnianie");
    lcd.setCursor(18,1);
    lcd.print("->");
    lcd.setCursor(0,2);
    lcd.print("Napelnianie rurek");
    lcd.setCursor(0,3);
    lcd.print("skladnikami");
  }

 else if(mode == 6){
    lcd.setCursor(8,0);
    lcd.print("MENU");
    lcd.setCursor(0,1);
    lcd.print("<-");
    lcd.setCursor(5,1);
    lcd.print("Oproznianie");
    lcd.setCursor(18,1);
    lcd.print("->");
    lcd.setCursor(0,2);
    lcd.print("Oproznianie rurek");
    lcd.setCursor(0,3);
    lcd.print("ze skladnikow");
  }

 if(digitalRead(BUTTON1) == LOW){ //przycisk lewo (<-)
    mode = (mode + 6) % MAX_DRINK;
    unsigned long time = millis();
    unsigned long time2 = millis();
    while(digitalRead(BUTTON1) == LOW && time2-time < 1000){
      time2 = millis();
      delay(10);
    }

    if (digitalRead(BUTTON1) == HIGH && x!=1){
        mode = (mode + 1) % MAX_DRINK;
        x=0;
      } else if(digitalRead(BUTTON1) == HIGH ) x = 0;
      
      x++;
      lcd.clear();
  }

 if(digitalRead(BUTTON2) == LOW){ //przycisk prawo (->)
    mode = (mode + 1) % MAX_DRINK;
    unsigned long time = millis();
    unsigned long time2 = millis();
    while(digitalRead(BUTTON2) == LOW && time2-time < 1000){
      time2 = millis();
      delay(10);
    }

    if (digitalRead(BUTTON2) == HIGH && x!=1){
      mode = (mode + 6) % MAX_DRINK;
      x=0;
    } else if(digitalRead(BUTTON2) == HIGH ) x = 0;
    
    x++;
    lcd.clear();
  }

 if(digitalRead(BUTTON4) == LOW){ //przycisk ilosc
    ilosc++;
    unsigned long time = millis();
    unsigned long time2 = millis();
    while(digitalRead(BUTTON4) == LOW && time2-time < 1000){
      time2 = millis();
      delay(10);
    }

    if (digitalRead(BUTTON4) == HIGH && x!=1){
      ilosc--;
      x=0;
    } else if(digitalRead(BUTTON4) == HIGH ) x = 0;
    
    x++;
    lcd.clear();
  }

 if(ilosc > MAX_ILOSC){
    ilosc = 1;
 }

 if(digitalRead(BUTTON3) == LOW){ //przycisk enter
    switch(mode){
      case 0:
      drink1();
      break;

      case 1:
      drink2();
      break;

      case 2:
      drink3();
      break;

      case 3:
      drink4();
      break;

      case 4:
      cleaning();
      break;

      case 5:
      setUpAll();
      break;
      
      case 6:
      oproznianie();
      break;
    };
  }
 delay(10); 
}

void drink1(){
 lcd.clear();
 lcd.setCursor(4,1);
 lcd.print("Nalewanie...");
 
 digitalWrite(RELAY1,LOW); //woda
 digitalWrite(RELAY2,LOW); //malina

 double startTime = millis();
 double currentTime = millis();
 delay(100);
 double length = ilosc*50/2.8*1000;
 while(currentTime-startTime<length*0.91){
    if(currentTime-startTime>length*0.15){
      digitalWrite(RELAY2,HIGH);
    }
    if(digitalRead(BUTTON4) == LOW){
      digitalWrite(RELAY1,HIGH);
      digitalWrite(RELAY2,HIGH);
      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Przerwano.");
      delay(1500);
      lcd.clear();
      return;
    }
    delay(1);
    currentTime = millis();
  }
 digitalWrite(RELAY1,HIGH);
 digitalWrite(RELAY2,HIGH);

 lcd.clear();
 lcd.setCursor(7,1);
 lcd.print("Drink");
 lcd.setCursor(6,2);
 lcd.print("gotowy.");
 delay(1500);
 lcd.clear();
}

void drink2(){
 lcd.clear();
 lcd.setCursor(4,1);
 lcd.print("Nalewanie...");
 
 digitalWrite(RELAY1,LOW); //woda
 digitalWrite(RELAY3,LOW); //jablko

 double startTime = millis();
 double currentTime = millis();
 delay(100);
  double length = ilosc*50/2.8*1000;
 while(currentTime-startTime<length*0.91){
    if(currentTime-startTime>length*0.15){
      digitalWrite(RELAY3,HIGH);
    }
    if(digitalRead(BUTTON4) == LOW){
      digitalWrite(RELAY1,HIGH);
      digitalWrite(RELAY3,HIGH);
      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Przerwano.");
      delay(1500);
      lcd.clear();
      return;
    }
    delay(1);
    currentTime = millis();
  }
 digitalWrite(RELAY1,HIGH);
 digitalWrite(RELAY3,HIGH);
 lcd.clear();
 lcd.setCursor(7,1);
 lcd.print("Drink");
 lcd.setCursor(6,2);
 lcd.print("gotowy.");
 delay(1500);
 lcd.clear();
}

void drink3(){
 lcd.clear();
 lcd.setCursor(4,1);
 lcd.print("Nalewanie...");

 digitalWrite(RELAY1,LOW); //woda
 digitalWrite(RELAY4,LOW); //pomarancza

 double startTime = millis();
 double currentTime = millis();
 delay(100);
 double length = ilosc*50/2.8*1000;
 while(currentTime-startTime<length*0.91){
    if(currentTime-startTime>length*0.18){
      digitalWrite(RELAY4,HIGH);//pomarancza
    }
    if(digitalRead(BUTTON4) == LOW){
      digitalWrite(RELAY1,HIGH);
      digitalWrite(RELAY4,HIGH);
      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Przerwano.");
      delay(1500);
      lcd.clear();
      return;
    }
    delay(1);
    currentTime = millis();
  }
 digitalWrite(RELAY1,HIGH);
 digitalWrite(RELAY4,HIGH);
 lcd.clear();
 lcd.setCursor(7,1);
 lcd.print("Drink");
 lcd.setCursor(6,2);
 lcd.print("gotowy.");
 delay(1500);
 lcd.clear();
}

void drink4(){
 lcd.clear();
 lcd.setCursor(4,1);
 lcd.print("Nalewanie...");

 digitalWrite(RELAY1,LOW);

 double startTime = millis();
 double currentTime = millis();
 delay(100);
 double length = ilosc*50/2.8*1000;
 while(currentTime-startTime<length*0.91){
    if(digitalRead(BUTTON4) == LOW){
      digitalWrite(RELAY1,HIGH);
      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Przerwano.");
      delay(1500);
      lcd.clear();
      return;
    }
    delay(1);
    currentTime = millis();
  }
 digitalWrite(RELAY1,HIGH);
 lcd.clear();
 lcd.setCursor(7,1);
 lcd.print("Drink");
 lcd.setCursor(6,2);
 lcd.print("gotowy.");
 delay(1500);
 lcd.clear();
}
 
void cleaning(){ //plukanie rurek woda
  lcd.clear();
  lcd.setCursor(5,1);
  lcd.print("Plukanie..");
  lcd.setCursor(0,2);
  lcd.print("Pompa 1");
  digitalWrite(RELAY1,LOW);
  unsigned long startTime = millis();
  unsigned long currentTime = millis();
  delay(100);
  while(currentTime-startTime<10000){
    if(digitalRead(BUTTON4) == LOW){
      digitalWrite(RELAY1,HIGH);
      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Przerwano.");
      delay(1500);
      lcd.clear();
      return;
    }
    delay(1);
    currentTime = millis();
  }
  //delay(3000);
  digitalWrite(RELAY1,HIGH);
  
  lcd.clear();
  lcd.setCursor(5,1);
  lcd.print("Plukanie..");
  lcd.setCursor(13,2);
  lcd.print("Pompa 2");
  digitalWrite(RELAY2,LOW);
  startTime = millis();
  currentTime = millis();
  delay(100);
  while(currentTime-startTime<10000){
    if(digitalRead(BUTTON4) == LOW){
      digitalWrite(RELAY2,HIGH);
      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Przerwano.");
      delay(1500);
      lcd.clear();
      return;
    }
    delay(1);
    currentTime = millis();
  }
  //delay(3000);
  digitalWrite(RELAY2,HIGH);
  
  lcd.clear();
  lcd.setCursor(5,1);
  lcd.print("Plukanie..");
  lcd.setCursor(0,3);
  lcd.print("Pompa 3");
  digitalWrite(RELAY3,LOW);
  startTime = millis();
  currentTime = millis();
  delay(100);
  while(currentTime-startTime<10000){
    if(digitalRead(BUTTON4) == LOW){
    digitalWrite(RELAY3,HIGH);
      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Przerwano.");
      delay(1500);
      lcd.clear();
      return;
    }
    delay(1);
    currentTime = millis();
  }
  //delay(3000);
  digitalWrite(RELAY3,HIGH);
  
  lcd.clear();
  lcd.setCursor(5,1);
  lcd.print("Plukanie..");
  lcd.setCursor(13,3);
  lcd.print("Pompa 4");
  digitalWrite(RELAY4,LOW);
  startTime = millis();
  currentTime = millis();
  delay(100);
  while(currentTime-startTime<10000){
    if(digitalRead(BUTTON4) == LOW){
      digitalWrite(RELAY4,HIGH);
      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Przerwano.");
      delay(1500);
      lcd.clear();
      return;
    }
    delay(1);
    currentTime = millis();
  }
  //delay(3000);
  digitalWrite(RELAY4,HIGH);
  
  lcd.clear();
  lcd.setCursor(6,1);
  lcd.print("Plukanie");
  lcd.setCursor(5,2);
  lcd.print("zakonczone.");
  delay(1500);
  lcd.clear();
  isFilled = 0;
}

void setUpAll(){ //napelnianie rurek skladnikami na drinki
  /*if(isFilled){
    lcd.clear();
    lcd.setCursor(4,1);
    lcd.print("Napelnione.");
    lcd.clear();
   break; //jakiś błąd tu jest
  }*/
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Napelnianie...");
  lcd.setCursor(0,2);
  lcd.print("Pompa 1");
  digitalWrite(RELAY1,LOW);
  delay(2300);
  digitalWrite(RELAY1,HIGH);
  
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Napelnianie...");
  lcd.setCursor(13,2);
  lcd.print("Pompa 2");
  digitalWrite(RELAY2,LOW);
  delay(1800);
  digitalWrite(RELAY2,HIGH);

  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Napelnianie...");
  lcd.setCursor(0,3);
  lcd.print("Pompa 3");
  digitalWrite(RELAY3,LOW);
  delay(2200);
  digitalWrite(RELAY3,HIGH);
  
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Napelnianie...");
  lcd.setCursor(13,3);
  lcd.print("Pompa 4");
  digitalWrite(RELAY4,LOW);
  delay(2000);
  digitalWrite(RELAY4,HIGH);
  
  lcd.clear();
  lcd.setCursor(4,1);
  lcd.print("Napelnianie");
  lcd.setCursor(5,2);
  lcd.print("zakonczone.");
  delay(1500);
  lcd.clear();
}

void oproznianie(){ //oproznianie rurek skladnikami na drinki
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Oproznianie...");
  lcd.setCursor(0,2);
  lcd.print("Pompa 1");
  digitalWrite(RELAY1,LOW);
  delay(4000);
  digitalWrite(RELAY1,HIGH);
  
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Oproznianie...");
  lcd.setCursor(13,2);
  lcd.print("Pompa 2");
  digitalWrite(RELAY2,LOW);
  delay(4000);
  digitalWrite(RELAY2,HIGH);
  
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Oproznianie...");
  lcd.setCursor(0,3);
  lcd.print("Pompa 3");
  digitalWrite(RELAY3,LOW);
  delay(4000);
  digitalWrite(RELAY3,HIGH);
  
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Oproznianie...");
  lcd.setCursor(13,3);
  lcd.print("Pompa 4");
  digitalWrite(RELAY4,LOW);
  delay(4000);
  digitalWrite(RELAY4,HIGH);
  
  lcd.clear();
  lcd.setCursor(4,1);
  lcd.print("Oproznianie");
  lcd.setCursor(5,2);
  lcd.print("zakonczone.");
  delay(1500);
  lcd.clear();
}
