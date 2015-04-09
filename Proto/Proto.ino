/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  Minerva Vapoizers Proto
  9-APRIL-2015
  Version 005
  Prototype Code to test digital potentiometer, voltmeter, and LCD.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//-------------------------------DECLERATIONS---------------------------------------------------------------------------------------------------------------------------------------------------
#define MODE 2 //changes Mode when clicked
#define LCD 8
#define PV6 4
#define KNOB A0
#define CHIP 3 //led in pin 3 
#define FIRE 12 //Fire Button in pin 12
#define VOLTMETER A5
bool firebutton; //holds current firebutton state
bool modebutton; //holds current modeutton state
bool omodebutton;//holds previous modebutton state
float DUTYCYCLE = 0.00; //pwm speed out of 255
float dutycyclepercentage; //duty cycle value in percentage
int ledmode = 0; //NORMAL MODE = 0 ALWAYS ON = 1 ALWAYS OFF = 2
int lcdmode = 1;//ON = 1 ALWAYS ON = 2 ALWAYS OFF = 3
float r1= 560.00; // First Resistors Value
float r2= 560.00; // Second Resistors Value
float vIn = 10.00; // The Max Voltage that will go in
float vOut = (r1/(r1+r2))*vIn; // The Voltage out
float voltageRatio = vIn/vOut; // the voltage ratio compared to Vin with Vout
float voltageStep = 0.00488;// Voltage In divided by 1024
float voltageValue; 
int sleeptimer = 0; //counts how long the loop has been going on
void setup()
{
  Serial.begin(9600); //sends information to the serial monitor
  pinMode(MODE, INPUT_PULLUP); //intiates pin as a input and also activates the resistor
  pinMode(FIRE, INPUT_PULLUP);//intiates pin as a input and also activates the resistor
  pinMode(KNOB, INPUT);//intiates pin as a input
  pinMode(LCD, OUTPUT);//intiates pin as a output
  pinMode(PV6, OUTPUT);
}

void loop()
{
  currentChange(); //Changes pwm when appropriate
  returnChange();//Returns values of the Currentchange function
  lcdSleepDisplay();
  PVLED();
  batteryLife();
  Serial.println(sleeptimer);
  Serial.println(lcdmode);
  delay(50);

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------FUNCTIONS---------------------------------------------------------------------------------------------------------------------------------------------------


void batteryLife()
{
 voltageValue = analogRead(VOLTMETER)*voltageStep;
 float batteryVoltage = voltageValue*voltageRatio;
 //Serial.println(batteryVoltage);
 if(batteryVoltage <= 7)
 {
   Serial.print("BATTERY LIFE LOW: ");
   Serial.println(batteryVoltage);
 }
 else{ 
 Serial.println(batteryVoltage);
 Serial.print(((abs(batteryVoltage - 6.8))/1.6)*100); 
 Serial.println("%");
 }
}

void lcdSleepDisplay() //makes the lcd display automatically go to sleep after idle
{
  if (lcdmode == 1)digitalWrite(LCD, HIGH);//When on Mode 1 the LCD display turns on
  if (lcdmode == 0) digitalWrite(LCD, LOW); //When on Mode 0 the LCD display turns off
  sleeptimer++; //adds 1 to the sleep timer.
  if (sleeptimer >= 100)(lcdmode = 0); //when sleep timer is equal or greater than 100, the lcd mode = 0
  if (sleeptimer >= 1000)sleeptimer = 100;
}

void PVLED() //changes mode from illuminates when fire button clicked, Always on, Always off
{
  if (ledmode == 0 && firebutton == LOW)digitalWrite(PV6, HIGH); //when Firebutton is clicked ipv6 led turns on
  else digitalWrite(PV6, LOW); //when firebutton is not clicked PV6 led turns off

  if (ledmode == 1)digitalWrite(PV6, HIGH); //always on
  else if (ledmode == 2)digitalWrite(PV6, LOW); //always off
}

void sleepModeReset() //when used the lcd display turns on and the sleep timer goes to 0
{
  lcdmode = 1; //lcd display on
  sleeptimer = 0; //sleep timer set back to 0
}

void returnChange() //returns values to serial
{

  Serial.print(dutycyclepercentage); //pwm set at percentage
  Serial.println("%");
  Serial.print("Led Mode: ");
  Serial.println(ledmode);
  Serial.print("Lcd Mode: ");
  Serial.println(lcdmode);
}

void currentChange()
{
  /*
   Function that has the "intelligence" of the push button, and changes the
   pwm higher or lower depending on which button is clicked.
  */
  modebutton = digitalRead(MODE); //Stores the Current Button Value
  firebutton = digitalRead(FIRE);//Stores the Current Fire Button Value
  DUTYCYCLE = analogRead(A0) * (255.0 / 1023.0); // Converts Read Values from 0 to 255
  if (modebutton == LOW && omodebutton == HIGH) ledmode++; //when clicked the ledmode increases by 1
  if (ledmode > 2)ledmode = 0; // if ledmode value greater than 2 return to 0
  if (lcdmode > 3)ledmode = 1;
  if (firebutton == LOW) // If the fire button is pressed then return to Normal Mode
  {
    sleepModeReset(); //uses sleepmode reset function
    analogWrite(CHIP, DUTYCYCLE); //updates pwm on chip
  }
  else
  {
    analogWrite(CHIP, 0); //if firebutton is not pressed the pwm is set to 0;
  }

  dutycyclepercentage = (DUTYCYCLE / 255.00) * 100; //converts to percentage
  omodebutton = modebutton; //stores this loops values which will be compared to next loops
}
