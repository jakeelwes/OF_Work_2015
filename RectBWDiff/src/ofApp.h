#pragma once

#include "ofMain.h"
#include "Strip.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    

    
    float t;
    bool colour = false;
    
    std::vector<Strip> strips;
};
