#include <board.h>

void Board::updateTime(void)
{
  _dt = _clock.getDateTime();
  // https://electronicfreakblog.wordpress.com/2014/03/06/die-zeit-im-sommer-und-im-winter/#more-413
  if (_dt.dayOfWeek == 7) {
    _dt.dayOfWeek = 0;
  }
  if (_dt.month <= 2 || _dt.month >= 11) {
    DST = false;
  }
  if (_dt.month >= 4 && _dt.month <= 9) {
    DST = true;
  }
  if (_dt.month == 3 && _dt.day - _dt.dayOfWeek >= 25) {
    if (_dt.hour >= 3) {
      DST = true;
    }
  }
  if (_dt.month == 10 && _dt.day - _dt.dayOfWeek < 25) {
    DST = true;
  }
  if (_dt.month == 10 && _dt.day - _dt.dayOfWeek >= 25) {
    if (_dt.hour >= 3) {
      DST = false;
    } else {
      DST = true;
    }
  }
  if (DST == true && !clockAtDST) {
    _dt.hour += 1;
  }
  if (DST == false && clockAtDST) {
    _dt.hour -= 1;
  }
}

void Board::update(void)
{
  updateTime();
  elapsedMinutes = 60 * _dt.hour + _dt.minute;
  lastTime = -1;
  lastPoint = 0;
  nextTime = -1;
  nextPoint = 0;
  for (uint8_t i = 0; i < length; i++) {
    if (elapsedMinutes >= 60 * timeTable[i][0] + timeTable[i][1]) {
      lastTime = 60 * timeTable[i][0] + timeTable[i][1];
      lastPoint = timeTable[i][2];
    }
  }
  if (lastTime == -1) {
    lastTime = 60 * timeTable[length - 1][0] + timeTable[length - 1][1];
    lastPoint = timeTable[length - 1][2];
  }
  for (int8_t i = length - 1; i >= 0; i--) {
    if (elapsedMinutes < 60 * timeTable[i][0] + timeTable[i][1]) {
      nextTime = 60 * timeTable[i][0] + timeTable[i][1];
      nextPoint = timeTable[i][2];
    }
  }
  if (nextTime == -1) {
    nextTime = 60 * timeTable[0][0] + timeTable[0][1];
    nextPoint = timeTable[0][2];
  }
  segmentProgress = 0.0;
  if (nextTime >= lastTime) { // no midnight in interval
    segmentProgress = (float) (elapsedMinutes - lastTime) / (nextTime - lastTime);
  } else {	// interval contains midnight
    if (elapsedMinutes >= lastTime) { // before midnight
      segmentProgress = (float) (elapsedMinutes - lastTime) / (nextTime + 24 * 60 - lastTime);
    } else {	// after midnight
      segmentProgress = (float) (elapsedMinutes + 24 * 60 - lastTime) / (nextTime + 24 * 60 - lastTime);
    }
  }
  newBrightness = (uint8_t) ( lastPoint + (nextPoint - lastPoint) * segmentProgress);
  _light.setPercent(newBrightness);
  if (newBrightness > 0) {
    _statusLED.on();
    _powerLED.off();
  } else {
    _statusLED.off();
    _powerLED.on();
  }
}