#define DELAY_AMOUNT 0

byte pins[] = {
  2,3,4,5,6,7,8,9,10,11,12,13,44,45,46};
int sizePins = 15;
/*Memory write routine*/
void memWrite(int pina, int pinb){
  for(int j =0; j<2; j++){ 
    //Light column
    for(int i = 0; i<2; i++){
      lightCol(pinb);
    }

    //Light row
    for(int i = 0; i<200; i++){
      lightRow(pina);
    }

  }
  //Light memory cell 

lightLeds(pina,pinb);

}
void lightCol(int pinb){
  for (int i = 0; i < sizePins; ++i)
  {
    lightLeds(pins[i],pinb);  
  } 

}
void lightRow(int pina){
  for (int i = 0; i < sizePins; ++i)
  {
    lightLeds(pina, pins[i]);  
  } 

}





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

// Subroutines

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

void run_unittests()
{
  for (int i = 0; i < 5; ++i)
  {
    byte pins[] = {
      2,3,4,5,6,7,8,9,10,11,12,13,44,45,46      };
    int sizeOfPins = 15;
    cycle(pins, sizeOfPins);
  }

  for (int i = 0; i < 5; ++i)
  {
    byte pins[] = {
      5,6,7,8,9        };
    byte sizeOfPins = 5;
    cycle(pins, sizeOfPins);
  }

  for (int i = 0; i < 5; ++i)
  {
    byte pins_x[] = {
      5,6,7,8,9        };
    byte sizeOfPins_x = 5;

    byte pins_y[] = {
      2,3,4,5,6,7        };
    byte sizeOfPins_y = 6;
    cycle(pins_x, pins_y, sizeOfPins_x, sizeOfPins_y);
  }
}


// Subroutines

void setup(){
}

void loop(){//the continuous loop; fades 1 led
  memWrite(6,4);
}


