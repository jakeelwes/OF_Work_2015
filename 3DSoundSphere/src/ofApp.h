#pragma once

#include "ofMain.h"
#include "fft.h"

#define BUFFER_SIZE 256
#define NUM_WINDOWS 80


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void keyPressed(int key);

    ofSoundPlayer sound;

    float * fftSmoothed;
    int nBandsToGet;
    
    void audioInSetup();
    void soundFileSetup();
    bool play;
    
    //audioIn
    
    void audioReceived 	(float * input, int bufferSize, int nChannels);
    
    float * left;
    float * right;
    int 	bufferCounter;
    fft		myfft;
    
    float magnitude[BUFFER_SIZE];
    float phase[BUFFER_SIZE];
    float power[BUFFER_SIZE];
    
    float freq[NUM_WINDOWS][BUFFER_SIZE/2];
    float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];

};
