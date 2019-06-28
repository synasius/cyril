#pragma once

#include "ofMain.h"
#include "ofxBeat.h"

class testApp : public ofBaseApp{
  ofxBeat beat;
  
	public:
		void setup() override;
		void update() override;
		void draw() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
  
  void audioReceived(float*, int, int) override;

};
