#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>


AudioInputI2S            i2s1;
AudioEffectDistortion2   distortion;
AudioEffectChorus2       chorus;
AudioEffectPhaser        phaser;
AudioMixer4              mixer1;
AudioEffectStereo        stereo;
AudioOutputI2S           i2s2;
AudioConnection          patchCord1(i2s1, 0, distortion, 0);
AudioConnection          patchCord2(i2s1, 0, chorus, 0);
AudioConnection          patchCord3(i2s1, 0, phaser, 0);
AudioConnection          patchCord5(distortion, 0, mixer1, 0);
AudioConnection          patchCord6(chorus, 0, mixer1, 1);
AudioConnection          patchCord7(phaser, 0, mixer1, 2);
AudioConnection          patchCord4(i2s1, 0, mixer1, 3);
AudioConnection          patchCord8(mixer1, 0, stereo, 0);
AudioConnection          patchCord14(stereo, 0, i2s2, 0);
AudioConnection          patchCord15(mixer1, 0, i2s2, 1);



const int myInput = AUDIO_INPUT_LINEIN;
AudioControlSGTL5000 audioShield;



enum effects1{DISTORTION, CHORUS, PHASER, CLEAN1};
enum effects2{STEREO, CLEAN2};
String rc, c1, c2, c3, c4, c5;
float g1, g2, g3, g4, g5;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(300);

  // allocate memory for the audio library
  AudioMemory(8);
  audioShield.enable();
  audioShield.volume(0.65);
  audioShield.inputSelect(myInput);

  mixer1.gain(DISTORTION, 0);
  mixer1.gain(CHORUS, 0);
  mixer1.gain(PHASER, 0);
  mixer1.gain(CLEAN1, 1);

  chorus.changeNum(2);
  phaser.begin(220);
  stereo.begin();
  stereo.mix(0.5);
}

void loop() {
  
  if(Serial.available() > 0){
    
    //type in form <0.00,0.00,0.00,0.00,0.00>
    //note: <distortion, chorus, phasor, stereo, clean>
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
    c5 = rc.substring(21,25);
    g5 = c5.toFloat();

    if(g1 >= 0 && g1 <= 1){
      mixer1.gain(DISTORTION, g1);
      Serial.print("Updated distortion to ");
      Serial.println(g1);
    }
    if(g2 >= 0 && g2 <= 1){
      mixer1.gain(CHORUS, g2);
      //adaptive parameter: num voices
      Serial.print("Updated chorus to ");
      Serial.println(g2);
    }
    if(g3 >= 0 && g3 <= 1){
      mixer1.gain(PHASER, g3);
      //phaser.changeDelay((g3 * 1103 + 220)); //adaptive parameter: 220 to 1323
      Serial.print("Updated phaser to ");
      Serial.println(g3);
    }
    if(g4 >= 0 && g4 <= 1){
      stereo.mix(g4); //change amount of stereo spread
      Serial.print("Updated stereo to ");
      Serial.println(g4);
    }
    if(g5 >= 0 && g5 <= 1){
      mixer1.gain(CLEAN1, g5);
      Serial.print("Updated clean to ");
      Serial.println(g5);
    }
  }
}
