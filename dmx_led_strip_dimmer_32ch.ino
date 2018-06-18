#include <EEPROM.h>
#include <DMXSerial2.h>
#include "Tlc5940.h"

#define RS485_PIN 2

const uint8_t channelMapping[] = {0, 1, 2, 3, 4, 5, 6, 7, 24, 25, 26, 27, 28, 29, 30, 31, 16, 17, 18, 19, 20, 21, 22, 23, 8, 9, 10, 11, 12, 13, 14, 15};

const uint16_t my_pids[] = {};
struct RDMINIT rdmInit = {
  "RobinOlejnik.de",
  1,
  "32ch_dmx_led_strip_dimmer",
  32,
  (sizeof(my_pids) / sizeof(uint16_t)), my_pids
};


void setup () {
  DMXSerial2.init(&rdmInit, processCommand, RS485_PIN, LOW, HIGH);
  Tlc.init();
}


void loop() {
  unsigned long lastPacket = DMXSerial2.noDataSince();
  Tlc.clear();

  if (DMXSerial2.isIdentifyMode()) {
    unsigned long now = millis();
    if (now % 1000 < 500) {
      for (unsigned char i = 0; i < 32; i++) {
        Tlc.set(i, 4095);
      }
    } else {
      for (unsigned char i = 0; i < 32; i++) {
        Tlc.set(i, 0);
      }
    }

  } else if (lastPacket < 5000) {
    for (unsigned char i = 0; i < 32; i++) {
      Tlc.set(channelMapping[i], DMXSerial2.readRelative(i) * 16);
    }
  } else {
    for (unsigned char i = 0; i < 32; i++) {
      Tlc.set(i, 0);
    }
  }
  Tlc.update();
  DMXSerial2.tick();
}

bool8 processCommand(struct RDMDATA *rdm, uint16_t *nackReason) {
  return false;
}
