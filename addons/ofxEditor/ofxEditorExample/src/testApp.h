#pragma once

#include "ofMain.h"
#include "ofxEditor.h"


class testApp : public ofBaseApp{
  
  ofxEditor editor;
  bool editorVisible;
  bool isFullscreen;
  
	public:
  testApp() : editor(9), editorVisible(true), isFullscreen(false) {}
  
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
  
  // Editor command callbacks are static methods
  static void toggleFullscreen(void *);
  static void toggleEditor(void *);
};
