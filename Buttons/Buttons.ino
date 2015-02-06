/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int but;
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  if (voltage>3)
  {
    but=0;
  }
  else if (voltage>-.1 && voltage<.1)
  {
    but=1;
  }
  else if (voltage>.3 && voltage<.6)
  {
    but=2;
  }
  else if (voltage>.8 && voltage<1.2)
  {
    but=3;    
  }
  else if (voltage>1.3 && voltage<1.7)
  {
    but=4;
  }
  else if (voltage>1.8 && voltage<2.2)
  {
    but=5;
  }
  else if (voltage>2.3 && voltage<2.7)
  {
    but=6;
  }
  //Serial.println(voltage);
  Serial.println(but);
}
