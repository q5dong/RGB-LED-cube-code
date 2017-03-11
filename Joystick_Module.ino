int xPin = A1;  //Joystick Pins for inputs
int yPin = A0;  
int buttonPin = 0;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

int Layer_1 = A2; //A2          //Voltage Layers for the cathode parts. We'll use analog so we can reserve digital ports for grounds
int Layer_2 = A3; //A3
int Layer_3 = A4; //A4
int Layer_4 = A5; //A5

int Bpin_1 = 2; //ground for pattern 1: middle square
int Gpin_1 = 3;
int Rpin_1 = 4;
int Bpin_2 = 5; //ground for pattern 2: diamond 1
int Gpin_2 = 6;
int Rpin_2 = 7;
int Bpin_3 = 8; //ground for pattern 2: diamond 2
int Gpin_3 = 9;
int Rpin_3 = 10;
int Bpin_4 = 11; //ground for pattern 2: Outer dots
int Gpin_4 = 12;
int Rpin_4 = 13;

/*Arrays for pins*/
int layers[4]; 
int positions[4][3]; // position & color
/**/


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  
  initializeArrays();
  
  //Pins for the Joystick
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  //Pinmodes for Cube Layers and Grounds
  pinMode(Layer_1, OUTPUT); pinMode(Layer_2, OUTPUT);  pinMode(Layer_3, OUTPUT);  pinMode(Layer_4, OUTPUT);
  
  pinMode(Bpin_1, OUTPUT);  pinMode(Gpin_1, OUTPUT);  pinMode(Rpin_1, OUTPUT);
  pinMode(Bpin_2, OUTPUT);  pinMode(Gpin_2, OUTPUT);  pinMode(Rpin_2, OUTPUT);
  pinMode(Bpin_3, OUTPUT);  pinMode(Gpin_3, OUTPUT);  pinMode(Rpin_3, OUTPUT); 
  pinMode(Bpin_4, OUTPUT);  pinMode(Gpin_4, OUTPUT);  pinMode(Rpin_4, OUTPUT);

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

  //initialize clear state og grounds. We do not want inconsistent patterns to be ruined
  digitalWrite(Bpin_1, HIGH);  digitalWrite(Gpin_1, HIGH); digitalWrite(Rpin_1, HIGH); 
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);

  if(xPosition > 1000) //Pattern for rotating shuriken
  {
 //Alex
   shuriken();
  }
  
  if(xPosition < 100) //Pattern for spiral
  {
    //JOLI
    for(int x = 0; x < 5; x++)
    {
    spin(0,1); delay(10);
    spin(1,1); delay(10);
    spin(0,0); delay(10);
    spin(1,0); delay(10);
    }
  }

  if(yPosition < 100) // Pattern for 
  {
   
  }

  if(yPosition > 1000) // Pattern for:::
  {
    
  }

  if(buttonState < 1) //Pattern for random flickerings. Will end with a random result
  {
     randomizer();
  }

}


/*My functions*/

// Initialize pin arrays
void initializeArrays(){
  layers[0] = Layer_1; //Top
  layers[1] = Layer_2;
  layers[2] = Layer_3;
  layers[3] = Layer_4;

  positions[0][0] = Rpin_1; // Center: 0, Red: 0
  positions[0][1] = Gpin_1; // Green: 1
  positions[0][2] = Bpin_1; // Blue: 2

  positions[1][0] = Rpin_2; // Right: 1
  positions[1][1] = Gpin_2;
  positions[1][2] = Bpin_2;

  positions[2][0] = Rpin_3; // Left: 2
  positions[2][1] = Gpin_3; 
  positions[2][2] = Bpin_3;

  positions[3][0] = Rpin_4; // Vertices: 3
  positions[3][1] = Gpin_4; 
  positions[3][2] = Bpin_4;
}

/* Turn all pins to low. */
void turnAllToLow(){

  /*Turn off layers*/
  for(int lyr = 0; lyr < 4; lyr++){
    analogWrite(layers[lyr], 200);
  }

  /*Turn off positions*/
  for(int num = 0; num < 4; num++) {
    for(int clr = 0; clr < 3; clr++){
      digitalWrite(positions[num][clr], LOW);
    }
  }
}


