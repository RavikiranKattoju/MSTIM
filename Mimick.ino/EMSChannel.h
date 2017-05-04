
#ifndef EMSCHANNEL_H_
#define EMSCHANNEL_H_

#include <Arduino.h>
#include "Wire.h"
#include "AD5252.h"

// Individual for each device must be knew
#define IDENT_PHRASE = "EMS-Service-BLE1"

//The Poti has 256 steps. 0 - 255.
#define POTI_STEPS_UP 255
#define POTI_STEPS_DOWN 0


class EMSChannel {

public:
	static void start();

	EMSChannel(uint8_t channel_to_Pads, uint8_t channel_to_Pads_2,
			uint8_t led_active_pin, AD5252 *digitalPoti, uint8_t wiperIndex);
	virtual ~EMSChannel();

	virtual void activate();
	virtual void deactivate();
	virtual bool isActivated();

	virtual void setIntensity(int intensity);
	virtual int getIntensity();

	virtual void setSignalLength(int signalLength);
	virtual int getSignalLength();

	virtual void applySignal();

	virtual void setMaxIntensity(int maxIntensity);
	virtual void setMinIntensity(int minIntensity);

	virtual int check();

private:
	//internal state
	bool activated;
	int intensity;
	unsigned long int endTime;
	int onTimeChannel;

	int maxIntensity; // Poti Value
	int minIntensity; // Poti Value

	//Poti control variables
	AD5252* digitalPoti;
	int wiperIndex;

	//Pin connections to Solid State Relays and LED
	uint8_t channel_to_Pads;
	uint8_t channel_to_Pads_2;
	uint8_t led_active_pin;

};

#endif /* EMSCHANNEL_H_ */

