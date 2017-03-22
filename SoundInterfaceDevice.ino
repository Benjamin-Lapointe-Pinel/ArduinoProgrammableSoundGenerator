#include "SoundInterfaceDevice.h"
#include "note.h"

void setup()
{
  Serial.begin(9600);

  noInterrupts();

  pinMode(3, OUTPUT);
  
  //CTC mode => 31.25kHz sample recalculation
  TCCR1A = 0x00;
  TCCR1B = _BV(WGM12) | _BV(CS10);
  OCR1A = 511;
  TIMSK1 = _BV(OCIE1A);

  //7-bit audio output precision => 125kHz PWM frequency
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20);
  OCR2A = 127;
  
  interrupts();

  for (int i = 0; i < NUMBER_OF_SQUARES; i++)
  {
    clear_channel(squares[i]);
  }
  for (int i = 0; i < NUMBER_OF_TRIANGLES; i++)
  {
    clear_channel(triangles[i]);
    triangles[i].pwm = 1;
    triangles[i].vector = 2;
  }
  for (int i = 0; i < NUMBER_OF_SAWTOOTH; i++)
  {
    clear_channel(sawtooths[i]);
  }
}

#define MELODY_LENGTH 32
const static uint16_t melody[NUMBER_OF_SQUARES + NUMBER_OF_TRIANGLES + NUMBER_OF_SAWTOOTH][MELODY_LENGTH] PROGMEM =
{
  {SID_C5, SID_C5, SID_C5, SID_AS4, SID_AS4, SID_AS4, SID_CS5, SID_CS5, SID_CS5, SID_C5, SID_C5, SID_C5, SID_AS4, SID_AS4, SID_C5, SID_C5, SID_C5, SID_C5, SID_C5, SID_AS4, SID_AS4, SID_AS4, SID_GS4, SID_GS4, SID_GS4, SID_AS4, SID_AS4, SID_AS4, SID_GS4, SID_GS4, SID_AS4, SID_AS4},
  {SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_DS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4, SID_CS4},  
  {0},
  {0},
  {SID_GS4, SID_GS4, 0, SID_GS4, SID_GS4, SID_GS4, SID_GS4, SID_GS4, SID_GS4, SID_GS4, SID_GS4, SID_GS4, 0, 0, SID_GS4, SID_G4, SID_FS4, SID_FS4, 0, SID_FS4, SID_FS4, SID_FS4, SID_FS4, SID_FS4, 0, SID_FS4, SID_FS4, SID_FS4, SID_FS4, SID_F4, SID_FS4, SID_G4},
  {0}
};

uint8_t melody_i = 0;

void loop()
{
  squares[0].note = pgm_read_word(&(melody[0][melody_i]));
  squares[1].note = pgm_read_word(&(melody[1][melody_i]));
  squares[2].note = pgm_read_word(&(melody[2][melody_i]));
  squares[3].note = pgm_read_word(&(melody[3][melody_i]));
  triangles[0].note = pgm_read_word(&(melody[4][melody_i]));
  sawtooths[0].note = pgm_read_word(&(melody[5][melody_i]));

  squares[0].volume = 8;
  squares[1].volume = 8;
  
  delay(115);
  
  //Effects ghetto
  squares[0].note = 0;
  squares[1].note = 0;
  delay(15);
  
  melody_i = (melody_i + 1) % MELODY_LENGTH;
}