/*
 * layerIdx: 0 as top
 * posIdx: Center: 0, Right: 1, Left: 2, Vertices 3
 * colorIdx: R: 0, G: 1, B: 2
 * two color options
 */
void turnSingleLayerSetOn(int layerIdx, int posIdx, int colorIdx1, int colorIdx2){
  /*
   * Set the specific layer HIGH, the chosen ground low, 
   * and rest of ground in that layer HIGH;
   * all other layers set to LOW.
   */
   turnAllToLow(); // First make sure all pins are low.

   analogWrite(layers[layerIdx], 200); // Set the layer input to HIGH

   // Set all other layers input to low
   for(int lI = 0; lI < 4; lI++) {
    if(lI != layerIdx){
      analogWrite(layers[lI], 0);
    }
   }
   digitalWrite(positions[posIdx][colorIdx1], LOW);
   digitalWrite(positions[posIdx][colorIdx2], LOW);
   for(int pI = 0; pI < 4; pI++){
    for(int cI = 0; cI < 3; cI++){
      if(!((pI == posIdx && cI == colorIdx1) || (pI == posIdx && cI == colorIdx2))){
        digitalWrite(positions[pI][cI], HIGH);
      }
    }
   }
}


/* Spin: swirling with changing colors
 * direc TRUE: upside down
 * FALSE: from bottom up
 * This only goes through once.
 */
void spin(boolean layerDir, boolean clockDir){
  int rdmColor = 0;
  
  /*First color is (generated number)/40 (range from 0 to 2), and second color is 
  ((generated number)&40)&10 (range from 0 to 9) */
  int firstColor;
  int secondColor;
  
  /*If statement for determining the final color*/
  int lyr; // layer index
  int realLyr; // real layer index
  int pos;
  for(lyr = 0; lyr < 4; lyr++){
    rdmColor = random(0, 99);
    Serial.print(" random number =  ");
    Serial.print(rdmColor);
    pos = lyr;
      realLyr = lyr;
      if (!layerDir){ // bottom up
        realLyr = 3 - lyr;
      }
      if(!clockDir){
        pos = 3 - lyr; 
      }
      firstColor = rdmColor / 40; // Gererate random number
      secondColor = (rdmColor & 40) & 10;
      // fix the range of the second color
      secondColor = secondColor / 4;

      // this function is responsible for turning the last layer off
      turnSingleLayerSetOn(realLyr, pos, firstColor, secondColor);
      delay(100); // delay after turning on

      // turning this pattern off from the ground
      digitalWrite(positions[pos][firstColor], HIGH);
      digitalWrite(positions[pos][secondColor], HIGH);
  }
}


