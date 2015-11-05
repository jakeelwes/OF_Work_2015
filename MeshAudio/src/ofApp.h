#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    void mousePressed(int x, int y, int button);
    void newMesh();
    void keyPressed  (int key);


    
    ofMesh mesh;

    int size;
    
    
    void soundSetup();

    void audioIn(float * input, int bufferSize, int nChannels);
    
    ofSoundStream soundStream;
    
    std::vector <float> left;
    std::vector <float> right;
    
    int bufferCounter;
    int drawCounter;
    
    float smoothedVol;

    uint64_t lastUpdate = 0;
    uint64_t interval = 100;
    
};
