#include "SoundInterfaceDevice.h"

#define CHANNEL 7

struct channel
{
  uint8_t waveform[16];
  uint16_t note;
  int16_t frequency;
  uint8_t index;
};

channel channels[CHANNEL] =
{
  //square (duty cycle 50%)
  {
    .waveform = {15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0},
    .note = 0,
    .frequency = 0,
    .index = 0
  },
  //square (duty cycle 50%)
  {
    .waveform = {15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0},
    .note = 0,
    .frequency = 0,
    .index = 0
  },
  //ramp
  {
    .waveform = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
    .note = 0,
    .frequency = 0,
    .index = 0
  },
  //sawtooth
  {
    .waveform = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
    .note = 0,
    .frequency = 0,
    .index = 0
  },
  //triangle
  {
    .waveform = {1, 3, 5, 7, 9, 11, 13, 15, 14, 12, 10, 8, 6, 4 ,2, 0},
    .note = 0,
    .frequency = 0,
    .index = 0
  },
  //triangle
  {
    .waveform = {1, 3, 5, 7, 9, 11, 13, 15, 14, 12, 10, 8, 6, 4 ,2, 0},
    .note = 0,
    .frequency = 0,
    .index = 0
  },
  //noise
  {
    .waveform = {15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0},
    .note = 0,
    .frequency = 0,
    .index = 0
  }
};

const uint16_t noise_table[16] = {4, 8, 16, 32, 64, 96, 128, 160, 202, 254, 380, 508, 762, 1016, 2034, 4068};

void setup()
{
  Serial.begin(9600);

  noInterrupts();

  pinMode(3, OUTPUT);
  
  //CTC mode => 31250Hz sample recalculation
  TCCR1A = 0x00;
  TCCR1B = _BV(WGM12) | _BV(CS10);
  OCR1A = 511;
  TIMSK1 = _BV(OCIE1A);

  //7-bit audio output precision => 125kHz PWM frequency
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20);
  OCR2A = 127;
  
  interrupts();
}

ISR(TIMER1_COMPA_vect)
{
  OCR2B = 0;
  for (uint8_t i = 0; i < CHANNEL; ++i)
  {
    if (channels[i].note)
    {
      channels[i].frequency -= 64;
      if (channels[i].frequency < 0)
      {
        channels[i].frequency += channels[i].note;
        channels[i].index++;
      }
      OCR2B += channels[i].waveform[channels[i].index & 15];
    }
  }
}

#define MELODY_LENGTH 32
const static uint16_t melody[CHANNEL][MELODY_LENGTH] PROGMEM =
{
  {0},//{SID_C5, SID_C5, SID_C5, SID_AS4, SID_AS4, SID_AS4, SID_CS5, SID_CS5, SID_CS5, SID_C5, SID_C5, SID_C5, SID_AS4, SID_AS4, SID_C5, SID_C5, SID_C5, SID_C5, SID_C5, SID_AS4, SID_AS4, SID_AS4, SID_GS4, SID_GS4, SID_GS4, SID_AS4, SID_AS4, SID_AS4, SID_GS4, SID_GS4, SID_AS4, SID_AS4},
  {0},//{SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4},  
  {0},
  {0},
  {SID_GS4, SID_GS4, 0, SID_GS4, SID_GS4, SID_GS4, SID_GS4, SID_GS4, SID_GS4, SID_GS4, SID_GS4, SID_GS4, 0, 0, SID_GS4, SID_G4, SID_FS4, SID_FS4, 0, SID_FS4, SID_FS4, SID_FS4, SID_FS4, SID_FS4, 0, SID_FS4, SID_FS4, SID_FS4, SID_FS4, SID_F4, SID_FS4, SID_G4},
  {0},
  {0}
};

uint8_t melody_i = 0;

void loop()
{
  for (int8_t i = 0; i < CHANNEL; ++i)
  {
    channels[i].note = pgm_read_word(&(melody[i][melody_i]));
  }
  delay(115);
  
  //Effects ghetto
  channels[0].note = 0;
  channels[1].note = 0;
  channels[2].note = 0;
  channels[3].note = 0;
  delay(15);
  
  melody_i = (melody_i + 1) % MELODY_LENGTH;
}










