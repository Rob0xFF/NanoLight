#include <pwmDevice.h>


PWMDevice::PWMDevice(uint8_t ctlPin) : _controlPin(ctlPin)
{
  pinMode(_controlPin, OUTPUT);
}

void PWMDevice::setPercent(uint8_t setPoint)
{
  _pwm = map(setPoint, 0, 100, 0, 255);
  analogWrite(_controlPin, _pwm);
}

uint8_t PWMDevice::getPercent(void)
{
  return map(_pwm, 0, 255, 0, 100);
}

void PWMDevice::setPWM(uint8_t setPoint)
{
  _pwm = setPoint;
  analogWrite(_controlPin, _pwm);
}

uint8_t PWMDevice::getPWM(void)
{
  return _pwm;
}

void PWMDevice::on(void)
{
  _pwm = 255;
  digitalWrite(_controlPin, HIGH);
}

void PWMDevice::off(void)
{
  _pwm = 0;
  digitalWrite(_controlPin, LOW);
}