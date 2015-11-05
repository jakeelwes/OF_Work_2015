#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    vidGrabber.setup(320, 240);
    vidGrabber.setVerbose(true);
    
    int pixelCount = vidGrabber.getWidth()*vidGrabber.getHeight();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
//    for (int i=0; i<vidGrabber.getWidth()*vidGrabber.getHeight(); i++){
//        
//        ofFloatColor pixelColour(vidGrabber.getPixels()[i*3]/255.f,				// r
//                                 vidGrabber.getPixels()[i*3+1]/255.f,			// g
//                                 vidGrabber.getPixels()[i*3+2]/255.f);          // b
//    }
    int randomPixel = ofRandom(pixelCount);
    col = ofFloatColor(vidGrabber.getPixels()[randomPixel*3]/255.f,                  // r
                       vidGrabber.getPixels()[randomPixel*3+1]/255.f,			// g
                       vidGrabber.getPixels()[randomPixel*3+2]/255.f);          // b
    
}

//--------------------------------------------------------------
void ofApp::draw(){


    ofSetBackgroundAuto( false );
    
    ofFill();
    ofSetColor(col);
    
    ofDrawCircle(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),10,10);
    
}
