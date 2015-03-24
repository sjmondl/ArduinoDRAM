#include <LiquidCrystal.h>

LiquidCrystal lcd(30, 32, 34, 35, 33, 31); //set up LCD pins

void setup() 
{
  pinMode(52, INPUT);
  pinMode(53, INPUT);  
  pinMode(50, INPUT);  
  pinMode(51, INPUT);
  //Serial.begin(9600);
lcd.begin(16, 2);
}
  int buttonState[4];  
  int last_button[4];
  int in=0;
  int state =1;
  
void loop()
{
  //This part of the code reads in the buttons, setting a button push to be a value of 1, 2, 3, or 4 depending on the button pushed; this becomes the input to the state machine
  //To keep the button from being read multiple times the code will not proceed if the button state is the same as it was on the last execution of the code
  //The input to the state machine is reset at the end of the code
  for (int button_io_pin=50; button_io_pin<=53; button_io_pin++)//poles each button
  {
    buttonState[53-button_io_pin] = digitalRead(button_io_pin);//sets button state to high if pushed, low if not
    if (buttonState[53-button_io_pin] != last_button[53-button_io_pin]) //if the button is the same value as last execution of code, exits
    { 
      delay(30);//debounces
      if (buttonState[53-button_io_pin] == HIGH)//only proceeds if button pressed
      {
         in = button_io_pin-49;//input to state machine
      }
    }
    last_button[53-button_io_pin] = buttonState[53-button_io_pin];//stores current value for comparison on next loop execution
  } 
//Serial.println(in);






//Begin state machine:

//for inputs: up   = 1
//            down = 2
//            sel  = 3
//            back = 4

//for each state, the first two lines are what is displayed on the LCD screen
//the thrird line is obsolete code it turned out doesn't seem to be needed

//Any comment ALL IN CAPS indicates that a program effecting the LEDs should be run when that state is reached

if (state == 1) 
{ 
  //print "Select Mode"_f
  //      "Settings"
  //lcd.clear();
  lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.println("Select Mode<    ");
  lcd.setCursor(0,1);
  lcd.print("Settings(v)     ");
    
  if (in == 1){//up
    state = 1;}
  else if (in == 2){//down
    state = 2;}
  else if (in == 3){//sel
    state = 4;}
  else if (in == 4){//back
    state = 1;}
  else if (in == 0){
    state = 1;}

} 
else if (state == 2)
{
  //print "Select Mode"
  //      "Settings (down)"_f
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Select Mode    ");
  lcd.setCursor(0,1);
  lcd.print("Settings(v)<   ");
    
  if (in == 1){//up
    state = 1;}
  else if (in == 2){//down
    state = 3;}
  else if (in == 3){//sel
    state = 12;}//CHANGE THIS WHEN THE SETTINGS SELECT STATES ARE ADDED
  else if (in == 4){//back
    state = 2;}
  else if (in == 0){
    state = 2;}
}
else if (state == 3)
{
  //print "Settings (up)"
  //      "Reset"_f
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Settings(^)        ");
  lcd.setCursor(0,1);
  lcd.print("Reset<             ");
  
  if (in == 1){//up
    state = 2;}
  else if (in == 2){//down
    state = 3;}
  else if (in == 3)//sel
  {
    state = 3;
    //RUN AUTOMATIC REFRESH, RUN DEFAULT SETTINGS, RUN RANDOM R/W
  }
  else if (in == 4){//back
    state = 3;}
  else if (in == 0){
    state = 3;}
}
else if (state == 4)
{
  //print "Refresh Mode_f"
  //      "Read/Write"
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Refresh Mode<         ");
  lcd.setCursor(0,1);
  lcd.print("Read/Write            ");
  
  if (in == 1){//up
    state = 4;}
  else if (in == 2){//down
    state = 5;}
  else if (in == 3){//sel
    state = 9;}
  else if (in == 4){//back
    state = 1;}
  else if (in == 0){
    state = 4;}
}
else if (state == 5)
{
  //print "Refresh Mode"
  //      "Read/Write"_f
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Refresh Mode          ");
  lcd.setCursor(0,1);
  lcd.print("Read/Write<           ");
  
  if (in == 1){//up
    state = 4;}
  else if (in == 2){//down
    state = 5;}
  else if (in == 3){//sel
    state = 6;}
  else if (in == 4){//back
    state = 1;}
  else if (in == 0){
    state = 5;}
}
else if (state == 6)
{
  //print "Random R/W"_f
  //      "Single Read (down)"
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Random R/W<           ");
  lcd.setCursor(0,1);
  lcd.print("Single Read(v)        ");
  
  if (in == 1){//up
    state = 6;}
  else if (in == 2){//down
    state = 7;}
  else if (in == 3){//sel
    state = 6;}
  //RUN RANDOM READ WRITE PROGRAM TO SET BOARD TO RANDOM READ WRITE MODE
  else if (in == 4){//back
    state = 4;}
  else if (in == 0){
    state = 6;}
}
else if (state == 7)
{
  //print "Random R/W"
  //      "Single Read (down)"_f
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Random R/W          ");
  lcd.setCursor(0,1);
  lcd.print("Single Read(v)<     ");
  
  if (in == 1){//up
    state = 6;}
  else if (in == 2){//down
    state = 8;}
  else if (in == 3){//sel
    state = 7;}
  //RUN A SINGLE READ PROGRAM AND THEN SET BOARD TO RANDOM READ WRITE MODE AFTER READ FINISHED
  else if (in == 4){//back
    state = 4;}
  else if (in == 0){
    state = 7;}
}
else if (state == 8)
{
  //print "Single Read (UP)"
  //      "Single Write"_f
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Single Read(^)        ");
  lcd.setCursor(0,1);
  lcd.print("Single Write<         ");
    
  if (in == 1){//up
    state = 7;}
  else if (in == 2){//down
    state = 8;}
  else if (in == 3){//sel
    state = 8;}
    //RUN A SINGLE WRITE PROGRAM AND THEN SET BOARD TO RANDOM READ WRITE MODE AFTER FINISHED
  else if (in == 4){//back
    state = 4;}
  else if (in == 0){
    state = 8;}
}
else if (state == 9)
{
  //print "Automatic Refresh"_f
  //      "Manual Refresh"
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Auto Refresh<      ");
  lcd.setCursor(0,1);
  lcd.print("Manual Refresh          ");
  
  if (in == 1){//up
    state = 9;}
  else if (in == 2){//down
    state = 10;}
  else if (in == 3){//sel
    state = 9;}
  //SET THE LEDS TO RUN IN AUTOMATIC REFRESH MODE
  else if (in == 4){//back
    state = 4;}
  else if (in == 0){
    state = 9;}
}
else if (state == 10)
{
  //print "Automatic Refresh"
  //      "Manual Refresh"_f
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Auto Refresh      ");
  lcd.setCursor(0,1);
  lcd.print("Manual Refresh<        ");
  
  if (in == 1){//up
    state = 9;}
  else if (in == 2){//down
    state = 10;}
  else if (in == 3){//sel
    state = 11;}
  //DISABLE THE AUTOMATIC REFRESH ROUTINE, ENABLE MANUAL REFRESH MODE
  else if (in == 4){//back
    state = 4;}
  else if (in == 0){
    state = 10;}
}
else if (state == 11)
{
  //print "Press Select to
  //       Trigger Refresh"
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Press Select to      ");
  lcd.setCursor(0,1);
  lcd.print("Trigger Refresh      ");

  if (in == 1){//up
    state = 11;}
  else if (in == 2){//down
    state = 11;}
  else if (in == 3){//sel
    state = 11;}
  //RUN A MANUAL REFRESH ON THE LEDS IN THE BOARD
  else if (in == 4){//back
    state = 9;}
  else if (in == 0){
    state = 11;}
}
else if (state == 12)
{
  //print "Set Speed"_f
  //      "Insert Bad Cells (down)"
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Set Speed<          ");
  lcd.setCursor(0,1);
  lcd.print("BadCellsOn(v)       ");
  
  if (in == 1){//up
    state = 12;}
  else if (in == 2){//down
    state = 15;}
  else if (in == 3){//sel
    state = 13;}
  else if (in == 4){//back
    state = 2;}
  else if (in == 0){
    state = 12;}
}
else if (state == 13)
{
  //print "Fast"_f
  //      "Slow"
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Fast<           ");
  lcd.setCursor(0,1);
  lcd.print("Slow            ");
    
  if (in == 1){//up
    state = 13;}
  else if (in == 2){//down
    state = 14;}
  else if (in == 3){//sel
    state = 13;}
    //RUN A PROGRAM THAT SETS THE SPEED OF EVERYTHING TO FAST
  else if (in == 4){//back
    state = 12;}
  else if (in == 0){
    state = 13;}
}
else if (state == 14)
{
  //print "Fast"
  //      "Slow"_F
  //lcd.clear();
 // lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Fast          ");
  lcd.setCursor(0,1);
  lcd.print("Slow<         ");
   
  if (in == 1){//up
    state = 13;}
  else if (in == 2){//down
    state = 14;}
  else if (in == 3){//sel
    state = 14;}
    //RUN A PROGRAM THAT SETS THE SPEED OF EVERYTHING TO SLOW
  else if (in == 4){//back
    state = 12;}
  else if (in == 0){
    state = 14;}
}
else if (state == 15)
{
  //print "Set Speed"
  //      "Insert Bad Cells (down)"_f
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Set Speed             ");
  lcd.setCursor(0,1);
  lcd.print("BadCellsOn(v)<        ");
  
  if (in == 1){//up
    state = 12;}
  else if (in == 2){//down
    state = 16;}
  else if (in == 3){//sel
    state = 15;}
    //RUNS A PROGRAM THAT INSERTS PREALOCATED BAD CELLS INTO THE LED ARRAY AND CHOOSES REPLACEMENT LEDS
  else if (in == 4){//back
    state = 2;}
  else if (in == 0){
    state = 15;}
}
else if (state == 16)
{
  //print "Remove Bad Cells (up)"_f
  //      "Set Refresh Time"
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("BadCellsOff(^)<        ");
  lcd.setCursor(0,1);
  lcd.print("SetRefreshTime         ");
 
  if (in == 1){//up
    state = 15;}
  else if (in == 2){//down
    state = 17;}
  else if (in == 3){//sel
    state = 16;}
  //RUNS A PROGRAM THAT REMOVES THE PREALOCATED BAD CELLS FROM THE ARRAY AND DISSABLE REPLACEMENT LEDS
  else if (in == 4){//back
    state = 2;}
  else if (in == 0){
    state = 16;}
}
else if (state == 17)
{
  //print "Remove Bad Cells (up)"
  //      "Set Refresh Time"_f
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("BadCellsOff(^)       ");
  lcd.setCursor(0,1);
  lcd.print("SetRefreshTime<      ");
  
  if (in == 1){//up
    state = 16;}
  else if (in == 2){//down
    state = 17;}
  else if (in == 3){//sel
    state = 18;}
  else if (in == 4){//back
    state = 2;}
  else if (in == 0){
    state = 17;}
}
else if (state == 18)
{
  //print "Fast"_f
  //      "Slow"
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Fast<            ");
  lcd.setCursor(0,1);
  lcd.print("Slow             ");
  
  if (in == 1){//up
    state = 18;}
  else if (in == 2){//down
    state = 19;}
  else if (in == 3){//sel
    state = 18;}
  //RUN A PROGRAM THAT SETS THE REFRESH RATE TO FAST
  else if (in == 4){//back
    state = 12;}
  else if (in == 0){
    state = 18;}
}
else if (state == 19)
{
  //print "Fast"
  //      "Slow"_f
  //lcd.clear();
  //lcd.noAutoscroll();
  lcd.setCursor(1,0);
  lcd.print("Fast           ");
  lcd.setCursor(0,1);
  lcd.print("Slow<          ");
 
  if (in == 1){//up
    state = 18;}
  else if (in == 2){//down
    state = 19;}
  else if (in == 3){//sel
    state = 19;}
    //RUNS A PROGRAM THAT SETS THE REFRESH RATE TO SLOW
  else if (in == 4){//back
    state = 12;}
  else if (in == 0){
    state = 19;}
}
//end state machine
//
in = 0;//reset input for next loop execution 
}  







