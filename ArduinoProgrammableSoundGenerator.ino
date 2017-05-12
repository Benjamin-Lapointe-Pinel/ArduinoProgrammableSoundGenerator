#include "APSG.h"
#include "melodies.h"

void setup()
{
  Serial.begin(9600);
  init_SID(); //Output on pin 3
}

void loop()
{
  //Each line is an example. Uncomment accordingly
  
  //sampleTest();
  //sweepTest();
  //scaleSequence();
  //melodyExample();
}








void melodyExample()
{
  /*
   * squares[0] = channels[0]
   * squares[1] = channels[1]
   * triangle   = channels[2]
   * sawtooth   = channels[3]
   * noise      = channels[4]
   * sample     = channels[5]
   */
  
  uint8_t melody_i = 0;

  noise.volume = 12;
  set_square_duty_cycle(squares[1], 2);

  while (true)
  {
    for (uint8_t i = 0; i < NUMBER_OF_CHANNELS; ++i)
    {
      channels[i]->note = pgm_read_word(&melody[i][melody_i]); //Read melody from PROGMEM (melodies.h)
    }
  
    //Cut square2 and noise short
    delay(35);
    squares[1].note = N_NOP;
    delay(15);
    noise.note = N_NOP;
    delay(50);
    
    melody_i = (melody_i + 1) % MELODY_LENGTH;
  }
}

/****************************** DEBUG ******************************/

uint16_t debug_array[] =
{
  N_C0, N_D0, N_E0, N_F0, N_G0, N_A0, N_B0, N_C1, N_NOP,
  N_C1, N_D1, N_E1, N_F1, N_G1, N_A1, N_B1, N_C2, N_NOP,
  N_C2, N_D2, N_E2, N_F2, N_G2, N_A2, N_B2, N_C3, N_NOP,
  N_C3, N_D3, N_E3, N_F3, N_G3, N_A3, N_B3, N_C4, N_NOP,
  N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_NOP,
  N_C5, N_D5, N_E5, N_F5, N_G5, N_A5, N_B5, N_C6, N_NOP,
  N_C6, N_D6, N_E6, N_F6, N_G6, N_A6, N_B6, N_C7, N_NOP,
  N_C7, N_D7, N_E7, N_F7, N_G7, N_A7, N_B7, N_NOP
};

void scaleSequence()
{
  for (uint8_t i = 0; i < NUMBER_OF_CHANNELS; ++i)
  {
    for (uint8_t j = 0; j < 71; ++j)
    {
      channels[i]->note = debug_array[j];
      delay(200);
    }
  }
  for (uint8_t j = 0; j < 71; ++j)
  {
    for (uint8_t i = 0; i < NUMBER_OF_CHANNELS; ++i)
    {      
      channels[i]->note = debug_array[j];
    }
    delay(200);
  }
}

void sampleTest()
{
  /*
  15|            ---
  14|         ---   ---
  13|      ---         ---
  12|                     
  11|                     
  10|   ---               ---
   9|                        
   7|                           
   6|                           
   8|---                     ---
   5|                           ---               ---
   4|                              
   3|                              
   2|                              ---         ---
   1|                                 ---   ---
   0|                                    ---
    |________________________________________________
      0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
  */
  uint8_t sin_wave[16] = {8, 10, 13, 14, 15, 14, 13, 10, 8, 5, 2, 1, 0, 1, 2, 5};
  init_sample_oscillator(sample, sin_wave, 16);

  while (true)
  {
    sample.note = N_A4;
    delay(100);
  }
}

void sweepTest()
{
  for (uint8_t i = 0; i < NUMBER_OF_CHANNELS; ++i)
  {
    channels[i]->sweep_direction = SWEEP_DOWN;
    channels[i]->sweep_shift = 1;
    channels[i]->sweep_speed = SWEEP_SPEED(8);
    for (uint8_t j = 0; j < 71; ++j)
    {
      channels[i]->note = debug_array[j];
      delay(200);
    }
    channels[i]->sweep_direction = SWEEP_NOP;
    channels[i]->sweep_shift = 0;
    channels[i]->sweep_speed = SWEEP_SPEED(0);
  }
  //megaman quickman laser beam (are those really sweeps?)
}












