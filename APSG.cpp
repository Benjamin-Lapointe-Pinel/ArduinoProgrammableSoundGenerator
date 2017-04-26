#include "APSG.h"

oscillator squares[NUMBER_OF_SQUARES];
oscillator triangle;
oscillator sawtooth;
oscillator noise;
oscillator sample;
oscillator *channels[NUMBER_OF_CHANNELS] =
{
  &squares[0],
  &squares[1],
  &triangle,
  &sawtooth,
  &noise,
  &sample
};



//TODO: -> (and rename parameter!)
void update_channel(struct oscillator& o, uint16_t c)
{
  if ((o.note >= o.sample_speed) && (o.note <= SID_C0))
  {
    o.frequency -= o.sample_speed;
    if (o.frequency < 0)
    {
      o.frequency += o.note;
      o.index++;
    }
    if ((o.sweep_shift) && !(c & o.sweep_speed))
    {
      uint16_t sweep = o.note >> o.sweep_shift;
      o.note += sweep * o.sweep_direction;
    }
  }
}

void init_SID()
{
  noInterrupts();

  pinMode(3, OUTPUT);

  TCCR2A =  _BV(COM2B1) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20);
  OCR2A = 0x7f; //7-bit precision => 125kHz PWM frequency
  TIMSK2 = _BV(TOIE2);

  for (uint8_t i = 0; i < NUMBER_OF_SQUARES; ++i)
  {
    init_square_oscillator(squares[i]);
  }
  init_triangle_oscillator(triangle);
  init_sawtooth_oscillator(sawtooth);
  init_noise_oscillator(noise);
  init_sample_oscillator(sample, {0}, 1);

  interrupts();
}

uint32_t seed = 0xD1CE5EED;
void set_noise_seed(uint32_t s)
{
  seed = s;
}

