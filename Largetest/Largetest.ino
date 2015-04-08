#include <LiquidCrystal.h>

#define DELAY_AMOUNT 1
#define SENSE_TIME 8 //How long the sense amp should stay lit before activating the cell
#define WRITE_TIME 500 
#define FLICKER 2

/*Subroutines */

byte pins[] = {
  2,3,4,5,6,7,8,9,10,11,12,13,44,45,46};

byte topBitline[] = { 
  45,13,11};
byte bottomBitline[] ={
  7,5,3};

byte senseAmpRow[]={9}; 

byte wordlines[]={
  46,44,12,10,8,6,4,2};
byte noCellWordlines[]={
  45,13, 11,9,7,5,3};


int sizePins = 15;





/////////////////////////////////////////////////////////////////////////////////////////////////////
//Light LEDs, pina fixed, while pinb cycles                                                        //
/////////////////////////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////
//Light Single LED
//////////////////////////////////////////////////////////////////////////////////
void lightSingle(int pina, int pinb){

  int pinRow = pina;
  int pinCol = pinb;


  if(pina == 46&& pinb ==46){
    pina = 45;
    pinb = 13;
  }

  if(pina == 45&& pinb ==45){
    pina = 13;
    pinb = 45;
  }

  if(pina == 12&& pinb ==12){
    pina = 13;
    pinb = 11;
  }

  if(pina==10 && pinb==10){
    pina = 45;
    pinb = 9;
  }

  if(pina==8 && pinb==8){
    pina = 9;
    pinb = 7;
  }

  if(pina==6 && pinb==6){
    pina = 7;
    pinb = 5;
  }
  if(pina==4 && pinb==4){ 
    pina = 5;
    pinb = 3;
  }
  if(pina==3 && pinb==3){
    pina = 3;
    pinb = 5;
  }

  pinMode(pina, OUTPUT);
  pinMode(pinb, OUTPUT);
  digitalWrite(pinb, LOW);
  analogWrite(pina, 255);
  delay(SENSE_TIME);
  pinMode(pina, INPUT);
  pinMode(pinb,INPUT);
   
  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//Light LEDs, delay_am controls how long LED remains lit
/////////////////////////////////////////////////////////////////////////////////////////////////////
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
   if(pina == 46&& pinb ==46){
    pina = 45;
    pinb = 13;
  }

  if(pina == 45&& pinb ==45){
    pina = 13;
    pinb = 45;
  }

  if(pina == 12&& pinb ==12){
    pina = 13;
    pinb = 11;
  }

  if(pina==10 && pinb==10){
    pina = 45;
    pinb = 9;
  }

  if(pina==8 && pinb==8){
    pina = 9;
    pinb = 7;
  }

  if(pina==6 && pinb==6){
    pina = 7;
    pinb = 5;
  }
  if(pina==4 && pinb==4){ 
    pina = 5;
    pinb = 3;
  }
  if(pina==3 && pinb==3){
    pina = 3;
    pinb = 5;
  }
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
 pinMode(pina, INPUT);
 pinMode(pinb, INPUT);
}

//////////////////////////////////////////////////////////////////
//Light 2 test
//////////////////
void lightTwo(int pin1, int pin2, int pin3, int pin4, int delayAm){
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  digitalWrite(pin2, LOW);
  analogWrite(pin1,255);
  delay(delayAm);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
   pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  digitalWrite(pin4, LOW);
  analogWrite(pin3,255);
  delay(delayAm);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
  
}

/** 
 * Run the default cycle
 */
void cycle()
{
  byte pins[] = {
    2,3,4,5,6,7,8,9,10,11,12,13,44,45,46                  };
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
      2,3,4,5,6,7,8,9,10,11,12,13,44,45,46                                                 };
    int sizeOfPins = 15;
    cycle(pins, sizeOfPins);
  }

  for (int i = 0; i < 5; ++i)
  {
    byte pins[] = {
      5,6,7,8,9                                                    };
    byte sizeOfPins = 5;
    cycle(pins, sizeOfPins);
  }

  for (int i = 0; i < 5; ++i)
  {
    byte pins_x[] = {
      5,6,7,8,9                                                    };
    byte sizeOfPins_x = 5;

    byte pins_y[] = {
      2,3,4,5,6,7                                                    };
    byte sizeOfPins_y = 6;
    cycle(pins_x, pins_y, sizeOfPins_x, sizeOfPins_y);
  }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*Light row north of sense amps
 *///////////////////////////////////////////////////////////////////////////////////////////////////
