# ArduinoProgrammableSoundGenerator
An Arduino NES inspired multichannel sounds generator library.
# How to use it
Plug a speaker to pin 3, then init the sound generator in the setup function.
```
#include "APSG.h"

void setup()
{
  init_SID();
}
```
Play a 440Hz triangle wave for 1 second, then stop.
```
triangle.note = N_A4;
delay(1000);
triangle.note = N_NOP;
```
Play 2 tones at the same time.
```
squares[0].note = N_A4;
squares[1].note = N_A5;
```
Set volume for specific channel to maximum.
```
noise.volume = 15;
```
Sweep a channel down to low frequency.
```
sawtooth.sweep_direction = SWEEP_DOWN;
sawtooth.sweep_shift = 1;
sawtooth.sweep_speed = SWEEP_SPEED(8);
```