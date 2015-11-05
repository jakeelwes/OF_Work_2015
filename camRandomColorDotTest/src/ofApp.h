#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber vidGrabber;
    
    int pixelCount;
    ofFloatColor col;
};
