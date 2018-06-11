/*******************************************************************************************************************
** Program to demonstrate the INA226 library for the Arduino IDE. A simple infinite loop of measurments will      **
** display the bus voltage and current running through the INA226.                                                **
**                                                                                                                **
** Detailed documentation can be found on the GitHub Wiki pages at https://github.com/SV-Zanshin/INA226/wiki      **
**                                                                                                                **
** This example is for a INA226 set up to measure a 5-Volt load with a 0.1 Ohm resistor in place, this is the same**
** setup that can be found in the Adafruit INA219 breakout board.  The complex calibration options are done at    **
** runtime using the 2 parameters specified in the "begin()" call and the library has gone to great lengths to    **
** avoid the use of floating point to conserve space and minimize runtime.  This demo program uses floating point **
** only to convert and display the data conveniently. The INA226 uses 15 bits of precision, and even though the   **
** current and watt information is returned using 32-bit integers the precision remains the same.                 **
**                                                                                                                **
** As of version 1.0.3 the library supports multiple INA226 devices.  The Atmel's EEPROM is used to store the 96  **
** bytes of static information per device using https://www.arduino.cc/en/Reference/EEPROM function calls.        **
** Although up to 16 devices could theoretically be present on the I2C bus the actual limit is determined by the  **
** available EEPROM - ATmega328 UNO has 1024k so can support up to 10 devices but the ATmega168 only has 512 bytes**
** which limits it to supporting at most 5 INA226s.  The library has been modified to be backwards compatible and **
** the device number (from 0 to number of devices found) is passed as the last parameter.                         **
**                                                                                                                **
** The datasheet for the INA226 can be found at http://www.ti.com/lit/ds/symlink/ina226.pdf and it contains the   **
** information required in order to hook up the device. Unfortunately it comes as a VSSOP package but it can be   **
** soldered onto a breakout board for breadboard use. The INA226 is quite similar to the INA219 mentioned above,  **
** but it can take bus voltages of up to 36V (which I needed in order to monitor a 24V battery system which goes  **
** above 28V while charging and which is above the absolute limits of the INA219). It is also significantly more  **
** accurate than the INA219.                                                                                      **
**                                                                                                                **
** This program is free software: you can redistribute it and/or modify it under the terms of the GNU General     **
** Public License as published by the Free Software Foundation, either version 3 of the License, or (at your      **
** option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY     **
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   **
** GNU General Public License for more details. You should have received a copy of the GNU General Public License **
** along with this program.  If not, see <http://www.gnu.org/licenses/>.                                          **
**                                                                                                                **
** Vers.  Date       Developer                     Comments                                                       **
** ====== ========== ============================= ============================================================== **
** 1.0.5  2018-06-08 https://github.com/SV-Zanshin removed unneeded prototype definitions                         **
** 1.0.4  2018-06-01 https://github.com/SV-Zanshin https://github.com/SV-Zanshin/INA226/issues/11 Corrected loop  **
** 1.0.3  2017-09-18 https://github.com/SV-Zanshin https://github.com/SV-Zanshin/INA226/issues/6 Multiple INA226s **
** 1.0.2  2017-08-09 https://github.com/SV-Zanshin Cosmetic changes                                               **
** 1.0.1  2017-01-12 https://github.com/SV-Zanshin Minor code cleanup and added more comments                     **
** 1.0.0  2017-01-09 https://github.com/SV-Zanshin Cloned example from test program suite                         **
**                                                                                                                **
*******************************************************************************************************************/
#include <INA226.h>                                                           // INA226 Library                   //
/*******************************************************************************************************************
** Declare program Constants                                                                                      **
*******************************************************************************************************************/
const uint32_t SERIAL_SPEED          = 115200;                                // Use fast serial speed            //
/*******************************************************************************************************************
** Declare global variables and instantiate classes                                                               **
*******************************************************************************************************************/
INA226_Class INA226;                                                          // INA class instantiation          //
uint8_t devicesFound = 0;                                                     // Number of INA226s found          //
/*******************************************************************************************************************
** Method Setup(). This is an Arduino IDE method which is called first upon initial boot or restart. It is only   **
** called one time and all of the variables and other initialization calls are done here prior to entering the    **
** main loop for data measurement and storage.                                                                    **
*******************************************************************************************************************/
void setup() {                                                                //                                  //
  Serial.begin(SERIAL_SPEED);                                                 // Start serial communications      //
  #ifdef  __AVR_ATmega32U4__                                                  // If we are a 32U4 processor, then //
    delay(2000);                                                              // wait 2 seconds for the serial    //
  #endif                                                                      // interface to initialize          //
  Serial.print(F("\n\nDisplay INA226 Readings V1.0.5\n"));                    // Display program information      //
  Serial.print(F(" - Searching & Initializing INA226\n"));                    // Display program information      //
  // The begin initializes the calibration for an expected ±1 Amps maximum current and for a 0.1Ohm resistor, and //
  // since no specific device is given as the 3rd parameter all devices are initially set to these values         //
  devicesFound = INA226.begin(1,100000);                                      // Set expected Amps and resistor   //
  Serial.print(F(" - Detected "));                                            //                                  //
  Serial.print(devicesFound);                                                 //                                  //
  Serial.println(F(" INA226 devices on I2C bus"));                            //                                  //
  INA226.setAveraging(4);                                                     // Average each reading n-times     //
  INA226.setBusConversion(7);                                                 // Maximum conversion time 8.244ms  //
  INA226.setShuntConversion(7);                                               // Maximum conversion time 8.244ms  //
  INA226.setMode(INA_MODE_CONTINUOUS_BOTH);                                   // Bus/shunt measured continuously  //
} // of method setup()                                                        //                                  //
/*******************************************************************************************************************
** This is the main program for the Arduino IDE, it is called in an infinite loop. The INA226 measurements are    **
** run in a simple infinite loop                                                                                  **
*******************************************************************************************************************/
void loop() {                                                                 // Main program loop                //
  static uint16_t loopCounter = 0;                                            // Count the number of iterations   //
  for (uint8_t i=0;i<devicesFound;i++) {                                      // Loop through all devices found   //
    Serial.print(F("Bus voltage   "));                                        //                                  //
    Serial.print(i+1);                                                        //                                  //
    Serial.print(F(": "));                                                    //                                  //
    Serial.print((float)INA226.getBusMilliVolts(true,i)/1000.0,4);            // Convert to millivolts            //
    Serial.print(F("V\nShunt voltage "));                                     //                                  //
    Serial.print(i+1);                                                        //                                  //
    Serial.print(F(": "));                                                    //                                  //
    Serial.print((float)INA226.getShuntMicroVolts(true,i)/1000.0,3);          // Convert to millivolts            //
    Serial.print(F("mV\nBus amperage  "));                                    //                                  //
    Serial.print(i+1);                                                        //                                  //
    Serial.print(F(": "));                                                    //                                  //
    Serial.print((float)INA226.getBusMicroAmps(i)/1000.0,4);                  // Convert to milliamp              //
    Serial.print(F("mA\nBus wattage   "));                                    //                                  //
    Serial.print(i+1);                                                        //                                  //
    Serial.print(F(":  "));                                                   //                                  //
    Serial.print((float)INA226.getBusMicroWatts(i)/1000.0,4);                 // Convert to milliwatts            //
    Serial.print(F("mW\n\n"));                                                //                                  //
  } // of for-next each device loop                                           //                                  //
  delay(5000);                                                                // Wait 5 seconds for next reading  //
  Serial.print(F("Loop iteration ")  );                                       //                                  //
  Serial.print(++loopCounter);                                                //                                  //
  Serial.print(F("\n\n")  );                                                  //                                  //
} // of method loop                                                           //----------------------------------//
