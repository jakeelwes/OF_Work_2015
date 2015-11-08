#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed  (int key);
    
    ofVideoGrabber vidGrabber;
    
    int vidHeight;
    int vidWidth;
    
    int pixelCount;
    
    int pixelTarget;
    
    bool randomPixel, noisePixel;
    
    float time, noiset, mouseInput;
    
    ofFloatColor col, averagedCol;
    
    ofPoint getField(ofPoint position);
    ofPoint center;
    
};
