/*******************************************************************************************************************
** Program to demonstrate the INA226 library for the Arduino IDE. A simple infinite loop of measurments will      **
** display the bus voltage and current running through the INA226                                                 **
** devices                                                                                                        **
**                                                                                                                **
** Vers.   Date       Developer           Comments                                                                **
** ======= ========== =================== ======================================================================= **
** 1.0.0   2017-01-09 Arnd@SV-Zanshin.Com Cloned example from test program suite                                  **
**                                                                                                                **
*******************************************************************************************************************/
#include <INA.h>                                                              // INA Library                      //

/*******************************************************************************************************************
** Declare program Constants                                                                                      **
*******************************************************************************************************************/
const uint8_t  GREEN_LED_PIN         =     13;                                // Green LED (nonstandard location) //
const uint32_t SERIAL_SPEED          = 115200;                                // Use fast serial speed            //
/*******************************************************************************************************************
** Declare global variables and instantiate classes                                                               **
*******************************************************************************************************************/
INA226_Class      INA226;                                                     // INA class instantiation          //
/*******************************************************************************************************************
** Declare prototypes for all functions used                                                                      **
*******************************************************************************************************************/
void    setup();                                                              // Called once on power-up/restart  //
void    loop();                                                               // Called repeatedly after setup()  //

/*******************************************************************************************************************
** Method Setup(). This is an Arduino IDE method which is called first upon initial boot or restart. It is only   **
** called one time and all of the variables and other initialization calls are done here prior to entering the    **
** main loop for data measurement and storage.                                                                    **
*******************************************************************************************************************/
void setup() {                                                                //                                  //
  pinMode(GREEN_LED_PIN, OUTPUT);                                             // Define the green LED as an output//
  digitalWrite(GREEN_LED_PIN,true);                                           // Turn on the LED                  //
  Serial.begin(SERIAL_SPEED);                                                 // Start serial communications      //
  delay(2000);                                                                // Wait for comms port to connect   //
  Serial.print(F("\n\nDisplay INA226 Readings V1.0.0\n"));                    // Display program information      //
  INA226.begin(     6,                                                        // Volts maximum expected on bus    //
                    1,                                                        // ± Amps maximum expected on bus   //
                  100,                                                        // ± Shunt millivolts maximum       //
               100000);                                                       // Shunt resistance in microOhm(µ?),//
                                                                              // "100000" equate to 0.1 Ohm       //
  INA226.setAveraging(4);                                                     // Average each reading n-times     //
  INA226.setBusConversion();                                                  // Maximum conversion time 8.244ms  //
  INA226.setShuntConversion();                                                // Maximum conversion time 8.244ms  //
  INA226.setMode(7);                                                          // Bus/shunt measured continuously  //
} // of method setup()                                                        //                                  //

/*******************************************************************************************************************
** This is the main program for the Arduino IDE, it is called in an infinite loop. The INA226 measurements are    **
** run in a simple infinite loop                                                                                  **
*******************************************************************************************************************/
void loop() {                                                                 // Main program loop                //
  Serial.print(F("Bus voltage:   "));
  Serial.print((float)INA226.getBusMilliVolts()/1000.0,4);
  Serial.println(F("V"));
  Serial.print(F("Shunt voltage: "));
  Serial.print((float)INA226.getShuntMicroVolts()/1000.0,3);
  Serial.println(F("mV"));
  Serial.print(F("Bus amperage:  "));
  Serial.print((float)INA226.getBusMicroAmps()/1000.0,3);
  Serial.println(F("mA"));
  Serial.print(F("Bus wattage:   "));
  Serial.print((float)INA226.getBusMicroWatts()/1000.0,3);
  Serial.println(F("mW"));
  Serial.println();
  delay(2000);
} // of method loop
