
#include "AD5252.h"

AD5252::AD5252(uint8_t address) {
	this->address = address;

}

AD5252::~AD5252() {
	// TODO Auto-generated destructor stub
}

//whiper index is 1 or 3
void AD5252::setPosition(uint8_t wiperIndex, uint8_t whiperPosition){
  Wire.beginTransmission(poti_manufactur_address);
  Wire.write(wiperIndex);
  Wire.write(whiperPosition);
  Wire.endTransmission(1);
}


void AD5252::setPosition_sync(uint8_t wiperIndex1,uint8_t wiperIndex2, uint8_t whiperPosition){
  Wire.beginTransmission(poti_manufactur_address);
  Wire.write(wiperIndex1);
  Wire.write(wiperIndex2);
  Wire.write(whiperPosition);
  Wire.endTransmission(1);
}

//whiper is 1 or 3
uint8_t AD5252::getPosition(uint8_t wiperIndex){
  Wire.beginTransmission(poti_manufactur_address);
  Wire.write(wiperIndex);
  Wire.endTransmission();
  Wire.requestFrom(poti_manufactur_address, (uint8_t)1);
  uint8_t one = Wire.read();
  return one;
}

void AD5252::decrement(uint8_t wiperIndex) {
}

void AD5252::increment(uint8_t wiperIndex) {
}

void AD5252::increment(uint8_t wiperIndex, int steps, int stepDelay) {
}

void AD5252::decrement(uint8_t wiperIndex, int steps, int stepDelay) {
}

