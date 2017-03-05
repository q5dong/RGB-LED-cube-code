
/*This assigned pin is just for testing purpose, you can leave it here since 
this pin is does not conflict with any pin assigned below*/
const int ledPin = A0;

/*
 * Constant setting: 
 * digital input controlling each floor;
 * digital variable of grounds;

********I changed all those codes to comments, if you want to put the codes below
back to working, put the end of comment mark right after this line and you can see 
how it works.

***put the end of comment here***

const int TOP_FLOOR = A1; //Set top floor to pin 13
const int SECOND_FLOOR = A2; //Set the floor below top floor to pin 12
const int THIRD_FLOOR = A3; //Set the floor above the bottom floor to pin 11
const int BOTTOM_FLOOR = A4; //Set the bottom floor to pin 10

// center four
const int CENTER_RED = 12; // Assign red color of the center 4 leds to pin 9
const int CENTER_GREEN = 11; // Assign green...8
const int CENTER_BLUE = 10; // Assign blue...7

// Vertices
const int VERTICES_RED = 9;
const int VERTICES_GREEN = 8;
const int VERTICES_BLUE = 7;

// right: the leds one grid right to the corresponding vertices, same for the "left"
const int RIGHT_RED = 6;
const int RIGHT_GREEN = 5;
const int RIGHT_BLUE = 4;

// left: the leds one grid left to the corresponding vertices
const int LEFT_RED = 3;
const int LEFT_GREEN = 2;
const int LEFT_BLUE = 1;
/*finish setting constants*/

/*
 * Global setting: set global variables
 * 
 */

/*finish global setting*/

void setup() {
  // put your setup code here, to run once:

  /*Default of all pins are set to low, which means, all leds
  are by default off*/

  /*Here is the setting for testing code at pin A0*/
  pinMode(ledPin, OUTPUT); // sets the digital pin as output
  /*End of testing code*/

  /*Starting the "real" code for RGB led cube
  Assigning all of the pins to output so that these pins can
  be set high or low for voltages*/
  pinMode(TOP_FLOOR, OUTPUT);
  pinMode(SECOND_FLOOR, OUTPUT);
  pinMode(THIRD_FLOOR, OUTPUT);
  pinMode(BOTTOM_FLOOR, OUTPUT);


  pinMode(CENTER_RED, OUTPUT);
  pinMode(CENTER_GREEN, OUTPUT);
  pinMode(CENTER_BLUE, OUTPUT);

  
  pinMode(VERTICES_RED, OUTPUT);
  pinMode(VERTICES_GREEN, OUTPUT);
  pinMode(VERTICES_BLUE, OUTPUT);


  pinMode(RIGHT_RED, OUTPUT);
  pinMode(RIGHT_GREEN, OUTPUT);
  pinMode(RIGHT_BLUE, OUTPUT);


  pinMode(LEFT_RED, OUTPUT);
  pinMode(LEFT_GREEN, OUTPUT);
  pinMode(LEFT_BLUE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  /*The code here relates to the ledPin variable defined at the 
  beginning of all the code, for purely testing purposes; you can
  comment it out to test how the led cube works; to do that, just
  remove the comment mark after this sentence. */
  digitalWrite(ledPin, HIGH); // sets the LED on
  delay(1000); //waits for a second
  digitalWrite(ledPin, LOW); //sets the LED off
  delay(1000); //waits for a second
  /*End of testing codes*/
  
}
