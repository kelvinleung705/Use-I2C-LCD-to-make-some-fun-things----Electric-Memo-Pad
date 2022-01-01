#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  //設定LCD位置0x27,設定LCD大小為16*2
// Joystick 1
const int VRx1 = 0; // Connect to Analog Pin 0
const int VRy1 = 1; // Connect to Analog Pin 1
int xa = 0;
int ya = 0;
int xb = 0;
int yb = 0;
int lista = 0;
int listb = 0;
int Clean = 1;  //1 will clear, 0 will not
int Chara = 1;
int Charb = 1;

char Big[27]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};
char Small[27]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
char Num[11]={'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' '};
char Pun[29]={'.', ',', '?', '/', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '[', ']', '{', '}', '|', ':', ';', '"', '<', '>', ' '};

void setup() {
  lcd.init(); //初始化LCD 
  lcd.backlight(); //開啟背光
  // Joystick 1:
  //pinMode(SW1, INPUT);
  //digitalWrite(SW1, HIGH);

// Joystick 2:
//pinMode(SW2, INPUT);
//digitalWrite(SW2, HIGH);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
}

void loop() {


  
  if (analogRead(VRx1) < 100) {
    if (lista == 0  && Charb == 3) {
      lista = 10;
      listb = 10;
    } else if (lista == 0  && Charb == 2) {
      lista = 26;
      listb = 26;
    } else if (lista == 0  && Charb == 1) {
      lista = 26;
      listb = 26;
    } else if (lista == 0  && Charb == 4) {
      lista = 28;
      listb = 28;
    } else {
      listb = lista-1;
      lista = listb; 
    }
    
  } else if (analogRead(VRx1) > 950) {
    if (lista == 10  && Charb == 3) {
      lista = 0;
      listb = 0;
    } else if (lista == 26  && Charb == 2) {
      lista = 0;
      listb = 0;
    } else if (lista == 26  && Charb == 1) {
      lista = 0;
      listb = 0;
    } else if (lista == 28  && Charb == 4) {
      lista = 0;
      listb = 0;
    } else {
      listb = lista+1;
      lista = listb; 
    }
  } else if (analogRead(VRy1) < 100) {
    if (Clean == 1) {
      lcd.setCursor(xa,ya);
      lcd.print(" ");
    } else {
      Clean = 1;
    }
    xb=xa-1;
    xa=xb;
    if (xb < 0 && yb == 0) {
      xa=15;
      xb=15;
      ya=1;
      yb=1;
    } else if (xb < 0 && yb == 1) {
      xa=15;
      xb=15;
      ya=0;
      yb=0;
    }
  } else if (analogRead(VRy1) > 950) {
    if (Clean == 1) {
      lcd.setCursor(xa,ya);
      lcd.print(" ");
    } else {
      Clean = 1;
    }
    xb=xa+1;
    xa=xb;
    if (xb > 15 && yb == 0) {
      xa=0;
      xb=0;
      ya=1;
      yb=1;
    } else if (xb > 15 && yb == 1) {
      xa=0;
      xb=0;
      ya=0;
      yb=0;
    }
    
  } else if (digitalRead(3) == HIGH) {
    Clean = 0; 
  } else if (digitalRead(2) == HIGH) {
    Charb = Chara+1;
    Chara = Charb;
    if (Charb == 5) {
      Chara = 1;
      Charb = 1;
    } 
  }
  
  /*Serial.println(xa);
  Serial.println(ya);*/
  Serial.println(analogRead(VRx1));
  Serial.println(analogRead(VRy1));
  Serial.println(lista);
  Serial.println(listb);
  Serial.println(Num[lista]);
  Serial.println(Num[listb]);
  Serial.println(Clean);
  Serial.println(Chara);
  Serial.println(Charb);
  lcd.setCursor(xa,ya); 

  if (Charb == 1) {
    if (lista > 26) {
    lista = 0;
    listb = 0;
    }
    lcd.print(Big[listb]);
  } else if (Charb == 2) {
    lcd.print(Small[listb]);
  } else if (Charb == 3) {
    if (lista > 10) {
      lista = 0;
      listb = 0;
    }
    lcd.print(Num[listb]); 
  } else if (Charb == 4) {    
      lcd.print(Pun[listb]); 
  }  
  delay(300); 
}
