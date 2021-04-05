#include <digitalDevice.h>


DigitalDevice::DigitalDevice(uint8_t ctlPin) : _controlPin(ctlPin)
{
  pinMode(_controlPin, OUTPUT);
}

void DigitalDevice::on(void)
{
	_state = 1;
  digitalWrite(_controlPin, HIGH);
}

void DigitalDevice::off(void)
{
	_state = 0;
  digitalWrite(_controlPin, LOW);
}

uint8_t DigitalDevice::getStatus(void)
{
	return _state;
}