#ifndef SOUND_INTERFACE_DEVICE_H
#define SOUND_INTERFACE_DEVICE_H

#include <stdint.h>

struct channel
{
  uint16_t note;
  int16_t frequency;
  uint8_t index;
  uint8_t pwm;
  uint8_t volume;
};

struct triangle : channel
{
  uint8_t vector;
};

const static uint8_t NUMBER_OF_SQUARES = 4;
extern volatile channel squares[NUMBER_OF_SQUARES];

const static uint8_t NUMBER_OF_TRIANGLES = 1;
extern volatile triangle triangles[NUMBER_OF_TRIANGLES];

const static uint8_t NUMBER_OF_SAWTOOTH = 1;
extern volatile channel sawtooths[NUMBER_OF_SAWTOOTH];

/*void set_noise_seed(int16_t);
int16_t get_noise();*/
void clear_channel(volatile struct channel&);

#endif
