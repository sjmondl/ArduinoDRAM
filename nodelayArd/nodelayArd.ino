#include <LiquidCrystal.h>

#define DELAY_AMOUNT 1

#define WRITE_TIME 5 //dont reduce past 5, the arduino cant deacivate pins fast enough to prevent artifacts
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //set up LCD pins

/*Subroutines included in this file:
 // void memWrite(int pina,int pinb), lights a row and a column, handles errors for cells that can
 // void lightRow(int pinb), lights the row associated with pinb
 // void lightCol(intpina), lights the column associated with pina
 // void lightLeds(int pina, int pinb), lights the LED associated with pina,pinb for the amount determined by DELAY_AMOUNT
 // void lightLeds(int pina, int pinb, delay_am), lights the LED associated with pina,pinb for the amount determined by delay_am
 // void fadeLeds(int pina, int pinb), Fades the LED associated with pina, pinb
 // void cycle(byte pins[], int sizeOfPins); cycles through all hooked up LEDs one at a time
 // void cycle(), same as above, use this one to call it for testing
 // void cycle(byte pins_x[], byte pins_y[], int sizeOfPins_x, int sizeOfPins_y), same as above
 // void run_unittests(), testing program
 */

byte pins[] = {
  13, 10, 9, 8, 7, 6, 22, 24, 26, 44, 45, 46
};
int sizePins = 15;
int prgmSelected = 0;

unsigned long previousMillis = millis();

//Light a row of LEDs. PinA varries while pinb is fixed
void lightRow(int pinb) {

  pinMode(pinb, OUTPUT);
  digitalWrite(pinb, LOW);

  for (int i = 0; i < sizePins; ++i)
  {
    pinMode(pins[i], OUTPUT);
    if (pins[i] != pinb) {
      digitalWrite(pins[i], HIGH);
    }
  }
  unsigned long currentMillis = millis();

 

  for (int j = 0; j < sizePins; ++j)
  {
     unsigned long elasped = currentMillis - previousMillis;
     if(elasped >= WRITE_TIME){
     pinMode(pins[j], INPUT);
      
     previousMillis =currentMillis;
     currentMillis = millis();
    
    }
    
    pinMode(pinb, INPUT);

  }
}



//Light a Column of LEDs
void lightCol(int pina) {
  previousMillis = millis();


  pinMode(pina, OUTPUT);
  digitalWrite(pina, HIGH);


  for (int i = 0; i < sizePins; ++i)
  {
    pinMode(pins[i], OUTPUT);
    if (pins[i] != pina) {
      digitalWrite(pins[i], LOW);

    }
  }
  unsigned long currentMillis = millis();
  unsigned long elasped = currentMillis - previousMillis;

  for (int j = 0; j < sizePins; ++j)
  {
    if (currentMillis >= WRITE_TIME) {
      pinMode(pins[j], INPUT);
    }

    pinMode(pina, INPUT);


  }
}






//Light LEDs, pina fixed, while pinb cycles
void lightLeds(int pina, int pinb)
{
  previousMillis = millis();
  if (pina != pinb)
  {
    pinMode(pina, OUTPUT);
    pinMode(pinb, OUTPUT);
    digitalWrite(pinb, LOW);

    analogWrite(pina, 255);
    unsigned long currentMillis = millis();
    unsigned long elasped = currentMillis - previousMillis;
    if (elasped >= WRITE_TIME) {

      pinMode(pina, INPUT);
      pinMode(pinb, INPUT);
    }
  }
}


//Light LEDs, delay_am controls how long LED remains lit
void lightLeds(int pina, int pinb, int delay_am)
{
  previousMillis = millis();
  if (pina != pinb)
  {
    pinMode(pina, OUTPUT);
    pinMode(pinb, OUTPUT);
    digitalWrite(pinb, LOW);
    unsigned long currentMillis = millis();
    analogWrite(pina, 255);
    unsigned long elasped = currentMillis - previousMillis;
    if (elasped >=delay_am) {
      pinMode(pina, INPUT);
      pinMode(pinb, INPUT);
    }
  }
}



/*Fade the LED to represent capacitor discharge
 (pina, pinb, rate to fade at(higher=slower), time to hold at 0, percentage max brightness of LED)
 If you decrease brightness, you must increase the rate feild to compensate
 void fadeLeds(int pina, int pinb, double rate,double delayAm, double bright)
 PinA will be set to relative high to light the correct cell LED
 */
void fadeLeds(int pina, int pinb, double rate, double delayAm, double bright)
{
  pinMode(pina, OUTPUT);
  pinMode(pinb, OUTPUT);
  analogWrite(pina, (bright * 255));
  int i = 0;

  while (i < bright * 250) {


    analogWrite(pinb, i);
    delay(rate);
    ++i;
  }
  analogWrite(pinb, bright * 255);
  delay(delayAm);

}



/**
 * Run the default cycle
 */
void cycle()
{
  byte pins[] = {
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 44, 45, 46
  };
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
      fadeLeds(pins[i], pins[j], 5, 1, 1);
    }
  }
}

void run_unittests()
{
  for (int i = 0; i < 5; ++i)
  {
    byte pins[] = {
      2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 44, 45, 46
    };
    int sizeOfPins = 15;
    cycle(pins, sizeOfPins);
  }

  for (int i = 0; i < 5; ++i)
  {
    byte pins[] = {
      5, 6, 7, 8, 9
    };
    byte sizeOfPins = 5;
    cycle(pins, sizeOfPins);
  }

  for (int i = 0; i < 5; ++i)
  {
    byte pins_x[] = {
      5, 6, 7, 8, 9
    };
    byte sizeOfPins_x = 5;

    byte pins_y[] = {
      2, 3, 4, 5, 6, 7
    };
    byte sizeOfPins_y = 6;
    cycle(pins_x, pins_y, sizeOfPins_x, sizeOfPins_y);
  }

}




void setup() {
  lcd.begin(16, 2);

}


void loop() {
  //go through a series of cell writes
  //the delays help with some stray lighting
  lightRow(10);
  //lightCol(13);


}












