#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <Servo.h>
Servo myServo;

int mot_min = 80;   //min servo angle
int mot_max = 170; //Max servo angle

//VOICE
String voice;
int
led1 = 26, //Connect LED 1 To Pin #2
led2 = 27, //Connect LED 2 To Pin #3
led3 = 28, //Connect LED 3 To Pin #4
led4 = 29, //Connect LED 4 To Pin #5
led5 = 30,
led6 = 31,
led7 = 32,
led8 = 33; //Connect LED 5 To Pin #6

void allon() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
  digitalWrite(led8, HIGH);
}
void alloff() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
}

#define buzzer 8
//#define trigPin 9
//#define echoPin 10

#define rxPin 1
#define txPin 0

SoftwareSerial mySerial(rxPin, txPin); // RX, TX
char myChar ;



long duration;
int distance, initialDistance, currentDistance, i;
int screenOffMsg = 0;
String password = "1234";
String tempPassword;
boolean activated = false; // State of the alarm
boolean isActivated;
boolean activateAlarm = false;                                //For activated countdown //RAHA
boolean alarmActivated = false;
boolean enteredPassword; // State of the entered password to stop the alarm
boolean passChangeMode = false;
boolean passChanged = false;


boolean buttonVal = false;
boolean prev_buttonVal = false;
boolean armButton = false;
boolean isArmed = false;            //false
const int triggeredLED = 12;   // 7
const int LED_Yellow = 13;  // 8
const int RedLED = 11;         // 4
const int GreenLED = 22;       // 5
const int inputPin = A0;
const int inputPin1 = A1;

const int BDLED1 = 34;
const int BDLED2 = 35;

const int MAX = 600;

const int lowrange = 2000;
const int highrange = 4000;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keypressed;
//define the cymbols on the buttons of the keypads
char keyMap[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {14, 15, 16, 17}; //Row pinouts of the keypad
byte colPins[COLS] = {18, 19, 20, 21}; //Column pinouts of the keypad

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(23, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)
char data = 0;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);

  myServo.attach(30);
  myServo.write(mot_min);

  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);

  pinMode(triggeredLED, OUTPUT);
  pinMode(LED_Yellow, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  //pinMode(armButton, INPUT);
  digitalWrite(triggeredLED, HIGH);
  delay(500);
  digitalWrite(triggeredLED, LOW);
  digitalWrite(13, HIGH);

  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);


}

