
int randEnd; //random setting

int on_1;
int on_2; //this is for random setting HIGH or LOW for the voltage layers
int on_3;
int on_4; 

int ground_1; //same for ground
int ground_2;
int ground_3;
int ground_4;
int ground_5;
int ground_6;
int ground_7;
int ground_8;
int ground_9;
int ground_10;
int ground_11;
int ground_12;

int xPin = A1; //Joystick Pins for inputs
int yPin = A0;


int buttonPin = 0;

int Layer_1 = A2; //Voltage Layers for the cathode parts. We'll use analog so we can reserve digital ports for grounds
int Layer_2 = A3;
int Layer_3 = A4;
int Layer_4 = A5;

int Bpin_1 = 2; //ground for pattern 1: middle square
int Gpin_1 = 3;
int Rpin_1 = 4;

int Bpin_2 = 5; //ground for pattern 2: diamond 1
int Gpin_2 = 6;
int Rpin_2 = 7;
              
int Bpin_3 = 8; //ground for pattern 2: diamond 2
int Gpin_3 = 9;
int Rpin_3 = 10;

int Bpin_4 = 11; //ground for pattern 2: diamond 2
int Gpin_4 = 12;
int Rpin_4 = 13;


int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 

  //Pins for the Joystick
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  //Pinmodes for Cube Layers and Grounds
  pinMode(Layer_1, OUTPUT);
  pinMode(Layer_2, OUTPUT);
  pinMode(Layer_3, OUTPUT);
  pinMode(Layer_4, OUTPUT);
  
  pinMode(Bpin_1, OUTPUT);
  pinMode(Gpin_1, OUTPUT);
  pinMode(Rpin_1, OUTPUT);

  
  pinMode(Bpin_2, OUTPUT);
  pinMode(Gpin_2, OUTPUT);
  pinMode(Rpin_2, OUTPUT);
  
  pinMode(Bpin_3, OUTPUT);
  pinMode(Gpin_3, OUTPUT);
  pinMode(Rpin_3, OUTPUT);
  
  pinMode(Bpin_4, OUTPUT);
  pinMode(Gpin_4, OUTPUT);
  pinMode(Rpin_4, OUTPUT);

  //activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP); 
  
  // For versions prior to Arduino 1.0.1
  // pinMode(buttonPin, INPUT);
  // digitalWrite(buttonPin, HIGH);
  
}

void loop() {
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  buttonState = digitalRead(buttonPin);
  
  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(buttonState);

  delay(100); // add some delay between reads

  if(xPosition > 1000) //Pattern for::::
  {
  }
  if(xPosition < 400) //Pattern for::::;
  {
  }
  if(yPosition < 400) // Pattern for:::
  {
  }
  if(yPosition > 1000) // Pattern for:::
  {
  }

  if(buttonState < 1) //Pattern for random flickerings. Will end with a random result
  {
    while(randEnd < 50)
    {
      on_1 = random(1,100);if(on_1 <50){on_1 = 200;} else {on_1 = 0;} //randomizes which Voltage layer will be on
      on_2 = random(1,100);if(on_2 <50){on_1 = 200;} else {on_2 = 0;}
      on_3 = random(1,100);if(on_3 <50){on_3 = 200;} else {on_3 = 0;}
      on_4 = random(1,100);if(on_4 <50){on_4 = 200;} else {on_4 = 0;}
      
      ground_1 = random(1,10) ; if(ground_1 < 3){ground_1 = HIGH;} else {ground_1 = LOW;}
      ground_2 = random(1,10) ; if(ground_2 < 6){ground_2 = HIGH;} else {ground_2 = LOW;}
      ground_3 = random(1,10) ; if(ground_3 < 4){ground_3 = HIGH;} else {ground_3 = LOW;}
      ground_4 = random(1,10) ; if(ground_4 < 9){ground_4 = HIGH;} else {ground_4 = LOW;}
      ground_5 = random(1,10) ; if(ground_5 < 5){ground_5 = HIGH;} else {ground_5 = LOW;}
      ground_6 = random(1,10) ; if(ground_6 < 6){ground_6 = HIGH;} else {ground_6 = LOW;}
      ground_7 = random(1,10) ; if(ground_7 < 7){ground_7 = HIGH;} else {ground_7 = LOW;}
      ground_8 = random(1,10) ; if(ground_8 < 4){ground_8 = HIGH;} else {ground_8 = LOW;}
      ground_9 = random(1,10) ; if(ground_9 < 4){ground_9 = HIGH;} else {ground_9 = LOW;}
      ground_10 = random(1,10) ; if(ground_10 < 4){ground_10 = HIGH;} else {ground_10 = LOW;}
      ground_11 = random(1,10) ; if(ground_11 < 4){ground_11 = HIGH;} else {ground_11 = LOW;}
      ground_12 = random(1,10) ; if(ground_12 < 4){ground_12 = HIGH;} else {ground_12 = LOW;}
    analogWrite(Layer_1, on_1); delay(5);
    analogWrite(Layer_2, on_2); delay(5);
    analogWrite(Layer_3, on_3); delay(5);
    analogWrite(Layer_4, on_4); delay(5);
    digitalWrite(Bpin_1, ground_1);delay(5);
    digitalWrite(Bpin_2, ground_2);delay(5);
    digitalWrite(Bpin_3, ground_3);delay(5);
    digitalWrite(Bpin_4, ground_4);delay(5);
    digitalWrite(Gpin_1, ground_5);delay(5);
    digitalWrite(Gpin_2, ground_6);delay(5);
    digitalWrite(Gpin_3, ground_7);delay(5);
    digitalWrite(Gpin_4, ground_8);delay(5);
    digitalWrite(Rpin_1, ground_9);delay(5);
    digitalWrite(Rpin_2, ground_10);delay(5);
    digitalWrite(Rpin_3, ground_11);delay(5);
    digitalWrite(Rpin_4, ground_12);delay(5);
    randEnd = random(1,53);
    }
    randEnd = 0;
    delay (2000);
    analogWrite(Layer_1, 0);
    analogWrite(Layer_2, 0);
    analogWrite(Layer_3, 0);
    analogWrite(Layer_4, 0);
  }


}
