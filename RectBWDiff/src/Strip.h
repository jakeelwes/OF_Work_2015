#pragma once

#include "ofMain.h"

class Strip : public ofBaseApp{
public:
    Strip();
    
    void update();
    
    float mapR, mapL;
    
    float t, speed;
    
    ofColor colour;
    
};