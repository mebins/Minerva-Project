

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  Minerva Vapoizers Proto
  29-March-2015
  Version 001
  Prototype Code to test digital potentiometer, voltmeter, and LCD.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//-------------------------------DECLERATIONS---------------------------------------------------------------------------------------------------------------------------------------------------
#define BUTTONPLUS 2 //when clicked will increase the pwm by set number
#define BUTTONMINUS 8// when clicked will decrease the pwm by set number
#define LED 3 //led in pin 3 
bool stateplus; //holds current plus button state
bool stateminus; //holds current minus button state
bool oldstateplus; //holds previous plus button state
bool oldstateminus;//holds previous minus button state
int DUTYCYCLE = 100; //pwm speed out of 255
int dpwm = 20;//delta pwm per click


void setup()
{
  Serial.begin(9600); //sends information to the serial monitor
  pinMode(BUTTONPLUS, INPUT_PULLUP); //intiates pin as a input function and also activates the resistor
  pinMode(BUTTONMINUS, INPUT_PULLUP);
}

void loop()
{
  Currentchange();
  Return();
  delay(50);
}


void Return()
{
  Serial.println(stateplus);
  Serial.println(stateminus);
  Serial.println(DUTYCYCLE);
}
void Currentchange()
{
  /*
   Function that has the "intelligence" of the push button, and changes the 
   pwm higher or lower depending on which button is clicked.
  */
  stateplus = digitalRead(BUTTONPLUS);
  stateminus = digitalRead(BUTTONMINUS);
  if (stateplus == LOW && oldstateplus == HIGH)
  {
    DUTYCYCLE += dpwm;
    if (DUTYCYCLE > 255)
    {
      DUTYCYCLE = 255;
    }
  }
  if (stateminus == LOW && oldstateminus == HIGH)
  {
    DUTYCYCLE -= dpwm;
    if (DUTYCYCLE < 0)
    {
      DUTYCYCLE = 0;
    }

  }
  analogWrite(LED, DUTYCYCLE);
  oldstateplus = stateplus;
  oldstateminus = stateminus;
}
