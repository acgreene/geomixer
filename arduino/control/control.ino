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

// teensy LED pin config
const int ledPin = 13;
int ledState = LOW;


enum effects1{DISTORTION, CHORUS, PHASER, CLEAN1};
enum effects2{STEREO, CLEAN2};
String rc, s;
char tags[3];
float in_mixes[3];
float mixes[5];
int i;
float val;
enum locs{D, C, P, S, U};



void setup() {
  pinMode(ledPin, OUTPUT);
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
  stereo.mix(0);
}

void blinkLED() {
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }
  digitalWrite(ledPin, ledState);
}

void run_distortion(float f) {
  if(f >= 0 && f <= 1){
      mixer1.gain(DISTORTION, f);
      Serial.print("Updated distortion to ");
      Serial.println(f);
  }
}

void run_chorus(float f) {
  if(f >= 0 && f <= 1){
      mixer1.gain(CHORUS, f);
      //adaptive parameter: num voices?
      Serial.print("Updated chorus to ");
      Serial.println(f);
    }
}

void run_phaser(float f) {
  if(f >= 0 && f <= 1){
      mixer1.gain(PHASER, f);
      //phaser.changeDelay((f * 1103 + 220)); //adaptive parameter: 220 to 1323?
      Serial.print("Updated phaser to ");
      Serial.println(f);
    }
}

void run_stereo(float f) {
  if(f >= 0 && f <= 1){
      stereo.mix(f); //change amount of stereo spread
      Serial.print("Updated stereo to ");
      Serial.println(f);
      if(mixes[U] == 0 && f > 0){
        mixer1.gain(CLEAN1, f);
        Serial.println("(and clean as well) ");
      }
    }
}

void run_clean(float f) {
  if(f >= 0 && f <= 1){
      if(mixes[S] > 0){
        val = f + mixes[S];
        mixer1.gain(CLEAN1, val);
        Serial.print("Updated clean to ");
        Serial.println(val);
      }else{
        mixer1.gain(CLEAN1, f);
        Serial.print("Updated clean to ");
        Serial.println(f);
      }
    }
}



void loop() {
  if(Serial.available() > 0){
    rc = Serial.readString();
    blinkLED();
    Serial.println(rc);

    //distortion: D, chorus: C, phasor: P, stereo: S, clean: U
    //c 0.000, c 0.000, c 0.000,
    
    tags[0] = rc.charAt(0); //parse input
    s = rc.substring(2,7);
    in_mixes[0] = s.toFloat();
    
    tags[1] = rc.charAt(9);
    s = rc.substring(11,16);
    in_mixes[1] = s.toFloat();
    
    tags[2] = rc.charAt(18);
    s = rc.substring(20,25);
    in_mixes[2] = s.toFloat();

    for(i = 0; i < 5; i++){ //reset mixes to 0
      mixes[i] = 0;
    }
    
    for(i = 0; i < 3; i++){ //get mixes for each effect that are non-zero
      switch (tags[i]) {
        case 'D': mixes[D] = in_mixes[i]; break;
        case 'C': mixes[C] = in_mixes[i]; break;
        case 'P': mixes[P] = in_mixes[i]; break;
        case 'S': mixes[S] = in_mixes[i]; break;
        case 'U': mixes[U] = in_mixes[i]; break;
      }
    }

    run_distortion(mixes[D]);
    run_chorus(mixes[C]);
    run_phaser(mixes[P]);
    run_stereo(mixes[S]);
    run_clean(mixes[U]);
  }
}