void shuriken()
{
  analogWrite(Layer_1, 200); analogWrite(Layer_2, 200); analogWrite(Layer_3, 200); analogWrite(Layer_4, 200);
  
  digitalWrite(Bpin_1, LOW);  digitalWrite(Gpin_1, LOW); digitalWrite(Rpin_1, LOW);  delay(1000);
  digitalWrite(Bpin_2, LOW);  digitalWrite(Gpin_2, LOW); digitalWrite(Rpin_2, LOW);  delay(1000);
  
  for(int i = 0; i < 7 ; i++)
  {
  analogWrite(Layer_1, 200); analogWrite(Layer_2, 0); analogWrite(Layer_3, 0); analogWrite(Layer_4, 0);

  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, LOW);  digitalWrite(Gpin_3, LOW); digitalWrite(Rpin_3, LOW);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, LOW);  digitalWrite(Gpin_4, LOW); digitalWrite(Rpin_4, LOW);
  delay(100);
  
  digitalWrite(Bpin_2, LOW);  digitalWrite(Gpin_2, LOW); digitalWrite(Rpin_2, LOW);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  }

  for(int i = 0; i < 7 ; i++)
  {
  analogWrite(Layer_1, 0); analogWrite(Layer_2, 200); analogWrite(Layer_3, 0); analogWrite(Layer_4, 0);
  
  digitalWrite(Bpin_1, LOW);  digitalWrite(Gpin_1, HIGH); digitalWrite(Rpin_1, LOW);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, LOW); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, LOW); digitalWrite(Rpin_4, HIGH);
  delay(100);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, LOW); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  }

  for(int i = 0; i < 7 ; i++)
  {
  analogWrite(Layer_1, 0); analogWrite(Layer_2, 0); analogWrite(Layer_3, 200); analogWrite(Layer_4, 0);
  
  digitalWrite(Bpin_1, HIGH);  digitalWrite(Gpin_1, LOW); digitalWrite(Rpin_1, LOW);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, LOW);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, LOW);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  
  digitalWrite(Bpin_2, LOW);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  }

  for(int i = 0; i < 7 ; i++)
  {
  analogWrite(Layer_1, 0); analogWrite(Layer_2, 0); analogWrite(Layer_3, 0); analogWrite(Layer_4, 200);
  
  digitalWrite(Bpin_1, LOW);  digitalWrite(Gpin_1, LOW); digitalWrite(Rpin_1, HIGH);

  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, LOW);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, LOW);
  delay(100);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, LOW);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  }

  for(int i = 0; i < 7; i++)
  {
  analogWrite(Layer_1, 0); analogWrite(Layer_2, 200); analogWrite(Layer_3, 200); analogWrite(Layer_4, 0);
  
  digitalWrite(Bpin_1, LOW);  digitalWrite(Gpin_1, HIGH); digitalWrite(Rpin_1, HIGH);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, LOW);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, LOW);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, LOW);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, LOW);
  delay(100);
  
  digitalWrite(Bpin_2, LOW);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, LOW);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  }
  for(int i = 0; i < 7; i++)
  {
  analogWrite(Layer_1, 200); analogWrite(Layer_2, 0); analogWrite(Layer_3, 0); analogWrite(Layer_4, 200);
  
  digitalWrite(Bpin_1, HIGH);  digitalWrite(Gpin_1, HIGH); digitalWrite(Rpin_1, LOW);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, LOW); digitalWrite(Rpin_3, LOW);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, LOW); digitalWrite(Rpin_4, LOW);
  delay(100);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, LOW); digitalWrite(Rpin_2, LOW);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  }
  for(int i = 0; i < 7; i++)
  {
  analogWrite(Layer_1, 200); analogWrite(Layer_2, 200); analogWrite(Layer_3, 200); analogWrite(Layer_4, 200);
  
  digitalWrite(Bpin_1, LOW);  digitalWrite(Gpin_1, LOW); digitalWrite(Rpin_1, LOW);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, LOW);  digitalWrite(Gpin_3, LOW); digitalWrite(Rpin_3, LOW);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  
  digitalWrite(Bpin_2, HIGH);  digitalWrite(Gpin_2, HIGH); digitalWrite(Rpin_2, HIGH);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, LOW);  digitalWrite(Gpin_4, LOW); digitalWrite(Rpin_4, LOW);
  delay(100);
  
  digitalWrite(Bpin_2, LOW);  digitalWrite(Gpin_2, LOW); digitalWrite(Rpin_2, LOW);
  digitalWrite(Bpin_3, HIGH);  digitalWrite(Gpin_3, HIGH); digitalWrite(Rpin_3, HIGH);
  digitalWrite(Bpin_4, HIGH);  digitalWrite(Gpin_4, HIGH); digitalWrite(Rpin_4, HIGH);
  delay(100);
  }
  delay(1000);
}

void randomizer()
{
int randEnd; //random setting

int on_1; int on_2;  int on_3;  int on_4; 

int ground_1; int ground_2;   int ground_3;   int ground_4;
int ground_5; int ground_6;   int ground_7;   int ground_8;
int ground_9; int ground_10;  int ground_11;  int ground_12;

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
    randEnd = random(1,52);
    }
    randEnd = 0;
    delay (2000);
    analogWrite(Layer_1, 0);
    analogWrite(Layer_2, 0);
    analogWrite(Layer_3, 0);
    analogWrite(Layer_4, 0);
  }
