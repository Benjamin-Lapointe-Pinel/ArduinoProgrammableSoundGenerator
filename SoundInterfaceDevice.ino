#include "SoundInterfaceDevice.h"

#define SWEEP_SPEED(x) (1 << x) - 1

const static uint8_t NUMBER_OF_SQUARES    = 4;
const static uint8_t NUMBER_OF_TRIANGLES  = 1;
const static uint8_t NUMBER_OF_SAWTOOTHS  = 1;
const static uint8_t NUMBER_OF_NOISES     = 1;
const static uint8_t NUMBER_OF_SAMPLES    = 1;
const static uint8_t NUMBER_OF_CHANNELS   = NUMBER_OF_SQUARES + NUMBER_OF_TRIANGLES + NUMBER_OF_SAWTOOTHS + NUMBER_OF_NOISES + NUMBER_OF_SAMPLES;

struct oscillator
{ 
  uint16_t note = 0;
  
  int16_t frequency = 0;
  uint8_t index = 0;

  uint8_t* sample = NULL;
  uint16_t sample_length = 0;

  uint8_t volume = 15;
  int8_t sweep_direction = 0;
  uint8_t sweep_shift = 0;
  uint16_t sweep_speed = 0;
};

oscillator squares[NUMBER_OF_SQUARES];
oscillator triangle;
oscillator sawtooth;
oscillator noise;
oscillator sample;
oscillator *channels[NUMBER_OF_CHANNELS] =
{
  &squares[0],
  &squares[1],
  &squares[2],
  &squares[3],
  &triangle,
  &sawtooth,
  &noise,
  &sample
};

uint16_t seed = 0xD1CE5EED;

void set_noise_seed(uint16_t s)
{
  seed = s;
}

uint8_t get_noise()
{
  uint8_t r = seed & 0x0001;
  seed >>= 1;
  r ^= seed & 0x0001;
  seed |= (uint16_t)r << 15;
  return r;
}

void init_square_oscillator(struct oscillator& o)
{
  delete[] o.sample;
  o.sample_length = 8;
  o.sample = new uint8_t[o.sample_length];
  o.sample_length--;
  
  set_square_duty_cycle(o, 4);
}

void set_square_duty_cycle(struct oscillator& o, uint8_t duty_cycle)
{
  uint8_t i = 0;
  for (; i < duty_cycle; ++i)
  {
    o.sample[i] = 1;
  }
  uint8_t sl = o.sample_length + 1;
  for (; i < sl; ++i)
  {
    o.sample[i] = 0;
  }
}

void init_triangle_oscillator(struct oscillator& o)
{
  o.sample_length = 16;
  o.sample = new uint8_t[o.sample_length];
  o.sample_length--;

  o.sample[0]   = 1;
  o.sample[1]   = 3;
  o.sample[2]   = 5;
  o.sample[3]   = 7;
  o.sample[4]   = 9;
  o.sample[5]   = 11;
  o.sample[6]   = 13;
  o.sample[7]   = 15;
  o.sample[8]   = 14;
  o.sample[9]   = 12;
  o.sample[10]  = 10;
  o.sample[11]  = 8;
  o.sample[12]  = 6;
  o.sample[13]  = 4;
  o.sample[14]  = 2;
  o.sample[15]  = 0;
}

void init_sawtooth_oscillator(struct oscillator& o)
{
  o.sample_length = 16;
  o.sample = new uint8_t[o.sample_length];
  o.sample_length--;
  
  o.sample[0]   = 0;
  o.sample[1]   = 1;
  o.sample[2]   = 2;
  o.sample[3]   = 3;
  o.sample[4]   = 4;
  o.sample[5]   = 5;
  o.sample[6]   = 6;
  o.sample[7]   = 7;
  o.sample[8]   = 8;
  o.sample[9]   = 9;
  o.sample[10]  = 10;
  o.sample[11]  = 11;
  o.sample[12]  = 12;
  o.sample[13]  = 13;
  o.sample[14]  = 14;
  o.sample[15]  = 15;
}

void init_noise_oscillator(struct oscillator& o)
{
  o.sample_length = 1;
  o.sample = new uint8_t[o.sample_length];
  o.sample_length--;
  
  o.sample[0] = 0;
}

