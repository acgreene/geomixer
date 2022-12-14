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


enum effects{DISTORTION, CHORUS, PHASER, CLEAN1};
String rc, s;
char tags[3];
float in_mixes[3];
float mixes[5];
int i;
float val;
bool on;
enum locs{D, C, P, S, U};

//elapsedMillis timeTest; //for testing

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  delay(300);
  
  // allocate memory for the audio library
  AudioMemory(8);
  audioShield.enable();
  audioShield.volume(0.5);
  audioShield.inputSelect(myInput);
  
  mixer1.gain(DISTORTION, 0);
  mixer1.gain(CHORUS, 0);
  mixer1.gain(PHASER, 0);
  mixer1.gain(CLEAN1, 1);
  
  chorus.changeNum(0);
  phaser.begin(300);
  distortion.begin();
  stereo.mix(0);
}

void blinkLED() {
  if (ledState == LOW) {
    ledState = HIGH;
  } 
  else {
    ledState = LOW;
  }
  digitalWrite(ledPin, ledState);
}

void run_distortion(float f) {
  on = distortion.getOn();
  if (f == 0 && on) {
    distortion.setOn(false);
    mixer1.gain(DISTORTION, f);
  } 
  else if (f > 0 && f <= 1) {
    if(!on){
      distortion.setOn(true);
    }
    mixer1.gain(DISTORTION, f);
    distortion.change_output_scalar(f);
  }
}

void run_chorus(float f) {
  on = chorus.getOn();
  if (f == 0 && on) {
    chorus.setOn(false);
    mixer1.gain(CHORUS, f);
    chorus.changeNum(0);
  } 
  else if (f > 0 && f <= 1) {
    if(!on){
      chorus.setOn(true);
    }
    mixer1.gain(CHORUS, f*1.5);
    if(f <= .33){
      chorus.changeNum(1);
    }
    else if(f > .33 && f <= .66){
      chorus.changeNum(2);
    }
    else{
      chorus.changeNum(3);
    }
  }
}

void run_phaser(float f) {
  on = phaser.getOn();
  if (f == 0 && on) {
    phaser.setOn(false);
    mixer1.gain(PHASER, f);
  } 
  else if (f > 0 && f <= 1) {
    if(!on){
      phaser.setOn(true);
    }
    phaser.changeDelay(300 + (1-f)*(1023));
    mixer1.gain(PHASER, f);
  }
}

void run_stereo(float f) {
  on = stereo.getOn();
  if (f <= 0 && on) {
    stereo.setOn(false);
    stereo.mix(f);
  } 
  else if (f > 0 && f <= 1) {
    if(!on){
      stereo.setOn(true);
    }
    stereo.mix(f);
    if(mixes[U] == 0){
      mixer1.gain(CLEAN1, f*0.9);
    }
  }
}

void run_clean(float f) {
  if (f >= 0 && f <= 1) {
    if (mixes[S] > 0) {
      val = f + mixes[S];
      mixer1.gain(CLEAN1, val);
    } else {
      mixer1.gain(CLEAN1, f);
    }
  }
}

void loop() {
  if (Serial.available() > 0) {
    //timeTest = 0;
    rc = Serial.readString();
    blinkLED();

    //distortion: D, chorus: C, phasor: P, stereo: S, clean: U
    //input format: c 0.000, c 0.000, c 0.000,
    
    tags[0] = rc.charAt(0); //parse input
    s = rc.substring(2,7);
    in_mixes[0] = s.toFloat();
    
    tags[1] = rc.charAt(9);
    s = rc.substring(11,16);
    in_mixes[1] = s.toFloat();
    
    tags[2] = rc.charAt(18);
    s = rc.substring(20,25);
    in_mixes[2] = s.toFloat();
    for (i = 0; i < 5; i++) { //reset mixes to 0
      mixes[i] = 0;
    }
    
    for (i = 0; i < 3; i++) { //get mixes for each effect that are non-zero
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
    //Serial.println(timeTest);
  }
}
