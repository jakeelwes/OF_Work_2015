#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    void mouseMoved(int x, int y);
    
        ofPoint getField(ofPoint position);
    
    ofxDatGui* gui;
    void onSliderEvent(ofxDatGuiSliderEvent e);
    
    float t, width, height;
    
    vector<ofPoint> points;
    ofMesh cloud;
    
    
    ofVideoGrabber vidGrabber;
    
    int pixelCount;
    ofFloatColor col;
};
