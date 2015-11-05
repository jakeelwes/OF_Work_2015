#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
#ifdef TARGET_OPENGLES
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA );
    ofLogWarning("ofApp") << "GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";
#else
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);
#endif
    
    threshold = 100;
    
    camWidth = 640;
    camHeight = 480;
    
    cam.setup(640, 480);
    cvImgColor.allocate(camWidth, camHeight);
    cvImgGrayscale.allocate(camWidth, camHeight);
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    cam.update();
    if(cam.isFrameNew()) {
        cam.update();
        cvImgColor.setFromPixels(cam.getPixels().getData(), camWidth, camHeight);
        cvImgGrayscale.setFromColorImage(cvImgColor);
        cvImgGrayscale.threshold(threshold, ofGetKeyPressed());
        contourFinder.findContours(cvImgGrayscale, 64 * 64, camWidth * camHeight, 5, false, true);
        
        polylines.clear();
        smoothed.clear();
        resampled.clear();

        
        ofPoint target;
        target.set(mouseX, mouseY);
        
        for(unsigned int i = 0; i < contourFinder.blobs.size(); i++) {
            ofPolyline cur;
            // add all the current vertices to cur polyline
            cur.addVertices(contourFinder.blobs[i].pts);
            cur.setClosed(true);
            
            // add the cur polyline to all these vector<ofPolyline>
            polylines.push_back(cur);
            smoothed.push_back(cur.getSmoothed(8));
            resampled.push_back(cur.getResampledByCount(100).getSmoothed(8));
            
            
            unsigned int index;

        }
    }
}

//--------------------------------------------------------------
void drawWithNormals(const ofPolyline& polyline) {
    for(int i=0; i< (int) polyline.size(); i++ ) {
        bool repeatNext = i == (int)polyline.size() - 1;
        
        const ofPoint& cur = polyline[i];
        const ofPoint& next = repeatNext ? polyline[0] : polyline[i + 1];
        
        float angle = atan2f(next.y - cur.y, next.x - cur.x) * RAD_TO_DEG;
        float distance = cur.distance(next);
        
        if(repeatNext) {
            ofSetColor(0);
        }
        glPushMatrix();
        glTranslatef(cur.x, cur.y, 0);
        ofRotate(angle);
        ofDrawLine(0, 0, distance, 0);
        glPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(255);
    ofEnableAntiAliasing();

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
    
    ofSetLineWidth(5);
    ofSetColor(0);
    
    ofPushMatrix();
    ofScale(2, 2);
    for(unsigned int i = 0; i < polylines.size(); i++) {
        drawWithNormals(smoothed[i]);
        
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofScale(2, -2);
    ofTranslate(0,-480);
    for(unsigned int i = 0; i < polylines.size(); i++) {
        drawWithNormals(resampled[i]);
    }
    
    ofPopMatrix();
    
    fbo.end();
    
    ofSetColor(255,255,255);
    fbo.draw(0,0);


    
}





