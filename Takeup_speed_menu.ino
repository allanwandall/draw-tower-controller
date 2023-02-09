void setTUSpeed(){
  tuExit = true;
  speedCounter = 1;
  tuSpeedOld = tuSpeed;
  tuSpeed = 0;
  lcd.setCursor(0,1);
  lcd.print("          ");
  tuLCDswitch();
  while(tuExit){
    unsigned char resultSpeed = process();
    if(resultSpeed == DIR_CW){
      tuMenu(true);
    }
    else if(resultSpeed == DIR_CCW){
      tuMenu(false);
    }

    button.loop();
    
    if(button.isPressed())
      tuSelect();

  }
  if(tuSpeed > tuSpeedMax){
    tuSpeed = tuSpeedMax;
  }
  tuStepsPerSecond = (conversionFactorTu*tuSpeed)+0.5;
  tuSpeedSet = true;
  enterPosition = 0;
  menuLCDswitch();
}

void tuMenu(bool dir){
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
  tuLCDswitch();
}

void tuSelect(){
  if(speedCounter == -2){
    tuSpeed = tuSpeedOld;
    tuExit = false;
  }else if(speedCounter == -1){
    tuExit = false;
  }else{
    tuSpeed = (tuSpeed*10) + speedCounter;
    enterPosition++;
    speedCounter = -1;
    tuLCDswitch();
  }
}

void tuLCDswitch(){
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
    lcd.setCursor(10,1);
    lcd.print("mm/min");
  }
} 
