#include "APSG.h"
#include "melodies.h"

//http://nesdev.com/NESSOUND.txt
//http://www.slack.net/~ant/nes-emu/apu_ref.txt


//TODO : je n'ai pas de génération d'envelope https://wiki.nesdev.com/w/index.php/APU_Envelope
//TODO: traiter tous les channels comme le sample!
//(sauf peut-être le noise, mais encore là... il pourrait avoir une très grande table de noise en mémoire... entk)
// C'est sur qu'il y aurait surement une perte de controle sur le volume

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
  noise.volume = 12;
  set_square_duty_cycle(squares[1], 2);
  
  for (uint8_t i = 0; i < NUMBER_OF_CHANNELS; ++i)
  {
    //Read melody from PROGMEM
    channels[i]->note = pgm_read_word(&melody[i][melody_i]);
  }

  //Cut square2 and noise short
  delay(35);
  squares[1].note = 0;
  delay(15);
  noise.note = 0;
  delay(50);
  
  melody_i = (melody_i + 1) % MELODY_LENGTH;
}


//****************************** DEBUG ******************************//
void sampleTest()
{
  uint8_t sin_wave[16] = {8,10,13,14,15,14,13,10,8,5,2,1,0,1,2,5};
  init_sample_oscillator(sample, sin_wave, 16);

  sample.note = N_A4;
  delay(2000);
}

void sweepTest()
{
  triangle.sweep_direction = SWEEP_DOWN;
  triangle.sweep_shift = 1;
  triangle.sweep_speed = SWEEP_SPEED(7);

  triangle.note = N_C5;
  delay(2000);
}


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

void debug()
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










