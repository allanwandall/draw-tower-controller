void moveStepper(){
  moveExit = true;
  movePress = true;
  moveSpeed = 1000*microStep;
  stepper.setSpeed(20000);
  
  lcd.setCursor(0,1);
  lcd.print("CW = 10mm up");
  
  while(moveExit){
    unsigned char resultMove = process();
    if(resultMove == DIR_CW){
      moveMenu(true);
    }
    else if(resultMove == DIR_CCW){
      moveMenu(false);
    }

    button.loop();

    if(button.isPressed())
    switchMove();
  }

  menuLCDswitch();
  
}

void switchMove(){
  if(movePress){
    moveSpeed = 200*microStep;
    movePress = false;
    lcd.setCursor(0,1);
    lcd.print("CW = 2mm up ");
  }else{
    moveExit = false;
  }
}

void moveMenu(bool dir){
  if(dir){
    stepper.move(-moveSpeed);
    stepper.runToPosition();
  }else{
    stepper.move(moveSpeed);
    stepper.runToPosition();
  }
}
