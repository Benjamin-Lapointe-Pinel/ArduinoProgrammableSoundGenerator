#ifndef APSG_H
#define APSG_H

#include <Arduino.h>
#include "note.h"

#define SAMPLE_SPEED(x) x * 4
#define SWEEP_SPEED(x) (1 << x) - 1
const static int8_t SWEEP_DOWN  = 1;
const static int8_t SWEEP_UP    = -1;

const static uint8_t NUMBER_OF_SQUARES    = 2;
const static uint8_t NUMBER_OF_TRIANGLES  = 1;
const static uint8_t NUMBER_OF_SAWTOOTHS  = 1;
const static uint8_t NUMBER_OF_NOISES     = 1;
const static uint8_t NUMBER_OF_SAMPLES    = 1;
const static uint8_t NUMBER_OF_CHANNELS   = NUMBER_OF_SQUARES
                                          + NUMBER_OF_TRIANGLES
                                          + NUMBER_OF_SAWTOOTHS
                                          + NUMBER_OF_NOISES
                                          + NUMBER_OF_SAMPLES;

struct oscillator
{ 
  uint16_t note = 0;
  
  int16_t frequency = 0;
  uint8_t index = 0;

  uint8_t* sample = NULL;
  uint16_t sample_length = 0;
  uint16_t sample_speed = 0;

  uint8_t volume = 15;
  int8_t sweep_direction = 0;
  uint8_t sweep_shift = 0;
  uint16_t sweep_speed = 0;
};

extern oscillator squares[NUMBER_OF_SQUARES];
extern oscillator triangle;
extern oscillator sawtooth;
extern oscillator noise;
extern oscillator sample;
extern oscillator *channels[NUMBER_OF_CHANNELS];

void init_SID();
void init_square_oscillator(struct oscillator& o);
void init_triangle_oscillator(struct oscillator& o);
void init_sawtooth_oscillator(struct oscillator& o);
void init_noise_oscillator(struct oscillator& o);
void init_sample_oscillator(struct oscillator& o, uint8_t s[], uint8_t sl);
void init_sample_oscillator(struct oscillator& o, uint8_t s[], uint8_t sl, uint16_t sample_speed);
void set_square_duty_cycle(struct oscillator& o, uint8_t duty_cycle);
uint8_t get_noise();
void copy_channel_sound(struct oscillator& source, struct oscillator& copy);
void update_channel(struct oscillator& o);
void silence();

#endif