//TODO inline? Optimisation voulu peut-être?...
uint8_t get_noise()
{
  uint32_t r = seed & 0x00000001;
  seed >>= 1;
  r ^= seed & 0x00000001;
  seed |= r << 31;
  return r;
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

void init_square_oscillator(struct oscillator& o)
{
  delete[] o.sample;
  o.sample_length = 8;
  o.sample_speed = SAMPLE_SPEED(o.sample_length);
  o.sample = new uint8_t[o.sample_length];
  o.sample_length--;
  
  set_square_duty_cycle(o, 4);
}

void init_triangle_oscillator(struct oscillator& o)
{
  o.sample_length = 16;
  o.sample_speed = SAMPLE_SPEED(o.sample_length);
  o.sample = new uint8_t[o.sample_length];
  o.sample_length--;

  o.sample[0]   = 6;
  o.sample[1]   = 12;
  o.sample[2]   = 18;
  o.sample[3]   = 24;
  o.sample[4]   = 30;
  o.sample[5]   = 36;
  o.sample[6]   = 42;
  o.sample[7]   = 48;
  o.sample[8]   = 42;
  o.sample[9]   = 36;
  o.sample[10]  = 30;
  o.sample[11]  = 24;
  o.sample[12]  = 18;
  o.sample[13]  = 12;
  o.sample[14]  = 6;
  o.sample[15]  = 0;
}

void init_sawtooth_oscillator(struct oscillator& o)
{
  o.sample_length = 16;
  o.sample_speed = SAMPLE_SPEED(o.sample_length);
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
  o.sample_speed = 256;
  o.sample = new uint8_t[o.sample_length];
  o.sample_length--;
  
  o.sample[0] = 0;
}

void init_sample_oscillator(struct oscillator& o, uint8_t s[], uint8_t sl)
{
  init_sample_oscillator(o, s, sl, SAMPLE_SPEED(sl));
}

void init_sample_oscillator(struct oscillator& o, uint8_t s[], uint8_t sl, uint16_t sample_speed)
{
  delete[] o.sample;
  o.sample_length = sl;
  o.sample_speed = sample_speed;
  o.sample = new uint8_t[o.sample_length];

  //Useless maybe? Pointer maybe?
  for (uint8_t i = 0; i < o.sample_length; ++i)
  {
    o.sample[i] = s[i];
  }

  o.sample_length--;
}

void copy_channel_sound(struct oscillator& source, struct oscillator& copy)
{
  copy.note = source.note;
  copy.volume = source.volume;
  copy.sweep_direction = source.sweep_direction;
  copy.sweep_shift = source.sweep_shift;
  copy.sweep_speed = source.sweep_speed;
}

void silence()
{
  for (int i = 0; i < NUMBER_OF_CHANNELS; i++)
  {
    channels[i]->note = 0;
    channels[i]->sweep_direction = 0;
    channels[i]->sweep_shift = 0;
    channels[i]->sweep_speed = 0;
  }
}

uint8_t steps[3] = {0};
uint16_t wave = 0;
uint16_t counter = 0;

ISR(TIMER2_OVF_vect)
{
  switch (wave)
  {
    case 0:
      steps[wave] = 0;
      
      for (uint8_t i = 0; i < NUMBER_OF_SQUARES; ++i)
      {
        if ((squares[i].note >= squares[i].sample_speed) && (squares[i].note <= SID_C0))
        {
          squares[i].frequency -= squares[i].sample_speed;
          if (squares[i].frequency < 0)
          {
            squares[i].frequency += squares[i].note;
            squares[i].index++;
          }
          if ((squares[i].sweep_shift) && !(counter & squares[i].sweep_speed))
          {
            uint16_t sweep = squares[i].note >> squares[i].sweep_shift;
            squares[i].note += sweep * squares[i].sweep_direction;
          }
          steps[wave] += squares[i].sample[squares[i].index & squares[i].sample_length] ? squares[i].volume : 0; // Tester le volume comme une division entière pour voir la rapidité. Ou un shift << >>
        }
      }
      break;
    case 1:
      steps[wave] = 0;
      
      if ((triangle.note >= triangle.sample_speed) && (triangle.note <= SID_C0))
      {
        triangle.frequency -= triangle.sample_speed;
        if (triangle.frequency < 0)
        {
          triangle.frequency += triangle.note;
          triangle.index++;
        }
        if ((triangle.sweep_shift) && !(counter & triangle.sweep_speed))
        {
          uint16_t sweep = triangle.note >> triangle.sweep_shift;
          triangle.note += sweep * triangle.sweep_direction;
        }
        steps[wave] += triangle.sample[triangle.index & triangle.sample_length] >> (3 - (triangle.volume >> 2));
      }
    
      if ((sawtooth.note >= sawtooth.sample_speed) && (sawtooth.note <= SID_C0))
      {
        sawtooth.frequency -= sawtooth.sample_speed;
        if (sawtooth.frequency < 0)
        {
          sawtooth.frequency += sawtooth.note;
          sawtooth.index++;
        }
        if ((sawtooth.sweep_shift) && !(counter & sawtooth.sweep_speed))
        {
          uint16_t sweep = sawtooth.note >> sawtooth.sweep_shift;
          sawtooth.note += sweep * sawtooth.sweep_direction;
        }
        steps[wave] += sawtooth.sample[sawtooth.index & sawtooth.sample_length] >> (3 - (sawtooth.volume >> 2));
      }
      break;
    case 2:
      steps[wave] = 0;
      
      if ((noise.note >= noise.sample_speed) && (noise.note <= SID_C0))
      {
        noise.frequency -= noise.sample_speed;
        if (noise.frequency < 0)
        {
          noise.frequency += noise.note;
          noise.index = get_noise();
        }
        if ((noise.sweep_shift) && !(counter & noise.sweep_speed))
        {
          uint16_t sweep = noise.note >> noise.sweep_shift;
          noise.note += sweep * noise.sweep_direction;
        }
        steps[wave] += noise.index ? 0 : noise.volume;
      }

      if ((sample.sample_length) && (sample.note >= sample.sample_speed) && (sample.note <= SID_C0))
      {
        sample.frequency -= sample.sample_speed;
        if (sample.frequency < 0)
        {
          sample.frequency += sample.note;
          sample.index++;
        }
        if ((sample.sweep_shift) && !(counter & sample.sweep_speed))
        {
          uint16_t sweep = sample.note >> sample.sweep_shift;
          sample.note += sweep * sample.sweep_direction;
        }
        steps[wave] += sample.sample[sample.index & sample.sample_length];
      }
      break;
    case 3:
      OCR2B = 0;
      for (int i = 0; i < wave; i++)
      {
        OCR2B += steps[i];
      }

      counter++;
      wave = -1;
      break;
  }
  wave++;
}










