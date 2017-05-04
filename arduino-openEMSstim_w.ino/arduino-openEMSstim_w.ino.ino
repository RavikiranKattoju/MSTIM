
// Necessary files ( AD5252.h, EMSSystem.h, EMSChannel.h) and dependencies (Wire.h, Arduino.h)

// TESTING COMMANDS
            //   For quick testing (e.g., opening the optocoupler ports, etc) you can use these single-char commands (one command = one char).
            //   The available commands are:
            //     "1": toggles the channel 1 between open/closed state (when the channel is closed, the potenciometer position is reset to minimum, i.e., 255)
            //     "2": toggles the channel 1 between open/closed state (when the channel is closed, the potenciometer position is reset to minimum, i.e., 255)
            //     "q": increases EMS signal on channel 1 by decreasing the digital potenciometer wiper position (i.e., resistance lowers and more EMS is passing)
            //           -> note that you have full EMS signal when the potentiometer wiper is at 0 (0 is the maximum) 
            //     "a": decreases EMS signal on channel 1 by increasing the digital potenciometer wiper position (i.e., resistance lowers and more EMS is passing)
            //           -> note that you have no EMS signal when the potentiometer wiper is at 255 (255 is the maximum resistance of the potentiometer) 
            //     "w": increases EMS signal on channel 2 by decreasing the digital potenciometer wiper position (i.e., resistance lowers and more EMS is passing)
            //           -> note that you have full EMS signal when the potentiometer wiper is at 0 (0 is the maximum) 
            //     "s": decreases EMS signal on channel 2 by increasing the digital potenciometer wiper position (i.e., resistance lowers and more EMS is passing)
            //           -> note that you have no EMS signal when the potentiometer wiper is at 255 (255 is the maximum resistance of the potentiometer)
// TESTING COMMANDS


#include "Arduino.h"
#include "Wire.h"
#include "AD5252.h"
#include "EMSSystem.h"
#include "EMSChannel.h"
#include "avr/pgmspace.h"

//DEBUG: setup for verbose mode (prints debug messages if DEBUG_ON is 1)
#define DEBUG_ON 1

//USB: allows to send simplified test commands (one char each, refer to https://github.com/PedroLopes/openEMSstim) to the board via USB (by default this is inactive)
#define USB_TEST_COMMANDS_ACTIVE 1

//Initialization of control objects

    AD5252 digitalPot(0);
    EMSChannel emsChannel1(5, 4, A2, &digitalPot, 1);
    EMSChannel emsChannel2(6, 7, A3, &digitalPot, 3);
    EMSSystem emsSystem(2);

void setup() 
{
    Serial.begin(19200);
    //Serial.setTimeout(75);
    Serial.flush();
              
    //Add the EMS channels and start the control    	
    emsSystem.addChannelToSystem(&emsChannel1);
    emsSystem.addChannelToSystem(&emsChannel2);
    EMSSystem::start();
    Serial.println("EMS System Start");
  
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void loop() 
{
    //Communicate to the EMS-module over USB
    if (Serial.available() > 0) 
    {
        if (USB_TEST_COMMANDS_ACTIVE) 
        {
            String message = Serial.readStringUntil('\n');
            doCommand(message);
    	  }
        Serial.flush(); 
	  }
}

void doCommand(String str) 
{
    char c = str[0];
    if (c == '1') 
      {
      		if (emsChannel1.isActivated()) 
          		{
            			emsChannel1.deactivate();
                  Serial.println("Channel 1 DeActivated \t");
        		  } 
    		  else 
        		  {
          			  emsChannel1.activate();
                  Serial.println("EMS: Channel 1 active /t");
        		  }
  	  }
	  else if (c == '2') 
  	  {
    		  if (emsChannel2.isActivated()) 
        		  {
          			  emsChannel2.deactivate();
                  Serial.println("Channel 2 DeActivated \t");
              } 
    		  else 
        		  {
            			emsChannel2.activate();
                  Serial.println("Channel 2 Activated \t");
              }
  	  }   
	  else if (c == 'a') 
  	  {
      		digitalPot.setPosition(1, digitalPot.getPosition(1) + 1);
      		Serial.println( "\tEMS1:" + String(digitalPot.getPosition(1))); 
  	  }
	  else if (c == 'q') 
  	  {
          digitalPot.setPosition(1, digitalPot.getPosition(1) - 1);
          Serial.println("EMS1:"+String(digitalPot.getPosition(1)));
  	  }
  	else if (c == 's') 
    	{
  		    digitalPot.setPosition(3, digitalPot.getPosition(3) + 1);
          Serial.println( "\tEMS1:" + String(digitalPot.getPosition(3))); 
      } 
	  else if (c == 'w') 
    	{
    		  digitalPot.setPosition(3, digitalPot.getPosition(3) - 1);
          Serial.println( "\tEMS2:" + String(digitalPot.getPosition(3))); 
    	}
    else if (c == 'f') // Dual Channel Activation + Syncronus Intensity  
      {
          emsChannel1.activate();
          emsChannel2.activate();
          String temp = ""; // convert string to int
          for (int i=str.indexOf('q')+1; i<str.indexOf('e'); i++)
              {     
                   temp += (char)str[i];
              }
          digitalPot.setPosition(1, temp.toInt());
          digitalPot.setPosition(3, temp.toInt());
          Serial.println("EMS1:"+String(digitalPot.getPosition(1))+ "EMS2:"+String(digitalPot.getPosition(3)));
      }    
    else Serial.println("Error /t");    
}

