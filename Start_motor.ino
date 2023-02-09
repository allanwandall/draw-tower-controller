void start(){
  // Funktion der skal få stepperen til at køre nedad med den angivne hastighed
  if(!speedSet || !tuSpeedSet){
    lcd.setCursor(0,1);
    lcd.print("Speed not set");
    return;
  }

  lcd.clear();
  delay(200);
  lcd.setCursor(0,0);
  lcd.print("Press=stop F:");
  lcd.print(stepperSpeed);
  lcd.setCursor(0,1);
  lcd.print("TU: ");
  lcd.setCursor(5,1);
  lcd.print(tuSpeed);
  lcd.setCursor(10,1);
  lcd.print("mm/min");
  startExit = true;
  tuStepper.setSpeed(tuStepsPerSecond);  
  stepper.setSpeed(-feedStepsPerSecond); 



  while(startExit){
      unsigned char result = process();
    if(result == DIR_CW){
      tuSpeed = tuSpeed - 20;
      tuStepsPerSecond = (conversionFactorTu*tuSpeed)+0.5;
      tuStepper.setSpeed(tuStepsPerSecond);
    }
    else if(result == DIR_CCW){
      tuSpeed = tuSpeed + 20;
      tuStepsPerSecond = (conversionFactorTu*tuSpeed)+0.5;
      tuStepper.setSpeed(tuStepsPerSecond);       
    } 

    stepper.runSpeed();
    tuStepper.runSpeed();
    
    if(millis() >= time_1 + INTERVAL_LCD){
      time_1 += INTERVAL_LCD;
      //if((int)tuSpeed < 1000 && saveExit){
       // lcd.setCursor(5,1);
       // lcd.print("     ");
       // saveExit = false;
     // }
      lcd.setCursor(5,1);
      lcd.print((int)tuSpeed);
    }
    
    button.loop(); // MUST call the loop() function first
  
    if(button.isPressed())
      startExit = false;
  }
  
  menuLCDswitch();
}
