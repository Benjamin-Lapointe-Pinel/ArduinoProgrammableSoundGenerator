#include <Arduino.h>
#include "SoundInterfaceDevice.h"

volatile channel squares[NUMBER_OF_SQUARES];
volatile triangle triangles[NUMBER_OF_TRIANGLES];
volatile channel sawtooths[NUMBER_OF_SAWTOOTH];

/*int16_t seed = 0x5EED5EED;

void set_noise_seed(int16_t s)
{
  seed = s;
}

int16_t get_noise()
{
  uint16_t r = seed >> 6;
  r = (r & 0x01) ^ (r >> 1);
  seed = (seed << 1) | r;
  return r;
}*/

void clear_channel(volatile struct channel& c)
{
  c.note = 0;
  c.frequency = 0;
  c.index = 0;
  c.pwm = 0;
  c.volume = 15;
}

uint16_t counter = 0;

ISR(TIMER1_COMPA_vect)
{
  counter++;
  
  OCR2B = 0;

  //squares
  for (uint8_t i = 0; i < NUMBER_OF_SQUARES; ++i)
  {
    if (squares[i].note)
    {
      squares[i].frequency -= 8;
      if (squares[i].frequency < 0)
      {
        squares[i].frequency += squares[i].note;
        
        if (squares[i].pwm)
        {
          squares[i].pwm = 0;
        }
        else
        {
          squares[i].pwm = squares[i].volume;
        }
      }
    }

    OCR2B += squares[i].pwm;
  }
  //triangles
  for (uint8_t i = 0; i < NUMBER_OF_TRIANGLES; ++i)
  {
    if (triangles[i].note)
    {
      triangles[i].frequency -= 64;
      if (triangles[i].frequency < 0)
      {
        triangles[i].frequency += triangles[i].note;
        triangles[i].pwm += triangles[i].vector;

        if (triangles[i].pwm == 17)
        {
          triangles[i].pwm = 14;
          triangles[i].vector = -2;
        }
        else if (triangles[i].pwm == 254)
        {
          triangles[i].pwm = 1;
          triangles[i].vector = 2;
        }
      }
    }
    
    OCR2B += triangles[i].pwm;
  }
  //sawtooths
  for (uint8_t i = 0; i < NUMBER_OF_SAWTOOTH; ++i)
  {
    if (sawtooths[i].note)
    {
      sawtooths[i].frequency -= 64;
      if (sawtooths[i].frequency < 0)
      {
        sawtooths[i].frequency += sawtooths[i].note;
        sawtooths[i].pwm = ++sawtooths[i].pwm & 15;
      }
    }

    OCR2B += sawtooths[i].pwm;
  }
}





