 void menu(bool dir)  {
  if(dir){
    menuCounter--;
    if(menuCounter<1){
      menuCounter=noM;
    }
  }else{
    menuCounter++;
    if (menuCounter>noM){
      menuCounter=1;
    }
  }
  menuLCDswitch();
 }

void menuLCDswitch(){
    switch (menuCounter) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set Feed Speed");
      if(speedSet){
        lcd.setCursor(0,1);
        lcd.print((int)stepperSpeed);
        lcd.setCursor(10,1);
        lcd.print("mm/min");
      }
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set TU Speed");
      if(tuSpeedSet){
        lcd.setCursor(0,1);
        lcd.print((int)tuSpeed);
        lcd.setCursor(10,1);
        lcd.print("mm/min");
      }
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Start Feed");
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Move Stepper");
      break;
    case 5:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Save Profile");
      break;
    case 6:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Load Profile");
  }
} 


void menuSelect(){
  switch (menuCounter) {
    case 1:
      setStepperSpeed();
      break;
    case 2:
      setTUSpeed();
      break;
    case 3:
      start();
      break;
    case 4:
      moveStepper();
      break;
    case 5:
      saveRead = false;
      saveEEPROM();
      break;
    case 6:
      saveRead = true;
      saveEEPROM();
      break;
  }
}
