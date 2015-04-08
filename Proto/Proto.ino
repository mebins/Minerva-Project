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
  pinMode(BUTTONMINUS, INPUT_PULLUP);//intiates pin as a input function and also activates the resistor
}

void loop()
{
  Currentchange(); //Changes pwm when appropriate
  ReturnChange();//Returns values of the Currentchange function
  delay(50);
}


/*=====================================================================
====================FUNCTIONS=====================================*/
void ReturnChange()
{
  Serial.println(stateplus); //returns the state of button 1
  Serial.println(stateminus); //returns the state of button 2
  Serial.println(DUTYCYCLE); //returns the rate of PWM(0,255)
}

void Currentchange()
{
  /*
   Function that has the "intelligence" of the push button, and changes the
   pwm higher or lower depending on which button is clicked.
  */
  stateplus = digitalRead(BUTTONPLUS); //Stores the Current Button Value
  stateminus = digitalRead(BUTTONMINUS);//Stores the Current Button Value
  if (stateplus == LOW && oldstateplus == HIGH)//When the button 1 is pressed and last loop it wasn't, increase the DUTY CYCLE BY dpwm
  {
    DUTYCYCLE += dpwm;
    if (DUTYCYCLE > 255)
    {
      DUTYCYCLE = 255; //DUTYCYCLE cannot go higher then 255
    }
  }
  if (stateminus == LOW && oldstateminus == HIGH) //When the button 2 is pressed and last loop it wasn't, decrease the DUTY CYCLE BY dpwm
  {
    DUTYCYCLE -= dpwm;
    if (DUTYCYCLE < 0)
    {
      DUTYCYCLE = 0; //DUTYCYCLE Cannot go below 0
    }

  }
  analogWrite(LED, DUTYCYCLE);
  oldstateplus = stateplus; //loop is ending and the oldstateplus holds the state of the button..
  oldstateminus = stateminus;//loop is ending and the oldstateminus holds the state of the button.
}
