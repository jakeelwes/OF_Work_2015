#include "ofApp.h"

float phase = TWO_PI; // separate u-noise from v-noise
float pollenMass = 0.8; // particle speed cap
float complexity = 3; // wind complexity
float timeSpeed = .02; // wind variation speed
float life = 10000;



ofPoint ofApp::getField(ofPoint position) {
    float normx = ofNormalize(position.x, 0, ofGetWidth());
    float normy = ofNormalize(position.y, 0, ofGetHeight());
    float u = ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
    float v = ofNoise(t - phase, normx * complexity - phase, normy * complexity + phase);
    return ofVec2f(u, v);
}

void ofApp::setup(){
    ofSetVerticalSync(true); // don't go too fast
    ofEnableAlphaBlending();
    
    
    vidGrabber.setup(320, 240);
    vidGrabber.setVerbose(true);
    
    int pixelCount = vidGrabber.getWidth()*vidGrabber.getHeight();
    
    
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    gui->addSlider("Complexity", 0, 20);
    gui->addSlider("Pollen Mass", 0, 2);
    gui->addSlider("Life", 1, 20);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->setOpacity(0.2);
    gui->addFooter();


    // draw the points into an ofMesh that is drawn as bunch of points
    life = 10000;
    
    cloud.clear();
    cloud.setMode(OF_PRIMITIVE_POINTS);
}

void ofApp::update(){
    
    vidGrabber.update();
    int randomPixel = ofRandom(pixelCount);
    col = ofFloatColor(vidGrabber.getPixels()[randomPixel*3]/255.f,                  // r
                       vidGrabber.getPixels()[randomPixel*3+1]/255.f,			// g
                       vidGrabber.getPixels()[randomPixel*3+2]/255.f, ofRandom(10));          // b
    
    
    width = ofGetWidth(), height = ofGetHeight();

    t = ofGetFrameNum() * timeSpeed;
    
    for(int i = 0; i < points.size(); i++) {
        float x = points[i].x; float y = points[i].y;
        
        ofPoint field = getField(points[i]); // get the field at this position
        // use the strength of the field to determine a speed to move
        // the speed is changing over time and velocity-space as well
        float speed = (1 + ofNoise(t, field.x, field.y)) / pollenMass;
        
        x += ofLerp(-speed, speed, field.x);
        y += ofLerp(-speed, speed, field.y);
        

        points[i].x = x;
        points[i].y = y;
        // add the current point to our collection of drawn points
        cloud.addVertex(ofVec2f(x, y));
        cloud.addColor(col);
        
        
        if(points.size() > life){
            points.erase(points.begin());
        }
//        if(cloud.getNumVertices() > life){   //_CANT GET TO WORK NICELY
//            cloud.removeVertex(0);
//        }
    }
}

void ofApp::draw(){
    
    ofBackgroundGradient(255, 100);
    
    cloud.draw();

}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e){
    if (e.target->is("Complexity")) complexity = e.target->getValue();
    if (e.target->is("Pollen Mass")) pollenMass = e.target->getValue();
    if (e.target->is("Life")) {
        life = e.target->getValue();
        if(e.target->getValue() == 20){
            life = 100000;
        }
    }
}

void ofApp::mouseMoved(int x, int y) {
    ofPoint point = ofPoint(ofGetMouseX(),ofGetMouseY());
    points.push_back(point);
}
