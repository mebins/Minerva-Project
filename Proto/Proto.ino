/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  Minerva Vapoizers Proto
  8-APRIL-2015
  Version 003
  Prototype Code to test digital potentiometer, voltmeter, and LCD.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//-------------------------------DECLERATIONS---------------------------------------------------------------------------------------------------------------------------------------------------
#define BUTTONPLUS 2 //when clicked will increase the pwm by set number
#define BUTTONMINUS 8// when clicked will decrease the pwm by set number
#define KNOB A0
#define LED 3 //led in pin 3 
#define FIRE 12 //Fire Button in pin 12

bool stateplus; //holds current plus button state
bool stateminus; //holds current minus button state
bool oldstateplus; //holds previous plus button state
bool oldstateminus;//holds previous minus button state
bool firebutton;
float DUTYCYCLE = 0.00; //pwm speed out of 255
float dutycyclepercentage;
int ledmode = 0; //NORMAL MODE = 0 ALWAYS ON = 1 ALWAYS OFF = 2 

void setup()
{
  Serial.begin(9600); //sends information to the serial monitor
  pinMode(BUTTONPLUS, INPUT_PULLUP); //intiates pin as a input function and also activates the resistor
  pinMode(BUTTONMINUS, INPUT_PULLUP);//intiates pin as a input function and also activates the resistor
  pinMode(FIRE, INPUT_PULLUP);//intiates pin as a input function and also activates the resistor
  pinMode(KNOB, INPUT);
}

void loop()
{
  Currentchange(); //Changes pwm when appropriate
  ReturnChange();//Returns values of the Currentchange function
  
  delay(50);
  
}

/*=========================FUNCTIONS======================================================================================================================================================*/
void ReturnChange()
{

  Serial.print(DUTYCYCLE);
  Serial.println("%");
  Serial.print("Mode: ");
  Serial.println(ledmode);
}

void Currentchange()
{
  /*
   Function that has the "intelligence" of the push button, and changes the
   pwm higher or lower depending on which button is clicked.
  */
  stateplus = digitalRead(BUTTONPLUS); //Stores the Current Button Value
  stateminus = digitalRead(BUTTONMINUS);//Stores the Current Button Value
  firebutton = digitalRead(FIRE);//Stores the Current Fire Button Value
  DUTYCYCLE = analogRead(A0)*(255.0/1023.0);
  if (firebutton == LOW) // If the fire button is pressed then return to Normal Mode
  {
    ledmode = 0; //Normal Mode
    analogWrite(LED, DUTYCYCLE);
  }
  else analogWrite(LED,0);
  dutycyclepercentage = DUTYCYCLE / 255.00;
  oldstateplus = stateplus; //loop is ending and the oldstateplus holds the state of the button..
  oldstateminus = stateminus;//loop is ending and the oldstateminus holds the state of the button.
}
