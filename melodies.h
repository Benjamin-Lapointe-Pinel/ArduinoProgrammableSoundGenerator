#ifndef MELODIES_H
#define MELODIES_H

#include "note.h"


/*
const static uint8_t MELODY_LENGTH = 32;
const static uint16_t melody[NUMBER_OF_CHANNELS][MELODY_LENGTH] PROGMEM =
{
  {N_C5, N_C5, N_C5, N_AS4, N_AS4, N_AS4, N_CS5, N_CS5, N_CS5, N_C5, N_C5, N_C5, N_AS4, N_AS4, N_C5, N_C5, N_C5, N_C5, N_C5, N_AS4, N_AS4, N_AS4, N_GS4, N_GS4, N_GS4, N_AS4, N_AS4, N_AS4, N_GS4, N_GS4, N_AS4, N_AS4},
  {N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_DS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4, N_CS4},
  {N_GS4, N_GS4, 0, N_GS4, N_GS4, N_GS4, N_GS4, N_GS4, N_GS4, N_GS4, N_GS4, N_GS4, 0, 0, N_GS4, N_G4, N_FS4, N_FS4, 0, N_FS4, N_FS4, N_FS4, N_FS4, N_FS4, 0, N_FS4, N_FS4, N_FS4, N_FS4, N_F4, N_FS4, N_G4}
};
*/

/*
const static uint8_t MELODY_LENGTH = 15;
const static uint16_t melody[NUMBER_OF_CHANNELS][MELODY_LENGTH] PROGMEM =
{
  {N_G4, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_D5, N_C5, N_NOP, N_NOP, N_NOP, N_NOP, N_NOP, N_NOP},
  {N_A4, N_D5, N_D5, N_D5, N_D5, N_C5, N_C5, N_B4, N_G4, N_C4, N_NOP, N_C4, N_C3, N_C3, N_C3},
  {N_G3, N_G3, N_G3, N_G3, N_G3, N_A3, N_A3, N_B3, N_C4, N_C4, N_G3, N_G3, N_C2, N_C2, N_C2},
  {},
  {},
};
*/


const static uint8_t MELODY_LENGTH = 64;
const static uint16_t melody[NUMBER_OF_CHANNELS][MELODY_LENGTH] PROGMEM =
{
  {N_D4, N_D4, N_D4, N_D4, N_D4, 0, N_D4, N_F4, N_AS4, N_AS4, N_AS4, N_AS4, N_A4, N_A4, N_A4, N_F4, N_G4, N_G4, N_G4, N_G4, N_G4, N_G4, N_F4, N_E4, N_F4, N_F4, N_E4, N_D4, N_E4, N_E4, N_D4, N_C4, N_G4, N_G4, N_G4, N_G4, N_G4, 0, N_G4, N_A4, N_AS4, N_AS4, N_AS4, N_AS4, N_A4, N_A4, N_A4, N_AS4, N_C5, N_C5, N_C5, N_C5, N_C5, N_C5, N_AS4, N_C5, N_D5, N_D5, N_C5, N_C5, N_AS4, N_AS4, N_A4, N_A4},
  {N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4, N_A4, N_AS4, N_A4, N_G4},
  {N_G3, 0, N_G3, N_G3, N_G3, 0, N_G3, N_G3, N_G3, 0, N_G3, N_G3, N_G3, 0, N_G3, N_G3, N_C3, 0, N_C3, N_C3, N_C3, 0, N_C3, N_C3, N_C3, 0, N_C3, N_C3, N_C3, 0, N_C3, N_C3, N_DS3, 0, N_DS3, N_DS3, N_DS3, 0, N_DS3, N_DS3, N_DS3, 0, N_DS3, N_DS3, N_DS3, 0, N_DS3, N_DS3, N_F3, 0, N_F3, N_F3, N_F3, 0, N_F3, N_F3, N_F3, 0, N_F3, N_F3, N_F3, 0, N_F3, N_F3},
  {},
  {N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3, N_E1, 0, N_DS3, N_DS3}
};


