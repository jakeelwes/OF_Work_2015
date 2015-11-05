#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    
#ifdef TARGET_OPENGLES
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA );
    ofLogWarning("ofApp") << "GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";
#else
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);
#endif
    
    
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofEnableAlphaBlending();
    fbo.begin();
    
    
    if( ofGetKeyPressed('c') ){
        ofClear(255,255,255, 0);
    }
    
    fadeAmnt = 2;
    
    
    ofFill();
    ofSetColor(255,255,255, fadeAmnt);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    
    ofNoFill();
    
    ofSetColor(255,255,255);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2,0);
    ofRotate(ofGetElapsedTimef()*30, 1,0,0.5);
    ofDrawBox(0,0,0,800-ofGetElapsedTimef());
    ofPopMatrix();
    
    ofSetColor(255,255,255);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2,0);
    ofRotate(ofGetElapsedTimef()*30, -1,0,0.5);
    ofDrawBox(0,0,0,ofGetElapsedTimef());
    ofPopMatrix();
    
    
    
    
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255,255,255);

    
    fbo.draw(0,0);
    
}