void init_sample_oscillator(struct oscillator& o, uint8_t* s, uint8_t sl)
{
  delete[] o.sample;
  o.sample = s;
  o.sample_length = sl;
  o.note = 0;
}

void setup()
{
  Serial.begin(250000);

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

  for (uint8_t i = 0; i < NUMBER_OF_SQUARES; ++i)
  {
    init_square_oscillator(squares[i]);
  }
  init_triangle_oscillator(triangle);
  init_sawtooth_oscillator(sawtooth);
  init_noise_oscillator(noise);
  init_sample_oscillator(sample, NULL, 0);
}

uint16_t counter = 1;

ISR(TIMER1_COMPA_vect)
{
  OCR2B = 0;
  
  for (uint8_t i = 0; i < NUMBER_OF_SQUARES; ++i)
  {
    if ((squares[i].note >= 32) && (squares[i].note <= SID_C0))
    {
      squares[i].frequency -= 32;
      if (squares[i].frequency < 0)
      {
        squares[i].frequency += squares[i].note;
        squares[i].index++;
      }
      if ((squares[i].sweep_shift) && !(counter & squares[i].sweep_speed))
      {
        uint16_t sweep = squares[i].note >> squares[i].sweep_shift;
        if (!sweep)
        {
          squares[i].note = 0;
          squares[i].sweep_direction = 0;
          squares[i].sweep_shift = 0;
          squares[i].sweep_speed = 0;
        }
        else if (squares[i].sweep_direction)
        {
          squares[i].note -= sweep;
        }
        else
        {
          squares[i].note += sweep;
        }
      }
      OCR2B += squares[i].sample[squares[i].index & squares[i].sample_length] ? squares[i].volume : 0;
    }
  }

  if ((triangle.note >= 64) && (triangle.note <= SID_C0))
  {
    triangle.frequency -= 64;
    if (triangle.frequency < 0)
    {
      triangle.frequency += triangle.note;
      triangle.index++;
    }
    if ((triangle.sweep_shift) && !(counter & triangle.sweep_speed))
    {
      uint16_t sweep = triangle.note >> triangle.sweep_shift;
      if (!sweep)
      {
        triangle.note = 0;
        triangle.sweep_direction = 0;
        triangle.sweep_shift = 0;
        triangle.sweep_speed = 0;
      }
      else if (triangle.sweep_direction)
      {
        triangle.note -= sweep;
      }
      else
      {
        triangle.note += sweep;
      }
    }
    OCR2B += triangle.sample[triangle.index & triangle.sample_length] >> (3 - (triangle.volume >> 2));
  }

  if ((sawtooth.note >= 64) && (sawtooth.note <= SID_C0))
  {
    sawtooth.frequency -= 64;
    if (sawtooth.frequency < 0)
    {
      sawtooth.frequency += sawtooth.note;
      sawtooth.index++;
    }
    if ((sawtooth.sweep_shift) && !(counter & sawtooth.sweep_speed))
    {
      uint16_t sweep = sawtooth.note >> sawtooth.sweep_shift;
      if (!sweep)
      {
        sawtooth.note = 0;
        sawtooth.sweep_direction = 0;
        sawtooth.sweep_shift = 0;
        sawtooth.sweep_speed = 0;
      }
      else if (sawtooth.sweep_direction)
      {
        sawtooth.note -= sweep;
      }
      else
      {
        sawtooth.note += sweep;
      }
    }
    OCR2B += sawtooth.sample[sawtooth.index & sawtooth.sample_length] >> (3 - (sawtooth.volume >> 2));
  }

  if (noise.note)
  {
    noise.frequency -= 256;
    if (noise.frequency < 0)
    {
      noise.frequency += noise.note;
      noise.index = get_noise();
    }
    
    OCR2B += noise.index ? 0 : noise.volume;
  }
  
  /*
  for (; i < j; ++i)
  {
    if (!channels[i].sample_length)
    {
      channels[i].frequency--;
      if (channels[i].frequency < 0)
      {
        channels[i].frequency += channels[i].note;
        channels[i].index++;
      }
      OCR2B += channels[i].sample[channels[i].index & channels[i].sample_length];
    }
  }*/

  counter++;
}