/*
const static uint8_t MELODY_LENGTH = 128;
const static uint16_t melody[NUMBER_OF_CHANNELS][MELODY_LENGTH] PROGMEM =
{
  {},
  {N_GS3, 0, N_GS3, 0, N_FS4, 0, N_GS3, 0, N_DS4, 0, N_GS3, 0, N_CS4, 0, N_GS3, 0, 0, 0, N_GS3, 0, N_FS4, 0, N_GS3, 0, N_DS4, 0, N_GS3, 0, N_CS4, 0, N_GS3, 0, N_GS3, 0, N_GS3, 0, N_FS4, 0, N_GS3, 0, N_DS4, 0, N_GS3, 0, N_CS4, 0, N_GS3, 0, 0, 0, N_GS3, 0, N_FS4, 0, N_GS3, 0, N_DS4, 0, N_GS3, 0, N_CS4, 0, N_GS3, 0, N_GS3, 0, N_GS3, 0, N_FS4, 0, N_GS3, 0, N_DS4, 0, N_GS3, 0, N_CS4, 0, N_GS3, 0, 0, 0, N_GS3, 0, N_FS4, 0, N_GS3, 0, N_DS4, 0, N_GS3, 0, N_CS4, 0, N_GS3, 0, N_GS3, 0, N_GS3, 0, N_FS4, 0, N_GS3, 0, N_DS4, 0, N_GS3, 0, N_CS4, 0, N_GS3, 0, 0, 0, N_GS3, 0, N_AS3, 0, N_GS3, 0, N_B4, 0, N_AS4, 0, N_GS4, 0, N_FS4, 0},
  {N_GS3, 0, N_GS3, 0, N_GS3, 0, N_GS3, 0, },
  {},
  {2000, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 0, 0, 2000, 0, 700, 0, 2000, 0, 2000, 0, 2000, 0, 700, 0, 2000, 0},
};
*/

/*
const static uint8_t MELODY_LENGTH = 12;
const static uint16_t melody[NUMBER_OF_CHANNELS][MELODY_LENGTH] PROGMEM =
{
  {N_G4, N_C5, N_E5, N_G5, N_C6, N_E6, N_G6, N_G6, N_G6, N_E6, N_E6, N_E6},
  {0, N_E4, N_G4, N_C5, N_E5, N_G5, N_C6, N_C6, N_C6, N_G5, N_G5, N_G5},
  {},
  {},
  {0, 0, 0, N_C5, N_E5, N_G5, N_E6, N_E6, N_E6, N_C6, N_C6, N_C6}
};
*/

/*
const static uint8_t MELODY_LENGTH = 7;
const static uint16_t melody[NUMBER_OF_CHANNELS][MELODY_LENGTH] PROGMEM =
{
  {N_C3, N_C4, N_A2, N_A3, N_AS2, N_AS3},
  {0, N_C3 + 1, N_C4 + 1, N_A2 + 1, N_A3 + 1, N_AS2 + 1, N_AS3 + 1},
  {},
  {},
  {N_C3 - 1, N_C4 - 1, N_A2 - 1, N_A3 - 1, N_AS2 - 1, N_AS3 - 1}
};
*/

