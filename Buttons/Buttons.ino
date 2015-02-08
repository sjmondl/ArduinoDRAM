
void setup() {
  Serial.begin(9600);// initialize serial communication at 9600 bits per second:
}

int lastbut = 0;//last button pressed

int getButton() {
  
  int currentBut;
  int sum=0;
  float voltage;
  int sensorValue, i;

  for (i=0; i<5; i++)
  {
    sum += analogRead(A0);
  }
  sensorValue = sum/5;//averaging to lessen effects of noise
  voltage = sensorValue * (5.0 / 1023.0);// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  //Serial.println(voltage);//for testing
  if (voltage>3) currentBut=0;
  else if (voltage>-.1 && voltage<.2) currentBut=1;
  else if (voltage>.3 && voltage<.6) currentBut=2;
  else if (voltage>.8 && voltage<1.2) currentBut=3;
  else if (voltage>1.3 && voltage<1.7) currentBut=4;
  else if (voltage>1.8 && voltage<2.2) currentBut=5;
  else if (voltage>2.3 && voltage<2.7) currentBut=6; 
  else currentBut=0;
  
  return currentBut;

}

void loop ()
{
  int currentBut;
  int button2, pressed_button;  
  int a=0;
  while(a==0)
  { 
    currentBut = getButton();
    
    if (currentBut != lastbut)
    {
        delay(50);        // debounce
  //      button2 = getButton();                  //alternative code, registers all presses, but 
  //      if(button2!=0) Serial.println(button2); //will occasionally register wrong press.  
        button2 = getButton();                                  //This code has no errors thrown about which button
        if (currentBut == button2)                              // is pressed, but will occasionally not register a
        {                                                       //button press at all
           lastbut = currentBut;                                //    
           pressed_button = currentBut;                         // 
           if(pressed_button!=0) Serial.println(pressed_button);//replace this with the variable you use to indicate a pushed button
           a=1;
        }               //
        else
        {
          a=0;
        }
    }
  }
}


////old obsolete code:
//  if (currentBut!=lastbut)
//    {
//      delay(5);
//      lastbut = currentBut;
//      if(currentBut!=0) Serial.println(lastbut);
//    }
  //Serial.println(count);
   // Serial.println(but);
  //Serial.println(voltage);
