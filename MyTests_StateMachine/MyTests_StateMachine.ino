#include <LiquidCrystal.h>
LiquidCrystal lcd(30, 32, 34, 35, 33, 31); //set up LCD pins


int row[]   =     {46,46,46,46,46,46,46,46,//The high voltage pin information, rows share the same high voltage pin 
                   44,44,44,44,44,44,44,44,
                   12,12,12,12,12,12,12,12,
                   10,10,10,10,10,10,10,10,
                    8, 8, 8, 8, 8, 8, 8, 8, 
                    6, 6, 6, 6, 6, 6, 6, 6, 
                    4, 4, 4, 4, 4, 4, 4, 4, 
                    2, 2, 2, 2, 2, 2, 2, 2};
int column[] =   {46,44,12,10, 8, 6, 4, 2,//The low voltage pin information, columns share the same low voltage pin
                   46,44,12,10, 8, 6, 4, 2,
                   46,44,12,10, 8, 6, 4, 2,
                   46,44,12,10, 8, 6, 4, 2,
                   46,44,12,10, 8, 6, 4, 2,
                   46,44,12,10, 8, 6, 4, 2,
                   46,44,12,10, 8, 6, 4, 2,
                   46,44,12,10, 8, 6, 4, 2};
int cellState[] =  {1, 0, 0, 0, 0, 0, 0, 0,//initalize cell on/off states to off
                    0, 1, 0, 0, 0, 0, 0, 0,
                    0, 0, 1, 0, 1, 0, 0, 0,
                    0, 0, 0, 1, 1, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 1, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 1, 0,
                    0, 0, 0, 0, 1, 0, 0, 1};
int cellBrightness[64];//creates cell brightness matrix, this is initialized at begining of program execution
//int cellBrightness[] =  {255,  0,255,  0,  0,  0,  0,255,//initalize cell brightnesses manually states to off
//                           0,100,  0,255,  0,  0,255,  0,
//                           0,  0,50,  0,  0,255,  0,  0,
//                           0,  0,  0,50,55,  0,  0,  0,
//                           0,  0,  0,25,25,  0,  0,  0,
//                           0,  0,255,  0,  0,10,  0,  0,
//                           0,255,  0,  0,  0,  0,5,  0,
//                         255,  0,  0,  0,  0,  0,  0,200};

long intervalDebounce = 30000;//don't trigger interrupt unless this micros has occured since last interrupt
long previousMicros = 0;

long interval = 100;//interval to decrement in milliseconds (time in minutes to fade from 100 to 0% is about interval*255/(1000*60))
long previousMillis = 0;
int fadeEnable = 0;  //0 if fade and refresh off, 1 if on
long intervalRefresh = interval*200;//interval to decrement in milliseconds (time in minutes to fade from 100 to 0% is about interval*255/(1000*60))
long previousMillisRefresh = 0;

int stepLength = 300;//this is how long each step in the activate and write routines take
                     //300 is about a second per step
int programState = 1;  //determines which program to run, can be manipulated by buttons

int in=0;//the input from the buttons, controls the state machine
int state=1;//the current state of the state machine, determines what's on LCD and value of programState

int val2;   //only used at 1 point in the main loop, but I wasn't sure where else to put this
int index2; //only used at 2 points in the main loop, but I wasn't sure where else to put this

int stateNext;//the next state for the state machine, incorporated to try to save time on execution

