#pragma once

// #define CYRIL_DEBUG

#include "Cyril/CyrilParser.h"
#include "Engine/Particle.h"

#include <ofMain.h>
#include <ofxBeat.h>
#include <ofxEditor.h>
#include <ofxPostProcessing.h>

#define FX_KALEIDOSCOPE 0
#define FX_NOISE_WARP 1
#define FX_PIXELATE 2
#define FX_BLOOM 3

//#include "ofxOsc.h"
// listen on port 12345
#define PORT 12345

#include <Poco/Timestamp.h>

class cyrilApp : public ofBaseApp
{
public:
  cyrilApp()
    : editor(10, "SourceCodePro.ttf")
  {}

  void setup() override;
  void update() override;
  void draw() override;

  void keyPressed(int key) override;
  void keyReleased(int key) override;
  void mouseMoved(int x, int y) override;
  void mouseDragged(int x, int y, int button) override;
  void mousePressed(int x, int y, int button) override;
  void mouseReleased(int x, int y, int button) override;
  void windowResized(int w, int h) override;
  void dragEvent(ofDragInfo dragInfo) override;
  void gotMessage(ofMessage msg) override;
  void applyGlobalSettings();
  void reloadSettings();

  void audioReceived(float*, int, int) override;

  void reloadFileBuffer(std::string);

  // Editor command callbacks
  static void toggleFx(void*);
  static void toggleFullscreen(void*);
  static void toggleOrtho(void*);
  static void toggleEditor(void*);
  static void toggleBackground(void*);
  static void toggleLights(void*);
  static void loadFile(void*);
  static void saveFile(void*);
  static void resetTimers(void*);
  static void pauseProgram(void*);
  static void runScript(void*);
  void toggleScript(int i, bool r);

private:
  ofxEditor editor;
  ofxBeat beat;

  // ofxSyphonServer mainOutputSyphonServer;
  // ofxSyphonClient mClient;

  //  ofxOscReceiver receiver;

  // ofxXmlSettings settings;
  string fileName;

  Cyril* prog[10];

  Poco::Timestamp modTimes[10];

  bool running[10];
  bool error[10];

  CyrilState _state;
  vector<string> progFiles;
  int currentProg;
  bool reportError;

  //  ofFbo edBuf;

  bool lightsOn;
  bool fxOn;

  bool autoClearBg;
  bool pauseProg;
  bool runningProg;
  bool overlay;
  bool editorVisible;
  bool cursorVisible;
  bool isFullScreen;
  bool doResetTimers;
  bool isOrtho;

  int lastSignalReport;

  void initPPFx();
};

