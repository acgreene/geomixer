#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>

AudioInputI2S            i2s1;
AudioEffectMyReverb      reverb1;
AudioOutputI2S           i2s2;
AudioConnection          patchCord1(i2s1, 0, reverb1, 0);
AudioConnection          patchCord2(reverb1, 0, i2s2, 0);

const int myInput = AUDIO_INPUT_LINEIN;
AudioControlSGTL5000 audioShield;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(300);

  AudioMemory(8);
  audioShield.enable();
  audioShield.volume(0.9);
  audioShield.inputSelect(myInput);

  reverb1.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
