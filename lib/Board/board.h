#ifndef BOARD_h
#define BOARD_h

#include "Arduino.h"
#include "Wire.h"

#include "settings.h"
#include <DS3231.h>
#include <pwmDevice.h>
#include <digitalDevice.h>

class Board
{
  public:

    Board()
    {
      _light.off();
      _powerLED.on();
      _clock.begin();
      // uncomment to automatically set clock, you need to comment, recompile and flash again after the clock is set and running, otherwise the clock will be set to this date everytime the device is started
      //_clock.setDateTime(__DATE__, __TIME__);
      _clock.enable32kHz(true);
      _clock.setOutput(DS3231_1HZ);
      _clock.enableOutput(true);
    };

    void update();

  private:

    DS3231 _clock;
    RTCDateTime _dt;

    // check if RTC was set while summer or winter time
    uint8_t clockAtDST = 0;

    uint8_t DST = 0;

    void updateTime(void);

    PWMDevice _light = PWMDevice(9);

    DigitalDevice _powerLED = DigitalDevice(16);

    DigitalDevice _statusLED = DigitalDevice(17);

    uint8_t length = sizeof(timeTable) / sizeof(timeTable[0]);

    int16_t elapsedMinutes;
    int16_t lastTime;
    int16_t lastPoint;
    int16_t nextTime;
    int16_t nextPoint;

    float segmentProgress;
    uint8_t newBrightness;

};
#endif