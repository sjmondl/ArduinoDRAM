//void setup() 
//{
//  pinMode(52, INPUT);
//  pinMode(53, INPUT);  
//  pinMode(50, INPUT);  
//  pinMode(51, INPUT);
//  Serial.begin(9600);
//}
//  
//int readbutton()
//{
//  int buttonState[4];  
//  int last_button[4];
//  for (int i=50; i<=53; i++)//poles each button
//  {
//    buttonState[i-53] = digitalRead(i);//sets button state to high if pushed, low if not
//    if (buttonState[i-53] != last_button[i-53]) //if the button is the same value as last execution of code, exits
//    { 
//      delay(50);//debounces
//      if (buttonState[i-53] == HIGH)//only proceeds if button pressed
//      {
//        Serial.println(i);
//        return(i);
//      }
//    }
//    last_button[i-53] = buttonState[i-53];//stores current value for comparison on next loop execution
//  } 
//}  
//
//
//void loop()
//{
//  int pressed_button;
//  pressed_button = readbutton();
//}  


//for some reason running as a function in the above code screwed 
//things up so sometimes it didn't read and sometimes it reads multiple presses




  int buttonState[4];  
  int last_button[4];
void buttonSelection()
{
  pinMode(52, INPUT);
  pinMode(53, INPUT);  
  pinMode(50, INPUT);  
  pinMode(51, INPUT);
  Serial.begin(9600);

  for (int i=50; i<=53; i++)//polls each button
  {
    buttonState[i-53] = digitalRead(i);//sets button state to high if pushed, low if not
    if (buttonState[i-53] != last_button[i-53]) //if the button is the same value as last execution of code, exits
    { 
      delay(30);//debounces
      if (buttonState[i-53] == HIGH)//only proceeds if button pressed
      {
        Serial.println(i);//put the output variable for the state machine here
      }
    }
    last_button[i-53] = buttonState[i-53];//stores current value for comparison on next loop execution
  } 
}  

