//This code was written by Bob Clagett for I Like To Make Stuff - 2016
//It accompanies the project at http://www.iliketomakestuff.com/make-quiz-game-buttons
//This is for a simple 4 player quiz game setup.
//Only one button will light at a time, until the reset button is pressed.
//The reset button turns off all LEDs and sets everything up for the next "round".

// http://www.arduino.cc/en/Tutorial/LiquidCrystal
// include the library code:
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial1


#include <BlynkSimpleStream.h>
// Go to the Project Settings (nut icon)
char auth[] = "8ad35991e21247b3b76fdb59c7a8f5ce";




// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


///Define Buttons
//Reset Button
int resetButtonPin = 25;
int resetLed = 31;
//speaker
int piezoPin = 35;

//Button1
int button1Pin = 27;
int led1Pin = 23;
int button1State = 0; 

//Button2
int button2Pin = 24;
int led2Pin = 29;
int button2State = 0; 

//Button3
int button3Pin = 9;
int led3Pin = 8;
int button3State = 0; 

//Button4
int button4Pin = 7;
int led4Pin = 6;
int button4State = 0;

char* buzzedplayer[]={"lathieeshe","cheryl"};

int resetButtonState = 0;
boolean pollingForPresses = 1;

int lastbutton1State = LOW;
int lastbutton2State = LOW;
int lastbutton3State = LOW;
int lastbutton4State = LOW;
int lastResetState = LOW;

WidgetLCD lcdapp(V1);



void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(resetLed, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(resetButtonPin, INPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);

Blynk.begin(Serial, auth);
   // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(4,0);
  lcd.print("READY");
  lcdapp.clear();
  lcdapp.print(4, 0,"Game");
  lcdapp.print(4, 1, "Start!");
  delay(100);
  lcd.clear();
}

void loop() {


  int reading1 = digitalRead(button1Pin);
  int reading2 = digitalRead(button2Pin);
  int reading3 = digitalRead(button3Pin);
  int reading4 = digitalRead(button4Pin);
  int readingReset = digitalRead(resetButtonPin);

    if(pollingForPresses==1){

      
      //Button 1
      if (reading1 != button1State && reading1 != lastbutton1State) {
        button1State = reading1;
        button1State = digitalRead(button1Pin);
         
              if (button1State == HIGH) {
                // turn LEDon:
               // Serial.print("\nButton 1 ON");
                lcd.print(buzzedplayer[0]);
                 lcdapp.clear();
  lcdapp.print(4, 0,"Lathieeshe");
  lcdapp.print(4, 1, "Pressed");
                digitalWrite(led1Pin, HIGH);
                // playtone();
                // lcdprint(buzzedplayer);
                pollingForPresses = 0;
              }
         button1State = 0;
      }
   
      //Button 2
      if (reading2 != button2State && reading2 != lastbutton2State) {
        button2State = reading2;
        button2State = digitalRead(button2Pin);
          
              if (button2State == HIGH) {
                // turn LED on:
             //  Serial.print("\nButton 2 ON");
                digitalWrite(led2Pin, HIGH);
                
                lcd.print("cheryl");
                 lcdapp.clear();
 // lcdapp.print(4, 0,"Cheryl");
  //lcdapp.print(4, 1, "Pressed");
                
                // playtone();
                pollingForPresses = 0;
              }
         button2State = 0;
      }

      //Button 3
      if (reading3 != button3State && reading3 != lastbutton3State) {
        button3State = reading3;
        button3State = digitalRead(button3Pin);
          
              if (button3State == HIGH) {
                // turn LED on:
               // Serial.print("\nButton 3 ON");
                digitalWrite(led3Pin, HIGH);
                pollingForPresses = 0;
              }
         button3State = 0;
      }

      //Button 4
      if (reading4 != button4State && reading4 != lastbutton4State) {
        button4State = reading4;
        button4State = digitalRead(button4Pin);
          
              if (button4State == HIGH) {
                // turn LED on:
                Serial.print("\nButton 4 ON");
                digitalWrite(led4Pin, HIGH);
                pollingForPresses = 0;
              }
         button4State = 0;
      }
      
    }
   //Check reset button
   if (pollingForPresses==0) {
     
      if (readingReset != resetButtonState && readingReset != lastResetState) {
              resetButtonState = digitalRead(resetButtonPin);
          
              if (resetButtonState == HIGH) {
                //Serial.print("\nReset button HIGH");
                digitalWrite(resetLed, HIGH);
                resetButtons();
              }
         
         resetButtonState = 0;
      }
    }
  lastResetState = readingReset;
  lastbutton1State = reading1;  
  lastbutton2State = reading2;
  lastbutton3State = reading3;  
  lastbutton4State = reading4;
   
    Blynk.run();
}


void resetButtons() {
  
  lastbutton1State = 0;
  lastbutton2State = 0;
  lastbutton3State = 0;
  lastbutton4State = 0;
  resetButtonState = 0;
  lastResetState = 0;
  
  button1State = 0;
  button2State = 0;
  button3State = 0;
  button4State = 0;
  
  Serial.print("\nAll the Buttons where reset!");
  lcd.clear();

  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
  digitalWrite(led4Pin, LOW);
  digitalWrite(resetLed, LOW);
  digitalWrite(resetButtonPin, LOW);
 
  pollingForPresses = 1;
}



void playtone(){
tone(piezoPin, 5000,500);}


