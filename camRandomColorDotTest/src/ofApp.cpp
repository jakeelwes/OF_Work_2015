#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    vidWidth = 320;
    vidHeight = 240;
    
    vidGrabber.setup(vidWidth, vidHeight);
    vidGrabber.setVerbose(true);
    vidGrabber.setDesiredFrameRate(60);

    
    ofSetBackgroundColor(255);
    
//    pixelCount = vidGrabber.getWidth()*vidGrabber.getHeight();
    pixelCount = vidHeight*vidWidth;
    
    ofSetVerticalSync(true);

    pixelTarget = pixelCount/2 + vidWidth/2;
    center = ofPoint(160,120);

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    noiset = ofGetFrameNum() * .02;

    vidGrabber.update();
    
    if(randomPixel == true){
        pixelTarget = ofRandom(pixelCount);
    }
    
    if(noisePixel == true){
        ofPoint field = getField(center);
        float speed = (1 + ofNoise(noiset, field.x, field.y)) / 0.8;
        
        center.x += ofLerp(-speed, speed, field.x);
        center.y += ofLerp(-speed, speed, field.y);
        
        //collisions
        if(center.x < 0){
            center.x = vidWidth;
        }
        if(center.x > vidWidth){
            center.x = 0;
        }
        if(center.y < 0){
            center.y = vidHeight;
        }
        if(center.y > vidHeight){
            center.y = 0;
        }
        
        cout<<(int)(center.x+0.5)<<endl;
        cout<<(int)(center.y+0.5)<<endl;
        
        pixelTarget = (int)(center.x+0.5) + vidWidth*(int)(center.y+0.5);
        
    }
    
    if(mouseInput == true){
        
        pixelTarget = (ofGetMouseX() + vidWidth*ofGetMouseY()) % pixelCount;
        
    }
    
    col = ofFloatColor(vidGrabber.getPixels()[pixelTarget*3]/255.f,
                       vidGrabber.getPixels()[pixelTarget*3+1]/255.f,
                       vidGrabber.getPixels()[pixelTarget*3+2]/255.f);
    
    
    // take colour average of three pixels to reduce noise/anomolys
    averagedCol = ofFloatColor((vidGrabber.getPixels()[pixelTarget*3-3]/255.f
                               + vidGrabber.getPixels()[pixelTarget*3]/255.f
                               + vidGrabber.getPixels()[pixelTarget*3+3]/255.f) /3,
                               (vidGrabber.getPixels()[pixelTarget*3-3+1]/255.f
                                + vidGrabber.getPixels()[pixelTarget*3+1]/255.f
                                + vidGrabber.getPixels()[pixelTarget*3+3+1]/255.f) /3,
                               (vidGrabber.getPixels()[pixelTarget*3-3+2]/255.f
                                + vidGrabber.getPixels()[pixelTarget*3+2]/255.f
                                + vidGrabber.getPixels()[pixelTarget*3+3+2]/255.f) /3);
    
    cout<<pixelTarget<<endl;
}

//--------------------------------------------------------------
void ofApp::draw(){


    ofSetBackgroundAuto( false );
    
    ofFill();
    ofSetColor(averagedCol);
    
    time += 0.5;

    ofDrawRectangle(0, ofGetHeight()-time, ofGetWidth(), 1);
    
    if(time>ofGetHeight()){
        time = 0;
        ofSetColor(255,190);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    }
    
    //view video
    
    ofSetHexColor(0xffffff); // wierd colours if not

    vidGrabber.draw(5, 5);
    ofSetColor(255,190);
    ofDrawRectangle(0, 0, vidWidth + 10, vidHeight + 10);
    
    ofSetColor(averagedCol);
    ofDrawCircle((pixelTarget % vidWidth)+5, (pixelTarget/vidWidth)+5, 5);
    
    ofSetHexColor(0x000000);
    ofDrawBitmapString("press '1' for center pixel",10,280);
    ofDrawBitmapString("press '2' for static random pixel",10,300);
    ofDrawBitmapString("press '3' for moving random pixel",10,320);
    ofDrawBitmapString("press '4' for perlin noise pixel",10,340);
    ofDrawBitmapString("press '5' for mouse input pixel",10,360);
    
}

void ofApp::keyPressed  (int key){
    randomPixel = false;
    noisePixel = false;
    mouseInput = false;
    
    switch(key){
        case '1':
            pixelTarget = pixelCount/2 + vidWidth/2;
        break;
        case '2':
            pixelTarget = ofRandom(pixelCount);
        break;
        case '3':
            randomPixel = true;
        break;
        case '4':
            noisePixel = true;
        break;
        case '5':
            mouseInput = true;
        break;
    }
}

ofPoint ofApp::getField(ofPoint position) {
    float phase = TWO_PI;
    
    float normx = ofNormalize(position.x, 0, vidWidth);
    float normy = ofNormalize(position.y, 0, vidHeight);
    float u = ofNoise(noiset + phase, normx * 3 + phase, normy * 3 + phase);
    float v = ofNoise(noiset - phase, normx * 3 - phase, normy * 3 + phase);
    return ofVec2f(u, v);
}
