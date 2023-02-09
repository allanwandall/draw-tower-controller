#include <LiquidCrystal_I2C.h>
#include <ezButton.h>
#include <AccelStepper.h>
#include <EEPROM.h>

#define R_START 0x0
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6
#define DIR_NONE 0x0
#define DIR_CW 0x10
#define DIR_CCW 0x20

#define dirPin 51
#define stepPin 50

#define tuDirPin 53
#define tuStepPin 52 

#define motorInterfaceType 1
#define stepsPerRevolution 6400

#define encoderButton 10

#define INTERVAL_LCD 100


const byte pin1 = 9;  // DT
const byte pin2 = 8;  // CLK 
int state = R_START;
int counter = 0;

int microStep = 32;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal_I2C lcd(0x27, 16, 2);
ezButton button(encoderButton);
 

 //number of menu options
int noM = 6;
 //number of speed options
int speedNoM = 9;
int aState;
int aLastState;
int menuCounter = 1;
unsigned long timer = 0;
bool speedExit = true;
int speedCounter = 1;
float stepperSpeed = 0;
bool speedSet = false;
uint8_t prevBut;
bool moveExit = true;
int moveSpeed = 1000;
bool movePress = true;
bool startExit = true;
bool tuExit = true;
float tuSpeed = 0;
bool tuSpeedSet = false;
float conversionFactorFeed = 53.33333; //steps per second for 1mm/min
float conversionFactorTu = 0.435366; //steps per second for 1mm/min
int feedStepsPerSecond = 0;
int tuStepsPerSecond = 0;
unsigned long time_1 = 0;
int enterPosition = 0;
float stepperSpeedOld;
float tuSpeedOld;
float stepperSpeedMax = 20.0;
float tuSpeedMax = 5000.0; //Mangler
bool saveExit = false;
int saveNoM = 50;
int saveCounter = 1;
bool saveRead = false;

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
AccelStepper tuStepper = AccelStepper(motorInterfaceType, tuStepPin, tuDirPin);
 
 
void setup() { 
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  pinMode(dirPin, OUTPUT);
  pinMode(tuDirPin, OUTPUT);

  stepper.setMaxSpeed(20000);
  stepper.setSpeed(0); 
  stepper.setAcceleration(20000);
  tuStepper.setMaxSpeed(5000*conversionFactorTu);
  tuStepper.setSpeed(0);   
  
  lcd.init();
  lcd.backlight();
  
  button.setDebounceTime(50);
   
  menuLCDswitch();  
} 

 
void loop() { 
  unsigned char result = process();
  if(result == DIR_CW){
    menu(true);
  }
  else if(result == DIR_CCW){
    menu(false);
  }

  button.loop();

  if(button.isPressed())
    menuSelect();


}
