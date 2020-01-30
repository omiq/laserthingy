// you can change these vvvv


// Delay after taking one step
#define STEPDELAY 20

// When at a magnet it will count 
// up to this number before restarting
#define PAUSETICKS 100

// How many steps to get past the current magnet
#define STEPSPASTMAGNET 150

// you can change these ^^^^^




// Default stepper library
#include <Stepper.h>

// change this to fit the number of steps per revolution
// for your motor
#define NEXTHOLE 500 

// Motor pins
#define MOTOR1  3     // IN1 on the ULN2003 
#define MOTOR2  4     // IN2 on the ULN2003 
#define MOTOR3  5     // IN3 on the ULN2003 
#define MOTOR4  6     // IN4 on the ULN2003 

// Hall effect and LED pins
#define HALLSENSORPIN  A0     
#define LEDPIN          2

// Control pins
#define SLOW          A5
#define PAUSE         A4
#define FAST          A3

// Initial speed/pause delay is set to slow
int speed = 3;

// Status of the sensor (LOW is triggered)
int hallstate = HIGH;  
int halt = 0;  

// initialize the stepper library
Stepper myStepper(4096, MOTOR1, MOTOR3, MOTOR2, MOTOR4);


// On startup, run the motor until hall triggers
void setup() { 

  // Start serial for debugging
  Serial.begin(115200);

  // Set the pin modes
  pinMode(LEDPIN, OUTPUT);      
  pinMode(HALLSENSORPIN, INPUT);    
  pinMode(SLOW, INPUT);    
  pinMode(PAUSE, INPUT);    
  pinMode(FAST, INPUT);    

 
}

// Keep the motor running until power is off
// or pause is hit
// Speed is controlled by butons
void loop() {

  halt = 0;

  // while not paused ...
  while(speed > 0 && halt == 0) {

    // keep rotating until positioned at next hole
    
   
      // take a step if not paused
      myStepper.step(1);

      // check the buttons have been pressed
      checkButtons();
      
      // tiny delay
      delay(STEPDELAY);
    
    

   if(halt==1) 
   {
    // wait before continue
    // the pause is set by buttons
    for(int tick = 0; tick < PAUSETICKS * speed; tick++)
    {

      // check the buttons
      checkButtons();
     
      delay(10);
    }

// move past the magnet
   for(int step = 0; step < STEPSPASTMAGNET; step++)
    {

       // take a step if not paused
      if(speed > 0) myStepper.step(1);

       // check the buttons have been pressed
      checkButtons();

       // tiny delay
      delay(STEPDELAY);

     }}
  }

  // check the buttons
  checkButtons();
}

// Check for button presses
void checkButtons()
{


  if ( digitalRead(HALLSENSORPIN) == LOW ) halt = 1;
 
       

  // slower button
  if(digitalRead(SLOW) == LOW) 
  { 
    if(speed >= 1) speed--;
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);

  }

  // pause button
  if(digitalRead(PAUSE) == LOW) 
  {
    speed=0;
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);

  }

  // speed up button
  if(digitalRead(FAST) == LOW) 
  {
    if(speed <= 4) speed++;
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);

  }

  // output the current speed to serial monitor
  Serial.println(speed);
}
