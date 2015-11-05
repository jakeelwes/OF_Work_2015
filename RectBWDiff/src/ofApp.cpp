#include "ofApp.h"

void ofApp::setup(){
    
    ofSetBackgroundColor(255);
    
    Strip strip;
    strip.t = ofRandom(1000);
    strip.speed = (ofRandom(0.01));
    strips.push_back(strip);
}

void ofApp::update(){
    
    for(std::size_t i = 0; i < strips.size(); i++) {
        strips[i].update();
    }
}

void ofApp::draw(){
    
    
//    sourceFactor = GL_DST_COLOR, destinationFactr = GL_ZERO, blendEquation = GL_FUNC_ADD (default);

    ofEnableAlphaBlending();

    glEnable(GL_BLEND);
    glBlendEquation(GL_INVERT_OVG_NV);
    glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    
    
    
//    ofEnableBlendMode(GL_FUNC_REVERSE_SUBTRACT);
    
    ofFill();
    for(std::size_t i = 0; i < strips.size(); i++) {
        
        if(colour){
            ofSetColor(strips[i].colour);
        } else {
            ofSetColor(0);
        }
        
        ofBeginShape();
        ofVertex(strips[i].mapR, 0);
        ofVertex(strips[i].mapR, ofGetHeight());
        ofVertex(strips[i].mapL, ofGetHeight());
        ofVertex(strips[i].mapL, 0);
        ofEndShape();
    }
    
}

void ofApp::mousePressed(int x, int y, int button) {
    
    Strip strip;
    strip.t = ofRandom(1000);
    strip.speed = (ofRandom(0.01));
    strips.push_back(strip);
}

void ofApp::keyPressed(int key){
    
    if (key == 'c'){
        colour = !colour;
    }
    
}
