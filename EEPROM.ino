void writeIntEEPROM(int address, int feed, int tu)
{ 
  EEPROM.write(address, feed >> 8);
  EEPROM.write(address + 1, feed & 0xFF);
  EEPROM.write(address + 2, tu >> 8);
  EEPROM.write(address + 3, tu & 0xFF);
}

void readEEPROM(int address)
{
  stepperSpeed = (EEPROM.read(address) << 8) + EEPROM.read(address + 1);
  tuSpeed = (EEPROM.read(address + 2) << 8) + EEPROM.read(address + 3);
  feedStepsPerSecond = (conversionFactorFeed*stepperSpeed)+0.5;
  tuStepsPerSecond = (conversionFactorTu*tuSpeed)+0.5;

  speedSet = true;
  tuSpeedSet = true;
}

void saveEEPROM()
{
  saveExit = true;
  if(!speedSet || !tuSpeedSet){
    lcd.setCursor(0,1);
    lcd.print("Speed not set");
    return;
  }
  saveLCDswitch();
  while(saveExit){
    unsigned char result = process();
    if(result == DIR_CW){
      saveMenu(true);
    }
    else if(result == DIR_CCW){
      saveMenu(false);
    }

    button.loop();
    
    if(button.isPressed())
      if(saveRead){
        readEEPROM(saveCounter*4);
        saveExit = false;
        lcd.setCursor(10,1);
        lcd.print("Loaded");
      }else{
        writeIntEEPROM(saveCounter*4,stepperSpeed, tuSpeed);
        saveExit = false;
        lcd.setCursor(10,1);
        lcd.print("Saved");
      }
    
  }
}

void saveMenu(bool dir){
  if(dir){
    saveCounter--;
    if(saveCounter<1){
      saveCounter=saveNoM;
    }
  }else{
    saveCounter++;
    if (saveCounter>saveNoM){
      saveCounter=1;
    }
  }
  saveLCDswitch();
}

void saveLCDswitch(){
  lcd.setCursor(0,1);
  lcd.print("     ");
  lcd.setCursor(0,1);
  lcd.print(saveCounter);
}
