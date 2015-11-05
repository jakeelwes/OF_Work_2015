#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    vidGrabber.setup(320, 240);
    vidGrabber.setVerbose(true);
    
    int width = vidGrabber.getWidth();
    int height = vidGrabber.getHeight();
    
    for (int y = 0; y < height; y++){
        for (int x = 0; x<width; x++){
            mesh.addVertex(ofPoint(x,y,0));
            mesh.addColor(ofColor(ofRandom(20),ofRandom(10),ofRandom(30), ofRandom(60)));
        }
    }
    extrusionAmount = 160;
    
    cam.setScale(1,-1,1);


}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    for (int i=0; i<vidGrabber.getWidth()*vidGrabber.getHeight(); i++){
        
        ofFloatColor sampleColor(vidGrabber.getPixels()[i*3]/255.f,				// r
                                 vidGrabber.getPixels()[i*3+1]/255.f,			// g
                                 vidGrabber.getPixels()[i*3+2]/255.f); //b
        ofVec3f tmpVec = mesh.getVertex(i);
        tmpVec.z = sampleColor.getBrightness() * extrusionAmount;
        
        

        mesh.setVertex(i, tmpVec);
        float rotateAmount = ofMap(ofGetMouseX(), 0, ofGetWidth(), -60, 60);
        
        
        //move the camera around the mesh
        ofVec3f camDirection(0,0,1);
        ofVec3f centre(vidGrabber.getWidth()/2.f,vidGrabber.getHeight()/2.f, 255/2.f);
        ofVec3f camDirectionRotated = camDirection.getRotated(rotateAmount, ofVec3f(0,1,0));
        ofVec3f camPosition = centre + camDirectionRotated * extrusionAmount*3;
        
        cam.setPosition(camPosition - ofPoint(0,0,300));
        cam.lookAt(centre);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(255,0);
    
    ofEnableDepthTest();
    
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    
    cam.begin();
    mesh.setMode(OF_PRIMITIVE_LINES_ADJACENCY);
    mesh.draw();
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    mesh.draw();
    cam.end();

}
