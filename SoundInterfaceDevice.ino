#include "SID.h"
#include "melodies.h"

void setup()
{
  Serial.begin(9600);
  init_SID();

  uint8_t sin_wave[16] = {8,10,13,14,15,14,13,10,8,5,2,1,0,1,2,5};
  init_sample_oscillator(sample, sin_wave, 16);
}

uint8_t melody_i = 0;

void loop()
{
  /*sawtooth.note = SID_C0;
  sawtooth.sweep_direction = SWEEP_UP;
  sawtooth.sweep_shift = 4;
  sawtooth.sweep_speed = SWEEP_SPEED(9);
  delay(10000);*/
  noise.volume = 12;
  set_square_duty_cycle(squares[1], 2);
  
  for (uint8_t i = 0; i < NUMBER_OF_CHANNELS; ++i)
  {
    channels[i]->note = pgm_read_word(&melody[i][melody_i]);
  }
  
  delay(35);
  squares[1].note = 0;
  delay(15);
  noise.note = 0;
  delay(50);
  
  melody_i = (melody_i + 1) % MELODY_LENGTH;
}
