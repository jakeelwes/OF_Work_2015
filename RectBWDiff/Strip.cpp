#include "Strip.h"

Strip::Strip(){
    colour = ofColor(ofRandom(255),0,ofRandom(255),ofRandom(200));
}

void Strip::update(){
    
    t += speed;
    
    ofSeedRandom();
    
    float r = ofNoise(t);
    mapL = ofMap(r,0,1,-ofGetWidth(),ofGetWidth()*2);
    
    float l = ofNoise(t+1000);
    mapR = ofMap(l,0,1,-ofGetWidth(),ofGetWidth()*2);
    
}