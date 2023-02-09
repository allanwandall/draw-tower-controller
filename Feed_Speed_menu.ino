void setStepperSpeed(){
  speedExit = true;
  speedCounter = 1;
  stepperSpeedOld = stepperSpeed;
  stepperSpeed = 0;
  lcd.setCursor(0,1);
  lcd.print("          ");
  speedLCDswitch();
  while(speedExit){
    unsigned char resultSpeed = process();
    if(resultSpeed == DIR_CW){
      speedMenu(true);
    }
    else if(resultSpeed == DIR_CCW){
      speedMenu(false);
    }

    button.loop();
    
    if(button.isPressed())
      speedSelect();

  }

  if(stepperSpeed > stepperSpeedMax){
    stepperSpeed = stepperSpeedMax;
  }
  feedStepsPerSecond = (conversionFactorFeed*stepperSpeed)+0.5;
  speedSet = true;
  enterPosition = 0;
  menuLCDswitch();
}

void speedMenu(bool dir){
  if(dir){
    speedCounter--;
    if(speedCounter<-2){
      speedCounter=speedNoM;
    }
  }else{
    speedCounter++;
    if (speedCounter>speedNoM){
      speedCounter=-2;
    }
  }
  speedLCDswitch();
}

void speedSelect(){
  if(speedCounter == -2){
    stepperSpeed = stepperSpeedOld;
    speedExit = false;
  }else if(speedCounter == -1){
    speedExit = false;
  }else{
    stepperSpeed = (stepperSpeed*10) + speedCounter;
    enterPosition++;
    speedCounter = -1;
    speedLCDswitch();
  }
}

void speedLCDswitch(){
  if(speedCounter == -2){
    lcd.setCursor(enterPosition,1);
    lcd.print(" ");
    lcd.setCursor(10,1);
    lcd.print("Return");
  }else if(speedCounter == -1){
    lcd.setCursor(enterPosition,1);
    lcd.print(" ");
    lcd.setCursor(10,1);
    lcd.print("Enter ");
  }else{
    lcd.setCursor(enterPosition,1);
    lcd.print(speedCounter);
    lcd.print("   ");
    lcd.setCursor(10,1);
    lcd.print("mm/min");
  }
} 
