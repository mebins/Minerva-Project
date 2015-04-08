/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  Minerva Vapoizers Proto
  8-APRIL-2015
  Version 002
  Prototype Code to test digital potentiometer, voltmeter, and LCD.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//-------------------------------DECLERATIONS---------------------------------------------------------------------------------------------------------------------------------------------------
#define BUTTONPLUS 2 //when clicked will increase the pwm by set number
#define BUTTONMINUS 8// when clicked will decrease the pwm by set number
#define LED 3 //led in pin 3 
#define FIRE 12 //Fire Button in pin 12
bool stateplus; //holds current plus button state
bool stateminus; //holds current minus button state
bool oldstateplus; //holds previous plus button state
bool oldstateminus;//holds previous minus button state
bool firebutton;
int DUTYCYCLE = 100; //pwm speed out of 255
int dpwm = 10;//delta pwm per click
float DUTYCYCLEPERCENTAGE;//Returns 0 to 100 of Dutycycle
int mode = 0;


void setup()
{
  Serial.begin(9600); //sends information to the serial monitor
  pinMode(BUTTONPLUS, INPUT_PULLUP); //intiates pin as a input function and also activates the resistor
  pinMode(BUTTONMINUS, INPUT_PULLUP);//intiates pin as a input function and also activates the resistor
  pinMode(FIRE, INPUT_PULLUP);//intiates pin as a input function and also activates the resistor
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
  
  Serial.print(DUTYCYCLEPERCENTAGE);
  Serial.println("%");
  Serial.print("Mode: ");
  Serial.println(mode);
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

  if (firebutton == LOW) // If the fire button is pressed then return to Normal Mode
  {
    mode = 0; //Normal Mode
  }

  if ( mode == 0 && stateplus == LOW && stateminus == LOW && oldstateplus == LOW && oldstateminus == LOW) //if on Normal Mode and if the change buttons are held change to Edit Mode
  {
    delay(200);
    if (mode == 0  && stateplus == LOW && stateminus == LOW && oldstateplus == LOW && oldstateminus == LOW) mode = 1; //Edit Mode
  }

  if (mode == 1) //if Edit Mode is on
  {
    if (stateplus == LOW && oldstateplus == LOW)
    {
      delay(100);
      if (stateplus == LOW && oldstateplus == LOW)
      {
        DUTYCYCLE += dpwm;
        if (DUTYCYCLE > 255)DUTYCYCLE = 255;
      }
    }
    if (stateminus == LOW && oldstateminus == LOW) //When the button 2 is pressed and last loop it wasn't, decrease the DUTY CYCLE BY dpwm
    {
      delay(100);
      if (stateminus == LOW && stateminus == LOW)
      {
        DUTYCYCLE -= dpwm;
        if (DUTYCYCLE < 0)DUTYCYCLE = 0; //DUTYCYCLE Cannot go below 0
      }
    }
  }
  DUTYCYCLEPERCENTAGE = ((DUTYCYCLE / 255.00) * 100.00);//Updates Percentage
  analogWrite(LED, DUTYCYCLE);
  oldstateplus = stateplus; //loop is ending and the oldstateplus holds the state of the button..
  oldstateminus = stateminus;//loop is ending and the oldstateminus holds the state of the button.
}