void setup()
{  
  for (int i=0; i<=63; i++)//initializes brightnesses of on cells to max, and off to zero
  {
    if(cellState[i] == 1)
    {
      cellBrightness[i] = 255;
    }
    else
    {
      cellBrightness[i] = 0;
    }
  }
  lcd.begin(16, 2);//tells arduion what type of LCD screen is attatched to it
  attachInterrupt(5,detect4,RISING);//sets interupsts to pins buttons are attached to,
  attachInterrupt(4,detect3,RISING);//they trigger on the rising edge of a button push
  attachInterrupt(3,detect2,RISING);
  attachInterrupt(2,detect1,RISING);
  stateLCD();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void detect1()//detects button presses on rising edge and passes on information to program
{
  unsigned long currentMicros = micros();
  if(currentMicros - previousMicros > intervalDebounce)//debounce
  {
    previousMicros = currentMicros;
    if(in==0)//debounce
    {
      in = 1;
      stateChange();
    }
  }
}
void detect2()//detects button presses on rising edge and passes on information to program
{
  unsigned long currentMicros = micros();
  if(currentMicros - previousMicros > intervalDebounce)//debounce
  {
    previousMicros = currentMicros;
    if(in==0)//debounce
    {
      in = 2;
      stateChange();
    }
  }
}
void detect3()//detects button presses on rising edge and passes on information to program
{
  unsigned long currentMicros = micros();
  if(currentMicros - previousMicros > intervalDebounce)//debounce
  {
    previousMicros = currentMicros;
    if(in==0)//debounce
    {
      in = 3;
      stateChange();
    }
  }
}
void detect4()//detects button presses on rising edge and passes on information to program
{
  unsigned long currentMicros = micros();
  if(currentMicros - previousMicros > intervalDebounce)//debounce
  {
    previousMicros = currentMicros;
    if(in==0)//debounce
    {
      in = 4;
      stateChange();
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BLdefault()//Light all bit lines at mid brightness
{
    fade();
    timedRefresh;
    int brightness = 100;
    
    pinMode(46, OUTPUT);
    digitalWrite(46,LOW);  
    pinMode(44, OUTPUT);
    digitalWrite(44,LOW);
    pinMode(12, OUTPUT);
    digitalWrite(12,LOW);
    pinMode(10, OUTPUT);
    digitalWrite(10,LOW);
    pinMode(8, OUTPUT);
    digitalWrite(8,LOW);
    pinMode(6, OUTPUT);
    digitalWrite(6,LOW);
    pinMode(4, OUTPUT);
    digitalWrite(4,LOW);
    pinMode(2, OUTPUT);
    digitalWrite(2,LOW);
    
    pinMode(45, OUTPUT);
    analogWrite(45,brightness);
    delayMicroseconds(100);    
    pinMode(45, INPUT);
    
    pinMode(13, OUTPUT);
    analogWrite(13,brightness);
    delayMicroseconds(100);    
    pinMode(13, INPUT);
    
    pinMode(11, OUTPUT);    
    analogWrite(11,brightness);    
    delayMicroseconds(100);
    pinMode(11, INPUT);    
    
    pinMode(7, OUTPUT);
    analogWrite(7,brightness);
    delayMicroseconds(100);    
    pinMode(7, INPUT);
    
    pinMode(5, OUTPUT);
    analogWrite(5,brightness);
    delayMicroseconds(100);    
    pinMode(5, INPUT);
    
    pinMode(3, OUTPUT);    
    analogWrite(3,brightness);    
    delayMicroseconds(100);
    pinMode(3, INPUT);    
    
    
    pinMode(46, INPUT);    
    pinMode(44, INPUT);
    pinMode(12, INPUT);
    pinMode(10, INPUT);
    pinMode(8, INPUT);
    pinMode(6, INPUT);
    pinMode(4, INPUT);
    pinMode(2, INPUT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This program lights all the bit line LEDs at a low brightness, with the exception of a target BL
//This target BL is illuminated at full brightness on the lower half and is turned off on the upper half
//Noticeable flickering occurs unfortunately 
void LowerBL_DefaultBL(int bitLine)
{    
    fade();
    timedRefresh;
    pinMode(bitLine, OUTPUT);
    digitalWrite(bitLine,LOW);
    
    pinMode(7, OUTPUT);
    analogWrite(7,255);
    delayMicroseconds(100);    
    pinMode(7, INPUT);
    
    pinMode(5, OUTPUT);
    analogWrite(5,255);
    delayMicroseconds(100);    
    pinMode(5, INPUT);
    
    pinMode(3, OUTPUT);    
    analogWrite(3,255);    
    delayMicroseconds(100);
    pinMode(3, INPUT);    
    
    pinMode(bitLine, INPUT);
 ////////////////// Above this line is the code to illuminate the lower half of the bit line,
 ////////////////// Below is the code to turn off the upper half and illuminate the rest of the BL LEDs
 int brightness = 125;   
    
    pinMode(46, OUTPUT);
    digitalWrite(46,LOW);  
    pinMode(44, OUTPUT);
    digitalWrite(44,LOW);
    pinMode(12, OUTPUT);
    digitalWrite(12,LOW);
    pinMode(10, OUTPUT);
    digitalWrite(10,LOW);
    pinMode(8, OUTPUT);
    digitalWrite(8,LOW);
    pinMode(6, OUTPUT);
    digitalWrite(6,LOW);
    pinMode(4, OUTPUT);
    digitalWrite(4,LOW);
    pinMode(2, OUTPUT);
    digitalWrite(2,LOW);
   pinMode(bitLine, INPUT);//Turns off the bit line that is targeted
    
    pinMode(45, OUTPUT);
    analogWrite(45,brightness);
    delayMicroseconds(100);    
    pinMode(45, INPUT);
    
    pinMode(13, OUTPUT);
    analogWrite(13,brightness);
    delayMicroseconds(100);    
    pinMode(13, INPUT);
    
    pinMode(11, OUTPUT);    
    analogWrite(11,brightness);    
    delayMicroseconds(100);
    pinMode(11, INPUT);    
    
    pinMode(7, OUTPUT);
    analogWrite(7,brightness);
    delayMicroseconds(100);    
    pinMode(7, INPUT);
    
    pinMode(5, OUTPUT);
    analogWrite(5,brightness);
    delayMicroseconds(100);    
    pinMode(5, INPUT);
    
    pinMode(3, OUTPUT);    
    analogWrite(3,brightness);    
    delayMicroseconds(100);
    pinMode(3, INPUT);    
    
    
    pinMode(46, INPUT);    
    pinMode(44, INPUT);
    pinMode(12, INPUT);
    pinMode(10, INPUT);
    pinMode(8, INPUT);
    pinMode(6, INPUT);
    pinMode(4, INPUT);
    pinMode(2, INPUT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This program lights all the bit line LEDs at a low brightness, with the exception of a target BL
//This target BL is illuminated at full brightness on the upper half and is turned off on the lower half
//Flickering is not very noticeable 
void UpperBL_DefaultBL(int bitLine)
{
    fade();
    timedRefresh();
    pinMode(bitLine, OUTPUT);
    digitalWrite(bitLine,LOW);
    
    pinMode(45, OUTPUT);
    analogWrite(45,255);
    delayMicroseconds(100);    
    pinMode(45, INPUT);
    
    pinMode(13, OUTPUT);
    analogWrite(13,255);
    delayMicroseconds(100);    
    pinMode(13, INPUT);
    
    pinMode(11, OUTPUT);    
    analogWrite(11,255);    
    delayMicroseconds(100);
    pinMode(11, INPUT);    
    
    pinMode(bitLine, INPUT);
 ////////////////// Above this line is the code to illuminate the upper half of the bit line,
 ////////////////// Below is the code to turn off the lower half and illuminate the rest of the BL LEDs
 int brightness = 125;   
    
    pinMode(46, OUTPUT);
    digitalWrite(46,LOW);  
    pinMode(44, OUTPUT);
    digitalWrite(44,LOW);
    pinMode(12, OUTPUT);
    digitalWrite(12,LOW);
    pinMode(10, OUTPUT);
    digitalWrite(10,LOW);
    pinMode(8, OUTPUT);
    digitalWrite(8,LOW);
    pinMode(6, OUTPUT);
    digitalWrite(6,LOW);
    pinMode(4, OUTPUT);
    digitalWrite(4,LOW);
    pinMode(2, OUTPUT);
    digitalWrite(2,LOW);
   pinMode(bitLine, INPUT);//Turns off the bit line that is targeted
    
    pinMode(45, OUTPUT);
    analogWrite(45,brightness);
    delayMicroseconds(100);    
    pinMode(45, INPUT);
    
    pinMode(13, OUTPUT);
    analogWrite(13,brightness);
    delayMicroseconds(100);    
    pinMode(13, INPUT);
    
    pinMode(11, OUTPUT);    
    analogWrite(11,brightness);    
    delayMicroseconds(100);
    pinMode(11, INPUT);    
    
    pinMode(7, OUTPUT);
    analogWrite(7,brightness);
    delayMicroseconds(100);    
    pinMode(7, INPUT);
    
    pinMode(5, OUTPUT);
    analogWrite(5,brightness);
    delayMicroseconds(100);    
    pinMode(5, INPUT);
    
    pinMode(3, OUTPUT);    
    analogWrite(3,brightness);    
    delayMicroseconds(100);
    pinMode(3, INPUT);    
    
    pinMode(46, INPUT);    
    pinMode(44, INPUT);
    pinMode(12, INPUT);
    pinMode(10, INPUT);
    pinMode(8, INPUT);
    pinMode(6, INPUT);
    pinMode(4, INPUT);
    pinMode(2, INPUT);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void wordLine(int wordLine)//Light's a single word line at full brightness. 
                           //The input to the program is the row pin
{    
    pinMode(wordLine, OUTPUT);
    digitalWrite(wordLine,HIGH);
    
    pinMode(45, OUTPUT);
    digitalWrite(45,LOW);
    pinMode(13, OUTPUT);
    digitalWrite(13,LOW);
    pinMode(11, OUTPUT);
    digitalWrite(11,LOW);
    pinMode(9, OUTPUT);
    digitalWrite(9,LOW);
    pinMode(7, OUTPUT);
    digitalWrite(7,LOW);
    pinMode(5, OUTPUT);
    digitalWrite(5,LOW);
    pinMode(3, OUTPUT);
    digitalWrite(3,LOW);
        
    delayMicroseconds(1000);   
        
    pinMode(45, INPUT);
    pinMode(13, INPUT);
    pinMode(11, INPUT);
    pinMode(9, INPUT);
    pinMode(7, INPUT);
    pinMode(5, INPUT);
    pinMode(3, INPUT);   
    pinMode(wordLine, INPUT);       
}
//////////////////////////////////////////////////////////////////////////////////
//Light Single LED
//Changes values in pin maps where row and column are the same to the place it is expected to light
//////////////////////////////////////////////////////////////////////////////////
void lightSingle(int pina, int pinb, int brightness){

//  int pinRow = pina;
//  int pinCol = pinb;

  if(pina == 46&& pinb ==46){
    pina = 45;
    pinb = 13;}
  if(pina == 44&& pinb ==44){
    pina = 13;
    pinb = 45;}
  if(pina == 12&& pinb ==12){
    pina = 13;
    pinb = 11;}
  if(pina==10 && pinb==10){
    pina = 45;
    pinb = 9;}
  if(pina==8 && pinb==8){
    pina = 9;
    pinb = 7;}
  if(pina==6 && pinb==6){
    pina = 7;
    pinb = 5;}
  if(pina==4 && pinb==4){ 
    pina = 5;
    pinb = 3;}
  if(pina==2 && pinb==2){
    pina = 3;
    pinb = 5;}

  pinMode(pina, OUTPUT);
  pinMode(pinb, OUTPUT);
  digitalWrite(pinb, LOW);
  analogWrite(pina, brightness);
  delayMicroseconds(100);
  pinMode(pina, INPUT);
  pinMode(pinb,INPUT);
}
//////////////////////////////////////////////////////////////////////////////////
void lightCells(){//turns on multiple cells at a time as specified by brightness[] (originally by the cellState[] array)
  for (int i=0; i<=63; i++)
  {
    if(cellBrightness[i] > 0)
    {
      lightSingle(row[i],column[i],cellBrightness[i]);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////
void activate(int index)//this is the activate routine, it also doubles as the read routine
{
  for (int i=0; i<=stepLength; i++)//loop controls length of step
  {
    resting(); //This is the initial state of the board (cells lit, BL 50%) 
  }
  for (int i=0; i<=stepLength; i++)
  {
    resting(); 
    wordLine(row[index]);
  }
  cellBrightness[index] = 10;//dims the target LED
  for (int i=0; i<=stepLength; i++)
  {
    resting(); 
    wordLine(row[index]);
    //lightSingle(row[index],column[index],cellBrightness[index]);
  }
  if(cellState[index] ==1)//(right now this is the only thing that needs the cell state array, all else could use brightness)
  {
    cellBrightness[index] = 255;//puts target LED to full brightness
  }
  else
  {
    cellBrightness[index] = 0;
  }
  for (int i=0; i<=stepLength; i++)
  {
    if((index<=31&&cellState[index]==1)||(index>=32&&cellState[index]==0))
    {
      UpperBL_DefaultBL(column[index]);//replaces resting to alter single BL
    }
    else
    {
      LowerBL_DefaultBL(column[index]);//replaces resting to alter single BL
    }
    lightCells();
    wordLine(row[index]);
    senseAmp(column[index]);
  }
}

//////////////////////////////////////////////////////////////////////////////////
void writeR(int value,int index)//this is the half finished activate routine, pass in a 1 (on) or 0 (off) for the value and the index of the cell (0-63)
{
  activate(index);//runs the activate LED routine first
  if (value != cellState[index])
  {
    if(cellState[index] == 1)
    {
      cellState[index] = 0;
      cellBrightness[index] = 0;
    }
    else
    {
      cellState[index] = 1;
      cellBrightness[index] = 255;
    }
    for (int i=0; i<=stepLength; i++)
    {
      if((index<=31&&cellState[index]==1)||(index>=32&&cellState[index]==0))
      {
        UpperBL_DefaultBL(column[index]);//replaces resting to alter single BL
      }
      else
      {
      LowerBL_DefaultBL(column[index]);//replaces resting to alter single BL
      }
      lightCells();
      wordLine(row[index]);
      senseAmp(column[index]);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////
void resting()//This is the state of the board in between write/read/refresh
{
  BLdefault(); 
  lightCells();
}
//////////////////////////////////////////////////////////////////////////////////
void senseAmp(int column)//This lights a single sense amp LED at full brightness
{
  lightSingle(9,column,255);
}
//////////////////////////////////////////////////////////////////////////////////
void fade()
{
  if(fadeEnable == 1)//SHOULD PROBABLY DELETE THIS CONDITION
  {
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval)// check to see if it's time to blink the LED; 
    {
       previousMillis = currentMillis;// save the last time you blinked the LED 
       for(int index=0; index<=63; index++)
       {
         if(cellState[index] == 1)
         {
           cellBrightness[index] = cellBrightness[index]-1;
           if(cellBrightness[index] == 0)
           {
             cellState[index] = 0;
           }
         }
       }
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////
void refresh()//This performs a write of the same value on every cell LED; 
{
  for(int index=0; index<=63; index++)
  {
    //activate(index);
    writeR(cellState[index],index);//the reason an activate was not chosen was because this resets a faded LED to full brightness
  } 
}
//////////////////////////////////////////////////////////////////////////////////
void timedRefresh()//This performs a refresh if LED fading is enabled, and performs it rapidly regardless of the step length
{                      //the idea was to call this instead of fade for the timed refresh, and fade for the manual one
  if(fadeEnable == 1)
  {  
    int tempStepLength = stepLength;
    stepLength = 30; 
    refresh();
    stepLength = tempStepLength;
  }  
}    

//////////////////////////////////////////////////////////////////////////////////
void randomRW()
{
  int index = random(64);//random number between 0 and 63 (inclusive) to determine targeted cell
  int RW = random(9);//random number between 0 and 3 (inclusive) to determine state to write, or if it should write at all
  if (RW >1)//75% chance of nothing happening for 1 step length
  {
    for (int i=0; i<=stepLength; i++)
    {
       resting();
    }
  }
  else
  {
  writeR(RW,index);// read appears identical to writing same value, so this is fine for both
  }
}
//////////////////////////////////////////////////////////////////////////////////
void triggerRefresh()
{
  unsigned long currentMillisRefresh = millis();
  if(currentMillisRefresh - previousMillisRefresh > intervalRefresh)// check to see if it's time to blink the LED; 
  {
     previousMillisRefresh = currentMillisRefresh;//save the last time you blinked the LED 
     timedRefresh();
  }
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void stateLCD()  //this program writes different messages to the LCD dependent upon the state
{                //for each state, the first two lines are what is displayed on the LCD screen
  if (state == 1)//the third line is obsolete code it turned out doesn't seem to be needed
  { 
    //print "Select Mode"_f
    //      "Settings"
    //lcd.clear();
    lcd.noAutoscroll();
    lcd.setCursor(1,0);
    lcd.println("Select Mode<    ");
    lcd.setCursor(0,1);
    lcd.print("Settings(v)     ");
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
    lcd.print("ChargeLeak         ");
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
    lcd.print("ChargeLeak<      ");
  }
  else if (state == 18)
  {
    //print "Fast"_f
    //      "Slow"
    //lcd.clear();
    //lcd.noAutoscroll();
    lcd.setCursor(1,0);
    lcd.print("On<            ");
    lcd.setCursor(0,1);
    lcd.print("Off             ");
  }
  else if (state == 19)
  {
    //print "Fast"
    //      "Slow"_f
    //lcd.clear();
    //lcd.noAutoscroll();
    lcd.setCursor(1,0);
    lcd.print("On           ");
    lcd.setCursor(0,1);
    lcd.print("Off<          ");
  }
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void stateChange()
{
  if (state == 1) 
  { 
    if (in == 1){//up
      stateNext = 1;}
    else if (in == 2){//down
      stateNext = 2;}
    else if (in == 3){//sel
      stateNext = 4;}
    else if (in == 4){//back
      stateNext = 1;}
    else if (in == 0){
      stateNext = 1;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  } 
  else if (state == 2)
  {
    if (in == 1){//up
      stateNext = 1;}
    else if (in == 2){//down
      stateNext = 3;}
    else if (in == 3){//sel
      stateNext = 12;}
    else if (in == 4){//back
      stateNext = 2;}
    else if (in == 0){
      stateNext = 2;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 3)
  {
    if (in == 1){//up
      stateNext = 2;}
    else if (in == 2){//down
      stateNext = 3;}
    else if (in == 3)//sel
    {
      stateNext = 3;
      //RUN AUTOMATIC REFRESH, RUN DEFAULT SETTINGS, RUN RANDOM R/W
    }
    else if (in == 4){//back
      stateNext = 3;}
    else if (in == 0){
      stateNext = 3;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 4)
  {
    if (in == 1){//up
      stateNext = 4;}
    else if (in == 2){//down
      stateNext = 5;}
    else if (in == 3){//sel
      stateNext = 9;}
    else if (in == 4){//back
      stateNext = 1;}
    else if (in == 0){
      stateNext = 4;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 5)
  {
    if (in == 1){//up
      stateNext = 4;}
    else if (in == 2){//down
      stateNext = 5;}
    else if (in == 3){//sel
      stateNext = 6;}
    else if (in == 4){//back
      stateNext = 1;}
    else if (in == 0){
      stateNext = 5;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 6)
  {
    if (in == 1){//up
      stateNext = 6;}
    else if (in == 2){//down
      stateNext = 7;}
    else if (in == 3){//sel
      stateNext = 6;
      programState = 1;}
    //RUN RANDOM READ WRITE PROGRAM TO SET BOARD TO RANDOM READ WRITE MODE  -----Done
    else if (in == 4){//back
      stateNext = 4;}
    else if (in == 0){
      stateNext = 6;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 7)
  {
    if (in == 1){//up
      stateNext = 6;}
    else if (in == 2){//down
      stateNext = 8;}
    else if (in == 3){//sel
      stateNext = 7;
      programState = 3;}
    //RUN A SINGLE READ PROGRAM AND THEN SET BOARD TO RANDOM READ WRITE MODE AFTER READ FINISHED --- Done
    else if (in == 4){//back
      stateNext = 4;}
    else if (in == 0){
      stateNext = 7;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 8)
  {
    if (in == 1){//up
      stateNext = 7;}
    else if (in == 2){//down
      stateNext = 8;}
    else if (in == 3){//sel
      stateNext = 8;
      programState = 2;}
      //RUN A SINGLE WRITE PROGRAM AND THEN SET BOARD TO RANDOM READ WRITE MODE AFTER FINISHED --- Done
    else if (in == 4){//back
      stateNext = 4;}
    else if (in == 0){
      stateNext = 8;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 9)
  {
    if (in == 1){//up
      stateNext = 9;}
    else if (in == 2){//down
      stateNext = 10;}
    else if (in == 3){//sel
      stateNext = 9;}
    //SET THE LEDS TO RUN IN AUTOMATIC REFRESH MODE
    else if (in == 4){//back
      stateNext = 4;}
    else if (in == 0){
      stateNext = 9;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 10)
  {
    if (in == 1){//up
      stateNext = 9;}
    else if (in == 2){//down
      stateNext = 10;}
    else if (in == 3){//sel
      stateNext = 11;}
    //DISABLE THE AUTOMATIC REFRESH ROUTINE, ENABLE MANUAL REFRESH MODE
    else if (in == 4){//back
      stateNext = 4;}
    else if (in == 0){
      stateNext = 10;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 11)
  {
    if (in == 1){//up
      stateNext = 11;}
    else if (in == 2){//down
      stateNext = 11;}
    else if (in == 3){//sel
      stateNext = 11;
      programState = 4;}
    //RUN A MANUAL REFRESH ON THE LEDS IN THE BOARD --- Done
    else if (in == 4){//back
      stateNext = 9;}
    else if (in == 0){
      stateNext = 11;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 12)
  {
    if (in == 1){//up
      stateNext = 12;}
    else if (in == 2){//down
      stateNext = 15;}
    else if (in == 3){//sel
      stateNext = 13;}
    else if (in == 4){//back
      stateNext = 2;}
    else if (in == 0){
      stateNext = 12;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 13)
  {
    if (in == 1){//up
      stateNext = 13;}
    else if (in == 2){//down
      stateNext = 14;}
    else if (in == 3){//sel
      stateNext = 13;
      stepLength = 30;}
      //RUN A PROGRAM THAT SETS THE SPEED OF EVERYTHING TO FAST -----done
    else if (in == 4){//back
      stateNext = 12;}
    else if (in == 0){
      stateNext = 13;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 14)
  {
    if (in == 1){//up
      stateNext = 13;}
    else if (in == 2){//down
      stateNext = 14;}
    else if (in == 3){//sel
      stateNext = 14;
      stepLength = 300;}
      //RUN A PROGRAM THAT SETS THE SPEED OF EVERYTHING TO SLOW -----done
    else if (in == 4){//back
      stateNext = 12;}
    else if (in == 0){
      stateNext = 14;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 15)
  {
    if (in == 1){//up
      stateNext = 12;}
    else if (in == 2){//down
      stateNext = 16;}
    else if (in == 3){//sel
      stateNext = 15;}
      //RUNS A PROGRAM THAT INSERTS PREALOCATED BAD CELLS INTO THE LED ARRAY AND CHOOSES REPLACEMENT LEDS
    else if (in == 4){//back
      stateNext = 2;}
    else if (in == 0){
      stateNext = 15;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 16)
  {
    if (in == 1){//up
      stateNext = 15;}
    else if (in == 2){//down
      stateNext = 17;}
    else if (in == 3){//sel
      stateNext = 16;}
    //RUNS A PROGRAM THAT REMOVES THE PREALOCATED BAD CELLS FROM THE ARRAY AND DISSABLE REPLACEMENT LEDS
    else if (in == 4){//back
      stateNext = 2;}
    else if (in == 0){
      stateNext = 16;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 17)
  {
    if (in == 1){//up
      stateNext = 16;}
    else if (in == 2){//down
      stateNext = 17;}
    else if (in == 3){//sel
      stateNext = 18;}
    else if (in == 4){//back
      stateNext = 2;}
    else if (in == 0){
      stateNext = 17;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 18)
  {
    if (in == 1){//up
      stateNext = 18;}
    else if (in == 2){//down
      stateNext = 19;}
    else if (in == 3){//sel
      stateNext = 18;
      fadeEnable = 1;}
    //RUN A PROGRAM THAT ENABLES FADE AND REFRESH ROUTINE
    else if (in == 4){//back
      stateNext = 12;}
    else if (in == 0){
      stateNext = 18;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  else if (state == 19)
  {
    if (in == 1){//up
      stateNext = 18;}
    else if (in == 2){//down
      stateNext = 19;}
    else if (in == 3){//sel
      stateNext = 19;
      fadeEnable = 0;}
      //RUNS A PROGRAM THAT DISABLES FADE AND REFRESH ROUTINE
    else if (in == 4){//back
      stateNext = 12;}
    else if (in == 0){
      stateNext = 19;}
    if (stateNext != state){
      state = stateNext;
      stateLCD();}    
  }
  in = 0;
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void loop()//always running, performs something different with LEDs dependent on programState
{
//////////////////////////////////////////////////////////////////////////////////  
  if (programState == 0)//no read writes
  {
    resting();
  }
  else if (programState == 1)//random read writes
  {
    randomRW();
  }
  else if (programState == 2)//single write, opposite value, random location
  { 
    index2 = random(64);//random location, 0 to 63
    if (cellState[index2] ==1)//ensures opposite value
    {  
      val2 = 0;
    }
    else
    {
      val2 = 1;
    }
    writeR(val2,index2);
    programState = 0;
  }
  else if (programState == 3)//single read, random location
  {
    index2 = random(64);
    activate(index2);
    programState = 0;
  }
  else if (programState == 4)//single refresh
  {
    refresh();
    programState = 0;
  }
//////////////////////////////////////////////////////////////////////////////////  
//////////////////////////////////////////////////////////////////////////////////  
//////////////////////////////////////////////////////////////////////////////////  
//////////////////////////////////////////////////////////////////////////////////
}


