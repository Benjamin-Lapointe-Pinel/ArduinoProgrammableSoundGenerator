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

  sample.note = SID_A4;
  delay(2000);
}

void sweepTest()
{
  noise.note = SID_C0;
  noise.sweep_direction = SWEEP_UP;
  noise.sweep_shift = 4;
  noise.sweep_speed = SWEEP_SPEED(9);
  delay(2000);
}