const static uint8_t MELODY_LENGTH = 64;
const static uint16_t melody[NUMBER_OF_CHANNELS][MELODY_LENGTH] PROGMEM =
{
  {SID_D4, SID_D4, SID_D4, SID_D4, SID_D4, 0, SID_D4, SID_F4, SID_AS4, SID_AS4, SID_AS4, SID_AS4, SID_A4, SID_A4, SID_A4, SID_F4, SID_G4, SID_G4, SID_G4, SID_G4, SID_G4, SID_G4, SID_F4, SID_E4, SID_F4, SID_F4, SID_E4, SID_D4, SID_E4, SID_E4, SID_D4, SID_C4, SID_G4, SID_G4, SID_G4, SID_G4, SID_G4, 0, SID_G4, SID_A4, SID_AS4, SID_AS4, SID_AS4, SID_AS4, SID_A4, SID_A4, SID_A4, SID_AS4, SID_C5, SID_C5, SID_C5, SID_C5, SID_C5, SID_C5, SID_AS4, SID_C5, SID_D5, SID_D5, SID_C5, SID_C5, SID_AS4, SID_AS4, SID_A4, SID_A4},
  {SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4, SID_A4, SID_AS4, SID_A4, SID_G4},  
  {},
  {},
  {SID_G3, 0, SID_G3, SID_G3, SID_G3, 0, SID_G3, SID_G3, SID_G3, 0, SID_G3, SID_G3, SID_G3, 0, SID_G3, SID_G3, SID_C3, 0, SID_C3, SID_C3, SID_C3, 0, SID_C3, SID_C3, SID_C3, 0, SID_C3, SID_C3, SID_C3, 0, SID_C3, SID_C3, SID_DS3, 0, SID_DS3, SID_DS3, SID_DS3, 0, SID_DS3, SID_DS3, SID_DS3, 0, SID_DS3, SID_DS3, SID_DS3, 0, SID_DS3, SID_DS3, SID_F3, 0, SID_F3, SID_F3, SID_F3, 0, SID_F3, SID_F3, SID_F3, 0, SID_F3, SID_F3, SID_F3, 0, SID_F3, SID_F3},
  {},
  {SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3, SID_E1, 0, SID_DS3, SID_DS3},
  {}
};

/*const static uint8_t MELODY_LENGTH = 128;
const static uint16_t melody[NUMBER_OF_CHANNELS][MELODY_LENGTH] PROGMEM =
{
  {},
  {SID_GS3, 0, SID_GS3, 0, SID_FS4, 0, SID_GS3, 0, SID_DS4, 0, SID_GS3, 0, SID_CS4, 0, SID_GS3, 0, 0, 0, SID_GS3, 0, SID_FS4, 0, SID_GS3, 0, SID_DS4, 0, SID_GS3, 0, SID_CS4, 0, SID_GS3, 0, SID_GS3, 0, SID_GS3, 0, SID_FS4, 0, SID_GS3, 0, SID_DS4, 0, SID_GS3, 0, SID_CS4, 0, SID_GS3, 0, 0, 0, SID_GS3, 0, SID_FS4, 0, SID_GS3, 0, SID_DS4, 0, SID_GS3, 0, SID_CS4, 0, SID_GS3, 0, SID_GS3, 0, SID_GS3, 0, SID_FS4, 0, SID_GS3, 0, SID_DS4, 0, SID_GS3, 0, SID_CS4, 0, SID_GS3, 0, 0, 0, SID_GS3, 0, SID_FS4, 0, SID_GS3, 0, SID_DS4, 0, SID_GS3, 0, SID_CS4, 0, SID_GS3, 0, SID_GS3, 0, SID_GS3, 0, SID_FS4, 0, SID_GS3, 0, SID_DS4, 0, SID_GS3, 0, SID_CS4, 0, SID_GS3, 0, 0, 0, SID_GS3, 0, SID_AS3, 0, SID_GS3, 0, SID_B4, 0, SID_AS4, 0, SID_GS4, 0, SID_FS4, 0},
  {},
  {},
  {},//{SID_GS3, 0, SID_GS3, 0, SID_GS3, 0, SID_GS3, 0, },
  {},
  {2000, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0},
  {}
};*/

uint8_t melody_i = 0;
uint16_t i = 0;

void loop()
{
  triangle.volume = 15;
  noise.volume = 12;
  squares[0].volume = 11;
  squares[1].volume = 10;
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







