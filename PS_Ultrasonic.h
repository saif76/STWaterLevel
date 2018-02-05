//******************************************************************************************
//  File: PS_Ultrasonic.h
//  Authors: 
//
//  Summary:  PS_Ultrasonic is a class which implements the SmartThings "Illuminance Measurement" device capability.
//			  It inherits from the st::PollingSensor class.  The current version uses an analog input to measure the 
//			  value of a simple photo resistor.
//
//			  The last four arguments of the constructor are used as arguments to an Arduino map() function which 
//			  is used to scale the analog input readings (0 to 1024) to Lux before sending to SmartThings.  The
//			  defaults for this sensor are based on the device used during testing.  
//
//			  Create an instance of this class in your sketch's global variable section
//			  For Example:  st::PS_Ultrasonic sensor1("ultrasonic", 120, 0, PIN_ULTRASONIC_T, PIN_ULTRASONIC_T);
//
//			  st::PS_Ultrasonic() constructor requires the following arguments
//				- String &name - REQUIRED - the name of the object - must match the Groovy ST_Anything DeviceType tile name
//				- long interval - REQUIRED - the polling interval in seconds
//				- long offset - REQUIRED - the polling interval offset in seconds - used to prevent all polling sensors from executing at the same time
//				- byte digitalTriggerPin - REQUIRED - the Arduino Pin to be used as a digital output to trigger ultrasonic
//				- byte digitalEchoPin - REQUIRED - the Arduino Pin to be used as a digital input to read the echo
//
//			  This class supports receiving configuration data from the SmartThings cloud via the ST App.  A user preference
//			  can be configured in your phone's ST App, and then the "Configure" tile will send the data for all sensors to 
//			  the ST Shield.  For PollingSensors, this data is handled in the beSMart() function.
//
//			  TODO:  Determine a method to persist the ST Cloud's Polling Interval data
//
//  Change History:
//
//    Date        Who            What
//    ----        ---            ----
//    
//
//
//******************************************************************************************

#ifndef ST_PS_Ultrasonic_H
#define ST_PS_Ultrasonic_H

#include "PollingSensor.h"
#include "MomentaryRelay.h"

namespace st
{
	class PS_Ultrasonic : public PollingSensor
	{
		private:
			byte m_nDigitalTriggerPin;
			byte m_nDigitalEchoPin;
			float m_nSensorValue;
			MomentaryRelay MR1;
			MomentaryRelay MR2;
			
		public:
			//constructor - called in your sketch's global variable declaration section
			PS_Ultrasonic(const __FlashStringHelper *name, unsigned int interval, int offset, byte digitalTriggerPin, byte digitalEchoPin);
			
			//destructor
			virtual ~PS_Ultrasonic();
			
			//SmartThings Shield data handler (receives configuration data from ST - polling interval, and adjusts on the fly)
			virtual void beSmart(const String &str);

			//function to get data from sensor and queue results for transfer to ST Cloud 
			virtual void getData();
			
			//gets
			//inline byte getPin() const {return m_nAnalogInputPin;}
			inline byte getSensorValue() const {return m_nSensorValue;}
				
			//sets
			void setPin(byte &trigPin,byte &echoPin);
	};
}
#endif
