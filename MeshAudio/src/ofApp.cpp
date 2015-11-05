#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    
    size = ofGetHeight();
    
    newMesh();
    soundSetup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    size = ofGetHeight();
    
    
//    if((int)ofGetElapsedTimef() % 10 == 0) {
//        cout<<"t"<<endl;
//    }
    
    uint64_t now = ofGetElapsedTimeMillis();
    
    if (now > (lastUpdate + interval) && smoothedVol > 0.01)
    {
        
        mesh.clear();
        newMesh();
        
        lastUpdate = now;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(255, 20);
    
    ofEnableAlphaBlending();
    
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2,0);
    ofRotate(ofGetElapsedTimef()*30, 0,1,0);
    
    mesh.draw();
    
    ofPopMatrix();
    
    
}

void ofApp::mousePressed(int x, int y, int button){
    mesh.clear();
    newMesh();
    
}

void ofApp::newMesh(){
    for (int i = 0; i < 150; i++){
        
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        
        mesh.addVertex(ofPoint(ofRandom(-size,size),ofRandom(-size,size),ofRandom(-size,size))); // make a new vertex
        mesh.addColor(ofColor(ofRandom(70),ofRandom(50),ofRandom(100), ofRandom(80)));  // add a color at that vertex
    }
}

void ofApp::soundSetup(){
    
    int bufferSize = 256;
    
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    int numCounted = 0;
    
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    curVol /= (float)numCounted;
    
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}

void ofApp::keyPressed  (int key){
    if (key == '1'){
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    }    if (key == '2'){
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    }    if (key == '3'){
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    }    if (key == '4'){
        mesh.setMode( OF_PRIMITIVE_LINES);
    }    if (key == '5'){
        mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    }    if (key == '6'){
        mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    }    if (key == '7'){
        mesh.setMode(OF_PRIMITIVE_POINTS);
    }
}
