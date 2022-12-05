#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=163,283
AudioEffectReverb        reverb1;        //xy=415.00000762939453,250.00000190734863
AudioEffectChorus        chorus1;        //xy=416,191
AudioEffectWaveshaper    waveshape1;     //xy=418,115
AudioEffectBitcrusher    bitcrusher1;    //xy=427,328
AudioMixer4              mixer1;         //xy=723,276
AudioOutputI2S           i2s2;           //xy=948,274
AudioConnection          patchCord1(i2s1, 0, waveshape1, 0);
AudioConnection          patchCord2(i2s1, 0, chorus1, 0);
AudioConnection          patchCord3(i2s1, 0, reverb1, 0);
AudioConnection          patchCord4(i2s1, 0, bitcrusher1, 0);
AudioConnection          patchCord5(reverb1, 0, mixer1, 2);
AudioConnection          patchCord6(chorus1, 0, mixer1, 1);
AudioConnection          patchCord7(waveshape1, 0, mixer1, 0);
AudioConnection          patchCord8(bitcrusher1, 0, mixer1, 3);
AudioConnection          patchCord9(mixer1, 0, i2s2, 0);
AudioConnection          patchCord10(mixer1, 0, i2s2, 1);
// GUItool: end automatically generated code

const int myInput = AUDIO_INPUT_LINEIN;
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
short delayline[CHORUS_DELAY_LENGTH];
AudioControlSGTL5000 audioShield;

enum effects{WAVESHAPE, CHORUS, REVERB, BITCRUSH};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(300);

  // allocate memory for the audio library
  AudioMemory(8);
  audioShield.enable();
  audioShield.volume(0.9);
  audioShield.inputSelect(myInput);

  float x[33] = {-1,-1,-1,-1,-1,-1,-0.995,-0.967,-0.917,-0.842,-0.745,-0.625,-0.5,-0.375,-0.25,-0.125,0,1.25,0.25,0.375,0.5,0.625,0.745,0.842,0.917,0.967,0.995,1,1,1,1,1,1};
  waveshape1.shape(x, 33);
  
  reverb1.reverbTime(3);
  
  chorus1.begin(delayline, CHORUS_DELAY_LENGTH, 3);
  
  bitcrusher1.bits(4);
  bitcrusher1.sampleRate(44100);
  
  mixer1.gain(WAVESHAPE, 0);
  mixer1.gain(CHORUS, 0);
  mixer1.gain(REVERB, 1);
  mixer1.gain(BITCRUSH, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  String rc;
  String c1;
  String c2;
  String c3;
  String c4;
  float g1;
  float g2;
  float g3;
  float g4;

  if(Serial.available() > 0){
    
    //type in form <0.00,0.00,0.00,0.00>
    //note: <waveshape, chorus, reverb, bitcrusher>
    rc = Serial.readString();
    Serial.println(rc);
    
    c1 = rc.substring(1,5);
    g1 = c1.toFloat();
    c2 = rc.substring(6,10);
    g2 = c2.toFloat();
    c3 = rc.substring(11,15);
    g3 = c3.toFloat();
    c4 = rc.substring(16,20);
    g4 = c4.toFloat();

    if(g1 >= 0 && g1 <= 1){
      mixer1.gain(WAVESHAPE, g1);
      Serial.print("Updated g1 to ");
      Serial.println(g1);
    }
    if(g2 >= 0 && g2 <= 1){
      mixer1.gain(CHORUS, g2);
      Serial.print("Updated g2 to ");
      Serial.println(g2);
    }
    if(g3 >= 0 && g3 <= 1){
      mixer1.gain(REVERB, g3);
      Serial.print("Updated g3 to ");
      Serial.println(g3);
    }
    if(g4 >= 0 && g4 <= 1){
      mixer1.gain(BITCRUSH, g4);
      Serial.print("Updated g4 to ");
      Serial.println(g4);
    }
  }
}