void lightTopBitline(int pina){ 

  pinMode(pina, OUTPUT);
  digitalWrite(pina, LOW);

  for(int i =0; i<3; i++){

    if ((topBitline[i] != pina) ){ 
      if(pina == 45&&  topBitline[i] ==13){
        pinMode(pina, INPUT);
        pinMode( topBitline[i], INPUT);
      }

      if(pina == 13&&  topBitline[i] ==45){
        pinMode(pina, INPUT);
        pinMode( topBitline[i], INPUT);
      }

      if(pina == 13&&  topBitline[i] ==11){
        pinMode(pina, INPUT);
        pinMode( topBitline[i], INPUT);
      }

      if(pina==45 &&  topBitline[i]==9){
        pinMode(pina, INPUT);
        pinMode( topBitline[i], INPUT);
      }

      if(pina==9 &&  topBitline[i]==7){
        pinMode(pina, INPUT);
        pinMode( topBitline[i], INPUT);
      }

      if(pina==7 &&  topBitline[i]==5){
        pinMode(pina, INPUT);
        pinMode( topBitline[i], INPUT);
      }
      if(pina==5 &&  topBitline[i]==3){ 
        pinMode(pina, INPUT);
        pinMode( topBitline[i], INPUT);
      }
      if(pina==3 &&  topBitline[i]==5){
        pinMode(pina, INPUT);
        pinMode( topBitline[i], INPUT);
      }
      else{

        digitalWrite(topBitline[i], HIGH);
        pinMode(topBitline[i], OUTPUT);


      }
    }
  }

  // delay(WRITE_TIME);
  for (int j=0;j < 3; ++j) {
    pinMode(topBitline[j], INPUT);
    pinMode(pina, INPUT);



  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*Light row south of sense amps*/
/////////////////////////////////////////////////////////////////////////////////////////////////////
void lightbtmBitline(int pina){ 

  pinMode(pina, OUTPUT);
  digitalWrite(pina, LOW);

  for(int i =0; i<3; i++){

    if ((bottomBitline[i] != pina) ){ 

      //Handle the diagnal pins with inconsistant numbering
      if(pina == 45&&  bottomBitline[i] ==13){
        pinMode(pina, INPUT);
        pinMode( bottomBitline[i], INPUT);
      }

      if(pina == 13&&  bottomBitline[i] ==45){
        pinMode(pina, INPUT);
        pinMode( bottomBitline[i], INPUT);
      }

      if(pina == 13&&  bottomBitline[i] ==11){
        pinMode(pina, INPUT);
        pinMode( bottomBitline[i], INPUT);
      }

      if(pina==45 &&  bottomBitline[i]==9){
        pinMode(pina, INPUT);
        pinMode( bottomBitline[i], INPUT);
      }

      if(pina==9 &&  bottomBitline[i]==7){
        pinMode(pina, INPUT);
        pinMode( bottomBitline[i], INPUT);
      }

      if(pina==7 &&  bottomBitline[i]==5){
        pinMode(pina, INPUT);
        pinMode( bottomBitline[i], INPUT);
      }
      if(pina==5 &&  bottomBitline[i]==3){ 
        pinMode(pina, INPUT);
        pinMode( bottomBitline[i], INPUT);
      }
      if(pina==3 &&  bottomBitline[i]==5){
        pinMode(pina, INPUT);
        pinMode( bottomBitline[i], INPUT);
      }
      else{
        //Ligth the LEDs
        digitalWrite(bottomBitline[i], HIGH);
        pinMode(bottomBitline[i], OUTPUT);
      }
    }
  }


//Deactivate the LEDs
  for (int j=0;j < 3; ++j) {
    pinMode(bottomBitline[j], INPUT);
    pinMode(pina, INPUT);



  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//ligth top word lines by setting pin selection high and cycling through others and setting them low
/////////////////////////////////////////////////////////////////////////////////////////////////////
void lightWord(int pina){


  pinMode(pina, OUTPUT);
  digitalWrite(pina, HIGH);

  for (int i = 0; i < 8; ++i)
  {
    pinMode(noCellWordlines[i], OUTPUT);
    digitalWrite(noCellWordlines[i], LOW);



  }

  for (int j=0;j < 8; ++j)
  { 
    pinMode(noCellWordlines[j], INPUT);
    pinMode(pina, INPUT);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Light word and bit lines
/////////////////////////////////////////////////////////////////////////////////////////////////////
void bitWord(int pina, int pinb){


  lightWord(pina);
//  if(pina >9){
    lightTopBitline(pinb);
//  }
//if(pina <9){
    lightbtmBitline(pinb);
//  }


}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//Cycle through word lines (Rows, no cells)
/////////////////////////////////////////////////////////////////////////////////////////////////////
void wordCycle(){
  for(int i = 0; i<8; i++){
    lightWord(wordlines[i]);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//Cycle through bit lines (Columns, non cells)
/////////////////////////////////////////////////////////////////////////////////////////////////////
void bitCycle(){
  for(int i = 0; i<8; ++i){
    lightTopBitline(wordlines[i]);
  }
  for(int i = 0; i<8; ++i){
    lightbtmBitline(wordlines[i]);
    {

    }  
  }

}
void lightMult( double bright,
                int pin1, int pin2, int rate1, 
                int pin3, int pin4, int rate2, 
                int pin5, int pin6, int rate3,
                int pin7, int pin8, int rate4,
                int pin9, int pin10,int rate5){
 if(pin1 == 46&& pin2 ==46){
    pin1 = 45;
    pin2 = 13;
  }

  if(pin1 == 45&& pin2 ==45){
    pin1 = 13;
    pin2 = 45;
  }

  if(pin1 == 12&& pin2 ==12){
    pin1 = 13;
    pin2 = 11;
  }

  if(pin1==10 && pin2==10){
    pin1 = 45;
    pin2 = 9;
  }

  if(pin1==8 && pin2==8){
    pin1 = 9;
    pin2 = 7;
  }

  if(pin1==6 && pin2==6){
    pin1 = 7;
    pin2 = 5;
  }
  if(pin1==4 && pin2==4){ 
    pin1 = 5;
    pin2 = 3;
  }
  if(pin1==3 && pin2==3){
    pin1 = 3;
    pin2 = 5;
  }

  if(pin3 == 46&& pin4 ==46){
    pin3 = 45;
    pin4 = 13;
  }

  if(pin3 == 45&& pin4 ==45){
    pin3 = 13;
    pin4 = 45;
  }

  if(pin3 == 12&& pin4 ==12){
    pin3 = 13;
    pin4 = 11;
  }

  if(pin3==10 && pin4==10){
    pin3 = 45;
    pin4 = 9;
  }

  if(pin3==8 && pin4==8){
    pin3 = 9;
    pin4 = 7;
  }

  if(pin3==6 && pin4==6){
    pin3 = 7;
    pin4 = 5;
  }
  if(pin3==4 && pin4==4){ 
    pin3 = 5;
    pin4 = 3;
  }
  if(pin3==3 && pin4==3){
    pin3 = 3;
    pin4 = 5;
  }
  if(pin5 == 46&& pin6 ==46){
    pin5 = 45;
    pin6 = 13;
  }

  if(pin5 == 45&& pin6 ==45){
    pin5 = 13;
    pin6 = 45;
  }

  if(pin5 == 12&& pin6 ==12){
    pin5 = 13;
    pin6 = 11;
  }

  if(pin5==10 && pin6==10){
    pin5 = 45;
    pin6 = 9;
  }

  if(pin5==8 && pin6==8){
    pin5 = 9;
    pin6 = 7;
  }

  if(pin5==6 && pin6==6){
    pin5 = 7;
    pin6 = 5;
  }
  if(pin5==4 && pin6==4){ 
    pin5 = 5;
    pin6 = 3;
  }
  if(pin5==3 && pin6==3){
    pin5 = 3;
    pin6 = 5;
  }
  if(pin7 == 46&& pin8 ==46){
    pin7 = 45;
    pin8 = 13;
  }

  if(pin7 == 45&& pin8 ==45){
    pin7 = 13;
    pin8 = 45;
  }

  if(pin7 == 12&& pin8 ==12){
    pin7 = 13;
    pin8 = 11;
  }

  if(pin7==10 && pin8==10){
    pin7 = 45;
    pin8 = 9;
  }

  if(pin7==8 && pin8==8){
    pin7 = 9;
    pin8 = 7;
  }

  if(pin7==6 && pin8==6){
    pin7 = 7;
    pin8 = 5;
  }
  if(pin7==4 && pin8==4){ 
    pin7 = 5;
    pin8 = 3;
  }
  if(pin7==3 && pin8==3){
    pin7 = 3;
    pin8 = 5;
  }
  if(pin9 == 46&& pin10 ==46){
    pin9 = 45;
    pin10 = 13;
  }

  if(pin9 == 45&& pin10 ==45){
    pin9 = 13;
    pin10 = 45;
  }

  if(pin9 == 12&& pin10 ==12){
    pin9 = 13;
    pin10 = 11;
  }

  if(pin9==10 && pin10==10){
    pin9 = 45;
    pin10 = 9;
  }

  if(pin9==8 && pin10==8){
    pin9 = 9;
    pin10 = 7;
  }

  if(pin9==6 && pin10==6){
    pin9 = 7;
    pin10 = 5;
  }
  if(pin9==4 && pin10==4){ 
    pin9 = 5;
    pin10 = 3;
  }
  if(pin9==3 && pin10==3){
    pin9 = 3;
    pin10 = 5;
  }
  int j,k,l,m = 0;
 for(int i =0; i<bright*250; i++){  

     
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  
   analogWrite(pin1,(bright*250));
   analogWrite(pin2, i);


  delay(FLICKER);
   pinMode(pin1, INPUT);
   pinMode(pin2, INPUT);
 
 
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  
    analogWrite(pin3,(bright*250));
    if(j>=bright*250){
      j=250;
    }
     analogWrite(pin4, j);
     if (j<=bright*250){
     j=j+rate2; }
       delay(FLICKER);
   pinMode(pin3, INPUT);
 pinMode(pin4, INPUT);
  
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  
 analogWrite(pin5,(bright*250));
 if(k>=bright*250){
      k=250;
    }
  analogWrite(pin6, k);
       if (k<bright*250){

  k=k+rate3;
       }
  delay(FLICKER);
 pinMode(pin5, INPUT);
 pinMode(pin6, INPUT);


  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  
   analogWrite(pin7,(bright*250));
   if(l>=bright*250){
      l=250;
    }
       analogWrite(pin8, l);
            if (j<bright*250){

      l=l+rate4; 
            }
       delay(FLICKER);
   pinMode(pin7, INPUT);
 pinMode(pin8, INPUT);
  
  pinMode(pin9, OUTPUT);
  pinMode(pin10, OUTPUT);

  analogWrite(pin9,(bright*250));
  if(m>=bright*250){
     m=250;
    }
  analogWrite(pin10, m);
       if (m<=bright*250){
            m=m+rate5;
       }
        delay(FLICKER);
      
 pinMode(pin9, INPUT);
 pinMode(pin10, INPUT);

   }
                  
                  
                  
                  
                  
                  



 
 

    
}
void writeCell(int pina, int pinb, int pinc, int pind){
for(int i =0; i<10000; i++){
  bitWord(pina,pinb);
  bitWord(pinc,pind);
}
lightSingle(9,pinb);
lightSingle(9,pind);
fadeLeds(pina,pinb, 10, 100, 1 );
fadeLeds(pinc,pind, 10, 100, 1 );

}
void writeMultiCell(int pin1,int pin2,int pin3,int pin4,int pin5,int pin6,int pin7,int pin8,int pin9, int pin10){
  for(int i =0; i<1000; i++){
      bitWord(pin1,pin2);
      bitWord(pin3,pin4);
      bitWord(pin5,pin6);
      bitWord(pin7,pin8);
      bitWord(pin9,pin10);
  }
 lightSingle(9,pin2);
lightSingle(9,pin4);
 lightSingle(9,pin6);
lightSingle(9,pin8);
lightSingle(9,pin10);

  lightMult(1,pin1,pin2, 1, pin3,pin4, 2, pin5,pin6,3, pin7,pin8 ,4, pin9,pin10,5);
}


//void loop(){










