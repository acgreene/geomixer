/*
  About: 
    Plays a wav file from an SD card to I2S out. 
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// for use with the Teensy Audio Shield
#define SDCARD_SDCS_PIN  10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

AudioPlaySdWav           playSdWav1;     
AudioOutputI2S           i2s1;        
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;    

void setup() {
  // set the data rate in bits per second (baud) for serial data transmission
  Serial.begin(9600);

  // allocate 8 blocks of memory for all audio connections
  // https://www.pjrc.com/teensy/td_libs_AudioConnection.html
  AudioMemory(8);

  // start the SGTL5000. this is the processor on the audio shield
  sgt15000_1.enable();

  // set the headphone volume level => range is 0 to 1.0
  sgt15000_1.volume(0.5);

  // for info on audio shield pins: https://www.pjrc.com/store/teensy3_audio.html
  // read SD card audio data through pin 11
  SPI.setMOSI(SDCARD_MOSI_PIN); 

  // set clock to pin 13
  SPI.setSCK(SDCARD_SCK_PIN); 

  // error handling for accessing the SD card
  if (!(SD.begin(SDCARD_SDCS_PIN))) {
    while(1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}

void loop() {
  wavFile = ""; // TO DO: put wav file on SD card and the filename here
  play(wavFile);
}

void play(string filename) {
  
  if (playSdWav1.isPlaying() == false) {
    Serial.println("Start playing");
    
    playSdWav1.play(filename);
    
    delay(10); // wait for library to parse WAV info
  }
  
}