void loop() {
 
  while (Serial.available()) {
    delay(10); //Delay added to make thing stable
    data = Serial.read(); //Conduct a serial read
    if (data == '#') {
      break; //Exit the loop when the # is detected after the word
    }
    voice += data; //Shorthand for voice = voice + c

        Serial.print(data);
    Serial.print("\n");
    if (data == 'E') {
      myServo.detach();
      digitalWrite(26, HIGH);
    }
    else if (data == 'F') {
      myServo.detach();
      digitalWrite(26, LOW);
    }

    if (data == 'G') {
      myServo.detach();
      digitalWrite(27, HIGH);
    }
    else if (data == 'H') {
      myServo.detach();
      digitalWrite(27, LOW);
    }

    if (data == 'I') {
      myServo.detach();
      digitalWrite(28, HIGH);
    }
    else if (data == 'J') {

      myServo.detach();
      digitalWrite(28, LOW);
    }


    if (data == 'K') {
      myServo.detach();
      digitalWrite(29, HIGH);
    }
    else if (data == 'L') {
      myServo.detach();
      digitalWrite(29, LOW);
    }

    if (data == 'S') {
      myServo.attach(30);
      myServo.write(mot_max);
      //myServo.detach();
      //digitalWrite(30, LOW);

    }

    else if (data == 'T') {
      myServo.attach(30);
      myServo.write(mot_min);
    }



    if (data == 'O') {
      myServo.detach();
      digitalWrite(31, HIGH);
    }
    else if (data == 'P') {
      myServo.detach();
      digitalWrite(31, LOW);
    }
    if (data == 'Q') {
      myServo.detach();
      digitalWrite(32, HIGH);
    }
    else if (data == 'R') {
      myServo.detach();
      digitalWrite(32, LOW);
    }

    if (data == 'M') {
      myServo.detach();
      digitalWrite(33, HIGH);
    }
    else if (data == 'N') {
      myServo.detach();
      digitalWrite(33, LOW);
    }
  }

  if (voice.length() > 0) {
    Serial.println(voice);
    //-----------------------------------------------------------------------//
    //----------Control Multiple Pins/ LEDs----------//
    if (voice == "*all on") {
      allon(); //Turn Off All Pins (Call Function)
    }
    else if (voice == "*all off") {
      alloff(); //Turn On  All Pins (Call Function)
    }

    //----------Turn On One-By-One----------//
    else if (voice == "*light on") {
      digitalWrite(led1, HIGH); //Light A
    }
    else if (voice == "*fan on") {
      digitalWrite(led2, HIGH); //fan A
    }
    else if (voice == "*right on") {
      digitalWrite(led3, HIGH); //b light on
    }
    else if (voice == "*send on") {
      digitalWrite(led4, HIGH);
    }
    else if (voice == "*bathroom on") {
      digitalWrite(led5, HIGH);
    }
    else if (voice == "*see on") {
      digitalWrite(led6, HIGH);
    }
    else if (voice == "*room c on") {
      digitalWrite(led7, HIGH);
    }
    else if (voice == "*ex light on") {
      digitalWrite(led8, HIGH);
    }

    //----------Turn Off One-By-One----------//
    else if (voice == "*light off") {
      digitalWrite(led1, LOW);
    }
    else if (voice == "*fan off") {
      digitalWrite(led2, LOW);
    }
    else if (voice == "*right off") {
      digitalWrite(led3, LOW);
    }
    else if (voice == "*send off") {
      digitalWrite(led4, LOW);
    }
    else if (voice == "*bathroom off") {
      digitalWrite(led5, LOW);
    }
    else if (voice == "*c off") {
      digitalWrite(led6, LOW); //control off
    }
    else if (voice == "*room c off") {
      digitalWrite(led7, LOW);
    }
    else if (voice == "*ex light off") {
      digitalWrite(led8, LOW);
    }
    //-----------------------------------------------------------------------//
    voice = "";
  }

  if (activateAlarm) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Security will be");
    lcd.setCursor(0, 1);
    lcd.print("activated in");

    int countdown = 5; // 9 seconds count down before activating the alarm
    while (countdown != 0) {
      lcd.setCursor(13, 1);
      lcd.print(countdown);
      countdown--;
      tone(buzzer, 700, 100);
      delay(1000);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Security Activated!");
    digitalWrite(GreenLED, HIGH);

    activateAlarm = false;

    alarmActivated = true;

  }

  if (alarmActivated) {


    int reading = analogRead(inputPin);
   // int reading1 = analogRead(inputPin1);


    Serial.println(reading);
    if (reading < MAX ) {        //if (reading < MAX || reading1 < MAX )
      tone(buzzer, 2000);

      digitalWrite(GreenLED, LOW);
      digitalWrite(RedLED, HIGH);

      digitalWrite(BDLED1, HIGH);
      digitalWrite(BDLED2, HIGH);

      lcd.clear();
      enterPassword();
    }
    else {
      noTone(buzzer);
    }
  }



  if (!alarmActivated) {
    if (screenOffMsg == 0 ) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("A - Activate");
      lcd.setCursor(0, 1);
      lcd.print("B - Change Pass");
      screenOffMsg = 1;
    }
    keypressed = myKeypad.getKey();
    if (keypressed == 'A') {      //If A is pressed, activate the alarm
      tone(buzzer, 1000, 200);
      activateAlarm = true;
    }
    else if (keypressed == 'B') {
      lcd.clear();
      int i = 1;
      tone(buzzer, 2000, 100);
      tempPassword = "";
      lcd.setCursor(0, 0);
      lcd.print("Current Password");
      lcd.setCursor(0, 1);
      lcd.print(">");
      passChangeMode = true;
      passChanged = true;
      while (passChanged) {
        keypressed = myKeypad.getKey();
        if (keypressed != NO_KEY) {
          if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
              keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
              keypressed == '8' || keypressed == '9' ) {
            tempPassword += keypressed;
            lcd.setCursor(i, 1);
            lcd.print("*");
            i++;
            tone(buzzer, 2000, 100);
          }
        }
        if (i > 5 || keypressed == '#') {
          tempPassword = "";
          i = 1;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Current Password");
          lcd.setCursor(0, 1);
          lcd.print(">");
        }
        if ( keypressed == '*') {
          i = 1;
          tone(buzzer, 2000, 100);
          if (password == tempPassword) {
            tempPassword = "";
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Set New Password");
            lcd.setCursor(0, 1);
            lcd.print(">");
            while (passChangeMode) {
              keypressed = myKeypad.getKey();
              if (keypressed != NO_KEY) {
                if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                    keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                    keypressed == '8' || keypressed == '9' ) {
                  tempPassword += keypressed;
                  lcd.setCursor(i, 1);
                  lcd.print("*");
                  i++;
                  tone(buzzer, 2000, 100);
                }
              }
              if (i > 5 || keypressed == '#') {
                tempPassword = "";
                i = 1;
                tone(buzzer, 2000, 100);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Set New Password");
                lcd.setCursor(0, 1);
                lcd.print(">");
              }
              if ( keypressed == '*') {
                i = 1;
                tone(buzzer, 2000, 100);
                password = tempPassword;
                passChangeMode = false;
                passChanged = false;
                screenOffMsg = 0;
              }
            }
          }
        }
      }
    }
  }
}

void enterPassword() {




  int k = 5;
  tempPassword = "";
  activated = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" *** ALARM *** ");
  lcd.setCursor(0, 1);
  lcd.print("Pass>");
  while (activated) {
    keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY) {
      if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
          keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
          keypressed == '8' || keypressed == '9' ) {
        tempPassword += keypressed;
        lcd.setCursor(k, 1);
        lcd.print("*");
        k++;
      }
    }
    if (k > 9 || keypressed == '#') {
      tempPassword = "";
      k = 5;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" *** ALARM *** ");
      lcd.setCursor(0, 1);
      lcd.print("Pass>");
    }
    if ( keypressed == '*') {
      if ( tempPassword == password ) {
        activated = false;                    //
        alarmActivated = false;

        digitalWrite(GreenLED, LOW);
        digitalWrite(RedLED, LOW );
        digitalWrite(BDLED1, LOW);
        digitalWrite(BDLED2, LOW);

        noTone(buzzer);
        screenOffMsg = 0;
      }
      else if (tempPassword != password) {
        lcd.setCursor(0, 1);
        lcd.print("Wrong! Try Again");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" *** ALARM *** ");
        lcd.setCursor(0, 1);
        lcd.print("Pass>");
      }
    }
  }
}
