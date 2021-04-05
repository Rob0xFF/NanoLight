#include <Arduino.h>
#include <avr/wdt.h>
#include <Wire.h>

#include "board.h"

Board * board;

volatile uint8_t tick = false;
#define TOCK false;
void tikTok()
{
  tick = true;
}

int atexit(void ( * /*func*/ )())
{
  return 0;
}

void initVariant() __attribute__((weak));
void initVariant() { }

int main(void)
{
  init();
  initVariant();
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), tikTok, RISING);
  board = new Board();
  wdt_enable(WDTO_8S);
  wdt_reset();
  for (;;) {
    if (tick) {
      board -> update();
      wdt_reset();
      tick = TOCK;
    }
  }
  return 0;
}