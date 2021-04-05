/*!
* @brief course of day schedule, declare each node, brightness will be interpolated in between to allow smooth ramping
* @syntax {hour[0 .. 23], minute[0 .. 59], brightness[0 .. 100]},
*/

const static uint8_t timeTable[][3] = {

  {11, 30, 0},
  {13, 30, 100},
  {20, 30, 100},
  {22, 30, 0}

};