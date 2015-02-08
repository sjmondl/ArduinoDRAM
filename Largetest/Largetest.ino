#define DELAY_AMOUNT .5

byte pins[] = {
  2,3,4,5,6,7,8,42,46};
int sizePins = 15;
/*Memory write routine*/
void memWrite(int pina, int pinb){
  //Error handling for cells with inconsistant pins, i.e. the diagonal cells
  //Take the invalid cells and light them using those pins, but alter the row 
  //and column pins to achieve correct behavior
  int pinRow = pina;
  int pinCol = pinb;


  if(pina == 45&& pinb ==13){
    pinRow = 46;
    pinCol = 46;
  }
  
  if(pina == 13&& pinb ==45){
    pinRow = 44;
    pinCol = 44;
  }

  if(pina == 13&& pinb ==11){
    pinRow = 12;
    pinCol = 12;
  }

  if(pina==45 && pinb==9){
    pinRow = 10;
    pinCol = 10;
  }

  if(pina==9 && pinb==7){
    pinRow = 8;
    pinCol = 8;
  }

  if(pina==7 && pinb==5){
    pinRow = 6;
    pinCol = 6;
  }
  if(pina==5 && pinb==3){ 
    pinRow = 4;
    pinCol = 4;
  }
  if(pina==3 && pinb==5){
    pinRow = 3;
    pinCol = 3;
  }
 
  //Light columns and rows, cycle program 1000 times(~1-3s)
  for(int k = 0; k<1000; k++){

    //Light column
    lightCol(pinCol);
    //Light row
    lightRow(pinRow);
  }

  //Light memory cell, hold for ~4s 
  // lightLeds(pina,pinb, 4000);
  
  //Fade the LED to represent capacitor discharge
  //(pina, pinb, rate to fade at(higher=slower), time to hold at 0, percentage max brightness of LED)
  // If you decrease brightness, you must increase the rate feild to compensate 
  fadeLeds(pina,pinb, 6, 10, 1);

}



//Light a column of LEDs. PinA varries while pinb is fixed
void lightCol(int pinb){
  for (int i = 0; i < sizePins; ++i)
  {
    lightLeds(pins[i],pinb);  
  } 

}


//Light a row of LEDs
void lightRow(int pina){
  for (int i = 0; i < sizePins; ++i)
  {
    lightLeds(pina, pins[i]);  
  } 

}

//Light LEDs, pina fixed, while pinb cycles
void lightLeds(int pina, int pinb)
{
  if (pina != pinb)
  {
    pinMode(pina, OUTPUT);
    pinMode(pinb, OUTPUT);
    digitalWrite(pinb, LOW);

    analogWrite(pina, 255);
    delay(DELAY_AMOUNT);

    pinMode(pina, INPUT);
    pinMode(pinb, INPUT);
  }
}


//Light LEDs, delay_am controls how long LED remains lit
void lightLeds(int pina, int pinb,int delay_am)
{
  if (pina != pinb)
  {
    pinMode(pina, OUTPUT);
    pinMode(pinb, OUTPUT);
    digitalWrite(pinb, LOW);

    analogWrite(pina, 255);
    delay(delay_am);

    pinMode(pina, INPUT);
    pinMode(pinb, INPUT);
  }
}



/*Fade the LED to represent capacitor discharge
  (pina, pinb, rate to fade at(higher=slower), time to hold at 0, percentage max brightness of LED)
  If you decrease brightness, you must increase the rate feild to compensate 
  void fadeLeds(int pina, int pinb, double rate,double delayAm, double bright)
  PinA will be set to relative high to light the correct cell LED
*/
void fadeLeds(int pina,int pinb,double rate,double delayAm, double bright)
{
  pinMode(pina, OUTPUT);
  pinMode(pinb, OUTPUT);
  analogWrite(pina,(bright*255));
 int i =0;

  while(i<bright*250){


    analogWrite(pinb, i);
    delay(rate);
    ++i;
  }
  analogWrite(pinb, bright*255);
  delay(delayAm);
}



/** 
 * Run the default cycle
 */
void cycle()
{
  byte pins[] = {
    2,3,4,5,6,7,8,9,10,11,12,13,44,45,46    };
  int sizeOfPins = 15;

  cycle(pins, sizeOfPins);
}

/** 
 * Control the pins by setting the array in the first parameter,
 * and setting the size in the second parameter
 */
void cycle(byte pins[], int sizeOfPins)
{
  for (int i = 0; i < sizeOfPins; ++i)
  {
    for (int j = 0; j < sizeOfPins; ++j)
    {
      lightLeds(pins[i], pins[j]);  
    } 
  }
}

/** 
 * Control the pins by setting two arrays, where the x array is run x times,
 * and the y array is run y * x - (number of repeat elements in both array).
 */
void cycle(byte pins_x[], byte pins_y[], int sizeOfPins_x, int sizeOfPins_y)
{
  for (int i = 0; i < sizeOfPins_x; ++i)
  {
    for (int j = 0; j < sizeOfPins_y; ++j)
    {
      lightLeds(pins_x[i], pins_y[j]);  
      
    } 
  }
}

void fadeCycle(byte pins[], int sizeOfPins)
{
  for (int i = 0; i < sizeOfPins; ++i)
  {
    for (int j = 0; j < sizeOfPins; ++j)
    {
      lightLeds(pins[i], pins[j]);  
      fadeLeds(pins[i],pins[j], 5,1,1);
    } 
  }
}

void run_unittests()
{
  for (int i = 0; i < 5; ++i)
  {
    byte pins[] = {
      2,3,4,5,6,7,8,9,10,11,12,13,44,45,46                      };
    int sizeOfPins = 15;
    cycle(pins, sizeOfPins);
  }

  for (int i = 0; i < 5; ++i)
  {
    byte pins[] = {
      5,6,7,8,9                        };
    byte sizeOfPins = 5;
    cycle(pins, sizeOfPins);
  }

  for (int i = 0; i < 5; ++i)
  {
    byte pins_x[] = {
      5,6,7,8,9                        };
    byte sizeOfPins_x = 5;

    byte pins_y[] = {
      2,3,4,5,6,7                        };
    byte sizeOfPins_y = 6;
    cycle(pins_x, pins_y, sizeOfPins_x, sizeOfPins_y);
  }
}




void setup(){
}

void loop(){
  //go through a series of cell writes
  memWrite(5,3);
  


}






