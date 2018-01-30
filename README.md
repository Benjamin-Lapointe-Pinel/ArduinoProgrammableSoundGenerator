# ArduinoProgrammableSoundGenerator
An Arduino NES inspired multichannel sounds generator library.
# How to use it
Plug a speaker to pin 3, then init the sound generator in the setup function.
```
void setup()
{
  init_SID();
}
```
```
triangle.note = N_A4;
delay(1000);
triangle.note = N_NOP;
```
Play a 440Hz triangle wave for 1 second, then stop.
```
squares[0].note = N_A4;
squares[1].note = N_A5;
```
Play 2 tones at the same time.
```
noise.volume = 15;
```
Set volume for specific channel to maximum.
```
sawtooth.sweep_direction = SWEEP_DOWN;
sawtooth.sweep_shift = 1;
sawtooth.sweep_speed = SWEEP_SPEED(8);
```
Sweep a channel down to low frequency.