#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"

class ofApp : public ofBaseApp
{
public:
    static const unsigned NUM_BOXES = 100;
    
    void setup() override;
    void update() override;
    void draw() override;

    void keyPressed(int key) override;
    
    // scene stuff
    ofxPostProcessing post;
    ofEasyCam cam;
    ofLight light;
    
    // boxes
    vector<ofVec3f> posns;
    vector<ofColor> cols;
    ofVboMesh boxMesh;
};
