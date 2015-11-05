#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();


    ofVideoGrabber cam;
    ofxCvColorImage cvImgColor;
    ofxCvGrayscaleImage cvImgGrayscale;
    ofxCvContourFinder contourFinder;
    vector<ofPolyline> polylines, smoothed, resampled;
    int camWidth, camHeight;
    
    int threshold;
    
    ofFbo fbo;
    int fadeAmnt;
};
