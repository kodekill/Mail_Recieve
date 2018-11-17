#include <Wire.h>
#include <SPI.h>
#include "RF24.h"  //Library for the transciever
#include <Adafruit_NeoPixel.h>
#include "TMRpcm.h"
#include "SD.h"
#include "SPI.h"

#define SD_ChipSelectPin 10
#define AUDIO "mail.wav"
#define PIN 2
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

RF24 radio(7,8);     // clock and data pins for the transciever
TMRpcm tmrpcm;

const byte rxAddr[6] = "00001";
char text;
bool yes;

void setup() {
  tmrpcm.speakerPin=9; //Should be 9
  Serial.begin(9600);
  Serial.println("Starting....");
  if(!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("SD fail");
    return;
  }

  pinMode(SD_ChipSelectPin, OUTPUT);
  pixel.begin();
  pixel.show(); // Initialize all pixels to 'off'
  
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
  
  tmrpcm.setVolume(6);
}

void loop() {
  //RedPixel();
  readCommunication();
}



void readCommunication(){
  if (radio.available()){ // Check for incoming data from transmitter
    while (radio.available()){  // While there is data ready
      char text[32] = {0};
      radio.read(&text, sizeof(text)); // Get the data payload (You must have defined that already!)
      yes = true;
    }
      
    if (yes == true){
      Serial.print("dataReceived = ");
      Serial.println(text);
        GreenPixel();
        tmrpcm.play(AUDIO);
        delay(500);
    }
   
  }
  yes = false;
  OffPixel();
}









void RedPixel(){
  pixel.setPixelColor(0, pixel.Color(25,0,0));
  pixel.show();
}

void BluePixel(){
  pixel.setPixelColor(0, pixel.Color(0,0,25));
  pixel.show();
}

void YellowPixel(){
  pixel.setPixelColor(0, pixel.Color(25,20,0));
  pixel.show();
}

void GreenPixel(){
  pixel.setPixelColor(0, pixel.Color(0,25,0));
  pixel.show();
}

void OffPixel(){
  pixel.setPixelColor(0, pixel.Color(0,0,0));
  pixel.show();
}