/*
const static uint8_t MELODY_LENGTH = 50;
const static uint16_t melody[NUMBER_OF_CHANNELS][MELODY_LENGTH] PROGMEM =
{
  {0, 0, N_G4, N_G5, 0, N_F5, N_F5, N_F5, N_A4, N_AS4, 0, N_B4, N_B4, N_B4, N_B4, N_B4, N_B4, N_G5, N_G6, 0, 0, 0, 0, 0, 0, 0, N_E5, 0, 0, N_DS5, N_E5, N_E5, N_E5, N_E5, N_E5, N_DS5, N_E5, N_E5, N_E5, N_A4, 0, N_C5, N_C5, N_C5, N_C5},
  {N_G2, 0, N_B3, N_B4, 0, N_A4, N_A4, N_A4, N_C3, N_CS3, 0, N_D3, N_D3, N_D3, N_D3, N_D3, N_D3, 0, 0, 0, 0, 0, 0, 0, 0, 0, N_G3, 0, 0, N_G3, N_G3, N_G3, N_G3, N_G3, 0, N_G3, N_G3, N_G3, N_G3, N_F3, 0, N_E3, N_E3, N_E3, N_E3},
  {N_B3, 0, N_G3, N_D4, 0, N_C4, N_C4, N_C4, N_F3, N_FS3, 0, N_G3, N_G3, N_G3, N_G3, N_G3, N_G3, 0, 0, 0, 0, N_G3, 0, 0, 0, 0, 0, 0, 0, N_C3, N_E3, N_E3, N_E3, N_G3, N_G3, N_G3, 0, 0, 0, 0, 0, N_F3, N_A2, 0, N_A2, N_C3, N_C3, N_C3},
  {},
  {0, 0, 0, N_C1, 0, 0, 0, 0, 0, N_C1, 0, 0, 0, 0, 0, N_C1, 0, 0, 0, 0, 0, N_C1, 0, 0, N_C1, 0, 0, N_C1, 0, N_C1, 0, 0, 0, N_C1, 0, N_C1, N_C1, 0, 0, N_C1, 0, N_C1, 0, 0, 0, N_C1, 0, N_C1, N_C1}
};
*/

/*
const static uint8_t MELODY_LENGTH = 72;
const static uint16_t melody[NUMBER_OF_CHANNELS][MELODY_LENGTH] PROGMEM =
{
  
  {N_C4, 0, N_C4, N_D4, N_D4, N_D4, N_C4, N_C4, N_C4, N_F4, N_F4, N_F4, N_E4, N_E4, N_E4, N_E4, 0, 0, N_C4, 0, N_C4, N_D4, N_D4, N_D4, N_C4, N_C4, N_C4, N_G4, N_G4, N_G4, N_F4, N_F4, N_F4, N_F4, 0, 0, N_C4, 0, N_C4, N_C5, N_C5, N_C5, N_A4, N_A4, N_A4, N_F4, N_F4, N_F4, N_E4, N_E4, N_E4, N_D4, N_D4, N_D4, N_AS4, 0, N_AS4, N_A4, N_A4, N_A4, N_F4, N_F4, N_F4, N_G4, N_G4, N_G4, N_F4, N_F4, N_F4, N_F4, N_F4, N_F4},
  {},
  {0, 0, 0, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, N_C2, N_C2, N_C2, N_C2, N_C2, N_C2, N_C2, N_C2, 0, N_C2, N_C2, N_C2, N_C2, N_C2, N_C2, N_C2, N_C2, N_C2, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, 0, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, N_AS1, N_AS1, N_AS1, N_AS1, N_AS1, N_AS1, 0, 0, 0, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2, N_C2, N_C2, N_C2, N_F2, N_F2, N_F2, N_F2, N_F2, N_F2},
  {0, 0, 0, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_C3, N_C3, N_C3, N_C3, N_C3, N_C3, N_C3, N_C3, 0, N_C3, N_C3, N_C3, N_C3, N_C3, N_C3, N_C3, N_C3, N_C3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, 0, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS2, N_AS2, N_AS2, N_AS2, N_AS2, N_AS2, 0, 0, 0, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_C3, N_C3, N_C3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3},
  {0, 0, 0, N_C0, 0, 0, N_C4, 0, 0, N_C4, 0, 0, N_C2, 0, 0, N_C4, 0, 0, N_C4, 0, 0, N_C0, 0, 0, N_C4, 0, 0, N_C4, 0, 0, N_C2, 0, 0, N_C4, 0, 0, N_C4, 0, 0, N_C0, 0, 0, N_C4, 0, 0, N_C4, 0, 0, N_C2, 0, 0, N_C4, 0, 0, N_C4, 0, 0, N_C0, 0, 0, N_C4, 0, 0, N_C4, 0, 0, N_C2, N_C0, N_C0, N_C0, N_C0, N_C0}
};
*/

#endif
