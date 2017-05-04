
#include <Arduino.h>
#include "Wire.h"

#ifndef AD5252_AD5252_H_
#define AD5252_AD5252_H_

class AD5252 {
public:
	AD5252(uint8_t address);
	virtual ~AD5252();
	void setPosition(uint8_t wiperIndex, uint8_t whiperPosition);
	void setPosition_sync(uint8_t wiperIndex1,uint8_t wiperIndex2, uint8_t whiperPosition);
  
	uint8_t getPosition(uint8_t wiperIndex);

	void decrement(uint8_t wiperIndex);
	void increment(uint8_t wiperIndex);

	void increment(uint8_t wiperIndex, int steps, int stepDelay);
	void decrement(uint8_t wiperIndex, int steps, int stepDelay);

private:
	static const uint8_t poti_manufactur_address = B0101100;
	uint8_t address;

};

#endif /* AD5252_AD5252_H_ */

