#ifndef PWMDEVICE_h
#define PWMDEVICE_h

#include "Arduino.h"

/*!
 * @brief pwmDevice main class
 */
class PWMDevice
{
  public:

    PWMDevice(uint8_t ctlPin);

    void setPWM(uint8_t setPoint);

    uint8_t getPWM();

    void setPercent(uint8_t setPoint);

    uint8_t getPercent();

    void on(void);

    void off(void);

  private:

    uint8_t _pwm = 0;

    const uint8_t _controlPin;

};
#endif