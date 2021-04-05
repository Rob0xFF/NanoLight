#ifndef DIGITALDEVICE_h
#define DIGITALDEVICE_h

#include "Arduino.h"

/*!
 * @brief digitalDevice main class
 */
class DigitalDevice
{
  public:

    DigitalDevice(uint8_t ctlPin);

    void on(void);

    void off(void);

		uint8_t getStatus(void);

  private:

		uint8_t _state = 0;

    const uint8_t _controlPin;

};
#endif