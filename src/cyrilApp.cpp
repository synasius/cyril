#include "cyrilApp.h"

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <ofSoundStream.h>


string
getIpAddress()
{
  string output = "NOT FOUND";
  struct ifaddrs* myaddrs;
  struct ifaddrs* ifa;
  struct sockaddr_in* s4;
  int status;

  char buf[64];

  status = getifaddrs(&myaddrs);
  if (status != 0) {
    perror("getifaddrs");
  }

  for (ifa = myaddrs; ifa != nullptr; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == nullptr)
      continue;
    if ((ifa->ifa_flags & IFF_UP) == 0)
      continue;

    if (ifa->ifa_addr->sa_family == AF_INET) {
      s4 = (struct sockaddr_in*)(ifa->ifa_addr);
      if (inet_ntop(ifa->ifa_addr->sa_family,
                    (void*)&(s4->sin_addr),
                    buf,
                    sizeof(buf)) == nullptr) {
        printf("%s: inet_ntop failed!\n", ifa->ifa_name);
      } else {
        if (ofToString(ifa->ifa_name) == "en0") {
          output = ofToString(buf);
        }
      }
    }
  }

  freeifaddrs(myaddrs);
  return output;
}

//--------------------------------------------------------------
void
cyrilApp::setup()
{
  doResetTimers = true;

  // TODO: use settings
  //ofSoundStreamSettings settings;
  //settings.numOutputChannels = 0;
  //settings.numInputChannels = 1;
  //settings.sampleRate = 44100;
  //settings.bufferSize = beat.getBufferSize();
  //settings.numBuffers = 4;
  //ofSoundStreamSetup(settings);
  ofSoundStreamSetup(0, 1, this, 44100, beat.getBufferSize(), 4);

  // Switch back to external data folder
  // ofSetDataPathRoot("../../../data/");

  ofBackground(0);
  pauseProg = false;
  // lightsOn = true;
  lightsOn = true;
  isOrtho = false;
  fxOn = true;

  runningProg = false;
  running[0] = false;
  running[1] = false;
  running[2] = false;
  running[3] = false;
  running[4] = false;
  running[5] = false;
  running[6] = false;
  running[7] = false;
  running[8] = false;
  running[9] = false;
  error[0] = false;
  error[1] = false;
  error[2] = false;
  error[3] = false;
  error[4] = false;
  error[5] = false;
  error[6] = false;
  error[7] = false;
  error[8] = false;
  error[9] = false;

#ifdef FULL_DEBUG
  ofSetLogLevel("ofxGLEditor", OF_LOG_VERBOSE);
#endif

  editor.addCommand('z', this, &cyrilApp::toggleFx);
  editor.addCommand('f', this, &cyrilApp::toggleFullscreen);
  editor.addCommand('a', this, &cyrilApp::toggleEditor);
  editor.addCommand('d', this, &cyrilApp::toggleBackground);
  editor.addCommand('k', this, &cyrilApp::toggleLights);
  editor.addCommand('l', this, &cyrilApp::loadFile);
  editor.addCommand('s', this, &cyrilApp::saveFile);
  editor.addCommand('e', this, &cyrilApp::resetTimers);
  editor.addCommand('p', this, &cyrilApp::pauseProgram);
  editor.addCommand('r', this, &cyrilApp::runScript);
  editor.addCommand('o', this, &cyrilApp::toggleOrtho);

  editorVisible = true;

  lastSignalReport = -1;

  // Init evaluation stack to empty
  _state.stk = new stack<float>;
  // Initialise our own matrix stack
  // TODO: replace with call to get from current renderer?
  _state.ms = new ofMatrixStack(ofGetWindowPtr());
  // Initialise empty paticle system
  _state.ps = new vector<Particle*>;
  // Initialise empty variable/register map
  _state.sym = new map<int, float>;
  // Initialise palettes
  _state.cs = new map<int, Palette*>;
  // Initialise sprites
  _state.img = new map<int, ofImage*>;
  _state.parent = nullptr;
  _state.light = new ofLight();
  //_state.light = NULL;

  (*_state.sym)[REG_X_MAX] = 640;
  (*_state.sym)[REG_Y_MAX] = 480;
  (*_state.sym)[REG_X_MID] = (*_state.sym)[REG_X_MAX] / 2.0;
  (*_state.sym)[REG_Y_MID] = (*_state.sym)[REG_Y_MAX] / 2.0;

  (*_state.sym)[REG_X_SCALE] = 100;
  (*_state.sym)[REG_Y_SCALE] = 100;
  (*_state.sym)[REG_Z_SCALE] = 100;

  (*_state.sym)[REG_PI] = PI;
  (*_state.sym)[REG_TWO_PI] = TWO_PI;

  (*_state.sym)[REG_PARTICLE_HEALTH] = 1;
  (*_state.sym)[REG_PARTICLE_DECAY] = 0.1;

  (*_state.sym)[OSC_X] = 0;
  (*_state.sym)[OSC_Y] = 0;
  (*_state.sym)[OSC_F1] = 0;
  (*_state.sym)[OSC_F2] = 0;
  (*_state.sym)[OSC_F3] = 0;
  (*_state.sym)[OSC_F4] = 0;

  // Reserve some space for Particle System
  _state.ps->reserve(2000);

  // Global settings
  ofEnableDepthTest();
  ofSetVerticalSync(true);
  if (lightsOn) {
    ofEnableLighting();
    _state.light->setAmbientColor(ofColor(0, 0, 0));
    _state.light->setDiffuseColor(ofColor(255, 255, 255));
    _state.light->setSpecularColor(ofColor(255, 255, 255));
    _state.light->setPointLight();
    _state.light->setAttenuation(1.f, 0.f, 0.f);
  }

  autoClearBg = true;
  ofSetBackgroundAuto(true);

  // changed this...
  cursorVisible = true;
  // ofHideCursor();
#ifdef __APPLE__
  // CGDisplayHideCursor(NULL); // <- OK
#endif

  (*_state.sym)[REG_FRAME] = 0;

  //  edBuf.allocate();
  //  edBuf.begin();
  //  ofClear(0,0,0,0);
  //  edBuf.end();

  ofEnableAlphaBlending();
  ofEnableAntiAliasing();
  ofEnableSmoothing();

  isFullScreen = false;
  // ofSetFullscreen(true);

  // mainOutputSyphonServer.setName("Cyril Main Output");
  // mClient.setup();
  // mClient.set("","Cyril Server");

  // listen on the given port
  //	cout << "listening for osc messages on " + getIpAddress() + ":" << PORT
  //<< endl; 	receiver.setup(PORT);

  // Configure the ofxPostProcessing effects
  _state.post = ofxPostProcessing();
  _state.post.init(ofGetWidth(), ofGetHeight());
  _state.post.setFlip(false);
  _state.kaleido = _state.post.createPass<KaleidoscopePass>();
  _state.noisewarp = _state.post.createPass<NoiseWarpPass>();

  _state.pixelate = _state.post.createPass<PixelatePass>();
  _state.bloom = _state.post.createPass<BloomPass>();

  for (int i = 0; i < 10; ++i) {
    modTimes[i] = 0;
  }
}

//--------------------------------------------------------------
void
cyrilApp::update()
{
  // check files for modifications
  for (int i = 0; i < 10; ++i) {
    // cout << "data/code/" + ofToString(i) + ".cy" << endl;
    ofFile f = ofFile("code/" + ofToString(i) + ".cy");
    if (f.exists()) {
      // cout << f.getPocoFile().getLastModified().epochTime() << endl;

      //          //TODO: had to disable this as ofFile has changed, cf no
      //          PocoFile
      //            Poco::Timestamp t = f.getPocoFile().getLastModified();
      //            if (t > modTimes[i]) {
      //                modTimes[i] = t;
      //                reloadFileBuffer("code/" + ofToString(i) + ".cy");
      //            }
    } else {
      // cout << "file " + ofToString(i) << ".cy not found" << endl;
    }
  }

  // Disable all ofxPostProcessing effects so they only activate
  // if command is present in a running program
  _state.post[FX_KALEIDOSCOPE]->disable();
  _state.post[FX_NOISE_WARP]->disable();
  _state.post[FX_PIXELATE]->disable();
  _state.post[FX_BLOOM]->disable();

  for (int i = 0; i < 10; ++i) {
    if (running[i]) {
      if (prog[i]->valid) {
        prog[i]->update(_state);
      }
    }
  }

  if (doResetTimers) {
    (*_state.sym)[REG_FRAME] = 0;
    ofResetElapsedTimeCounter();
    doResetTimers = false;
  } else {
    (*_state.sym)[REG_FRAME]++;
  }

  (*_state.sym)[REG_TIME] = ofGetElapsedTimeMillis();
  (*_state.sym)[REG_SECS] = ofGetElapsedTimef();
  (*_state.sym)[REG_FAST] = ofGetElapsedTimef() * 10;
  (*_state.sym)[REG_SLOW] = ofGetElapsedTimef() * 2;

  // For beat detection
  beat.update((*_state.sym)[REG_TIME]);
  (*_state.sym)[REG_BEAT_MAGNITUDE] = beat.getMagnitude();
  (*_state.sym)[REG_BEAT_KICK] = beat.kick();
  (*_state.sym)[REG_BEAT_SNARE] = beat.snare();
  (*_state.sym)[REG_BEAT_HIHAT] = beat.hihat();
  for (int i = REG_BEAT_FFT_START; i < REG_BEAT_FFT_MAX; ++i) {
    (*_state.sym)[i] = beat.getBand(i - REG_BEAT_FFT_START);
  }

  for (vector<Particle*>::iterator it = _state.ps->begin();
       it != _state.ps->end();
       ++it) {
    (*it)->update();
  }
  ofRemove(*_state.ps, Particle::isDead);

  //	// check for waiting OSC messages
  //	while(receiver.hasWaitingMessages()){
  //		// get the next message
  //		ofxOscMessage m;
  //        receiver.getNextMessage(&m);
  //        // Check for the toggle messages
  //        bool msgProcessed = false;
  //        for (int i = 1; i < 9; ++i) {
  //            if (m.getAddress() == ("/1/toggle" + ofToString(i))) {
  //                cout << "Process message " <<  ("/1/toggle" + ofToString(i))
  //                << endl; if (m.getArgAsFloat(0) == 0) {
  //                    toggleScript(i, false);
  //                }
  //                else if (m.getArgAsFloat(0) == 1) {
  //                    toggleScript(i, true);
  //                }
  //                msgProcessed = true;
  //            }
  //        }
  //        if (m.getAddress() == "/1/xy1") {
  //            (*_state.sym)[OSC_X] = m.getArgAsFloat(0);
  //            (*_state.sym)[OSC_Y] = m.getArgAsFloat(1);
  //            msgProcessed = true;
  //        }
  //        else if (m.getAddress() == "/1/fader1") {
  //            (*_state.sym)[OSC_F1] = m.getArgAsFloat(0);
  //            msgProcessed = true;
  //        }
  //        else if (m.getAddress() == "/1/fader2") {
  //            (*_state.sym)[OSC_F2] = m.getArgAsFloat(0);
  //            msgProcessed = true;
  //        }
  //        else if (m.getAddress() == "/1/fader3") {
  //            (*_state.sym)[OSC_F3] = m.getArgAsFloat(0);
  //            msgProcessed = true;
  //        }
  //        else if (m.getAddress() == "/1/fader4") {
  //            (*_state.sym)[OSC_F4] = m.getArgAsFloat(0);
  //            msgProcessed = true;
  //        }
  //
  //        if (!msgProcessed) {
  //            cout << "Unknown OSC message " << m.getAddress() << endl;
  //        }
  //
  //        /*
  //        string msg_string;
  //        msg_string = m.getAddress();
  //        cout << msg_string << endl;
  //        cout << m.getArgAsFloat(0);
  //        */
  //  }
}

//--------------------------------------------------------------
void
cyrilApp::draw()
{

  if (fxOn) {
    _state.post.begin();
  }

  ofEnableDepthTest();

  if (lightsOn) {
    _state.light->enable();
    // The default position of the light (apply z-scale)
    _state.light->setPosition(0, 0, 1000);
  } else {
    ofDisableLighting();
  }

  // ofEnableAlphaBlending();

  _state.ms->clearStacks();
  float X_MID = (*_state.sym)[REG_X_MID];
  float Y_MID = (*_state.sym)[REG_Y_MID];
  float X_SCALE = (*_state.sym)[REG_X_SCALE];
  float Y_SCALE = (*_state.sym)[REG_Y_SCALE];
  float Z_SCALE = (*_state.sym)[REG_Z_SCALE];

  for (int i = 0; i < 10; ++i) {
    if (running[i]) {
      if (prog[i]->valid) {
        ofPushMatrix();
        ofTranslate(X_MID, Y_MID);
        _state.ms->pushMatrix();
        _state.ms->translate(X_MID, Y_MID);

        ofScale(X_SCALE, Y_SCALE, Z_SCALE);
        _state.ms->scale(X_SCALE, Y_SCALE, Z_SCALE);

        prog[i]->eval(_state);

        _state.ms->popMatrix();
        ofPopMatrix();
      }
    }
  }

  for (vector<Particle*>::iterator it = _state.ps->begin();
       it != _state.ps->end();
       ++it) {
    (*it)->draw(&_state);
  }

  if (lightsOn) {
    _state.light->disable();
  }

  if (fxOn) {
    _state.post.end();
  }

  // mainOutputSyphonServer.publishScreen();

  // Draw the editor if enabled
  if (editorVisible) {
    ofDisableDepthTest();
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255);
    ofFill();
    editor.draw();
    ofTranslate(X_MID - 50, 10);
    for (int i = 0; i < 10; ++i) {
      if (error[i]) {
        ofSetColor(255, 0, 0);
      } else if (running[i]) {
        ofSetColor(255);
      } else {
        ofSetColor(150);
      }
      ofDrawRectangle(i * 10, 0, 8, 8);
      if (editor.currentBuffer == i) {
        ofSetColor(255);
        ofDrawRectangle(i * 10, 10, 8, 5);
      }
    }
    ofPopStyle();
    ofPopMatrix();
  }
}

void
cyrilApp::toggleFx(void* _o)
{
  ((cyrilApp*)_o)->fxOn = !((cyrilApp*)_o)->fxOn;
}

void
cyrilApp::toggleFullscreen(void* _o)
{
  ((cyrilApp*)_o)->isFullScreen = !((cyrilApp*)_o)->isFullScreen;
  ofSetFullscreen(((cyrilApp*)_o)->isFullScreen);

  if (((cyrilApp*)_o)->isFullScreen) {
    ofHideCursor();
#ifdef __APPLE__
    CGDisplayHideCursor(NULL);
#endif
  } else {
    ofShowCursor();
#ifdef __APPLE__
    CGDisplayShowCursor(NULL);
#endif
  }
}
void
cyrilApp::toggleEditor(void* _o)
{
  ((cyrilApp*)_o)->editorVisible = !((cyrilApp*)_o)->editorVisible;
}
void
cyrilApp::toggleOrtho(void* _o)
{
  ((cyrilApp*)_o)->isOrtho = !((cyrilApp*)_o)->isOrtho;
  if (((cyrilApp*)_o)->isOrtho) {
    // ofSetupScreenOrtho();
    ofSetupScreenOrtho(1200, 1200, 0, 10);
  } else {
    ofSetupScreenPerspective(1200, 1200, 0, 0, 0);
  }
}
void
cyrilApp::toggleBackground(void* _o)
{
  ((cyrilApp*)_o)->autoClearBg = !((cyrilApp*)_o)->autoClearBg;
}
void
cyrilApp::toggleLights(void* _o)
{
  ((cyrilApp*)_o)->lightsOn = !((cyrilApp*)_o)->lightsOn;
  ofEnableLighting();
  ofSetSmoothLighting(true);
  ((cyrilApp*)_o)->_state.light->setAmbientColor(ofColor(0, 0, 0));
  ((cyrilApp*)_o)->_state.light->setDiffuseColor(ofColor(255, 255, 255));
  ((cyrilApp*)_o)->_state.light->setSpecularColor(ofColor(255, 255, 255));
  ((cyrilApp*)_o)->_state.light->setPointLight();
  ((cyrilApp*)_o)->_state.light->setAttenuation(1.f, 0.f, 0.f);
}

void
cyrilApp::loadFile(void* _o)
{
  int whichEditor = ((cyrilApp*)_o)->editor.currentBuffer;
  ((cyrilApp*)_o)
    ->editor.loadFile("code/" + ofToString(whichEditor) + ".cy", whichEditor);
  ((cyrilApp*)_o)->editor.update();
}

void
cyrilApp::saveFile(void* _o)
{
  int whichEditor = ((cyrilApp*)_o)->editor.currentBuffer;
  ((cyrilApp*)_o)
    ->editor.saveFile("code/" + ofToString(whichEditor) + ".cy", whichEditor);
}

void
cyrilApp::resetTimers(void* _o)
{
  ((cyrilApp*)_o)->doResetTimers = true;
}

void
cyrilApp::pauseProgram(void* _o)
{
  if (((cyrilApp*)_o)->prog[((cyrilApp*)_o)->editor.currentBuffer] &&
      ((cyrilApp*)_o)->prog[((cyrilApp*)_o)->editor.currentBuffer]->valid) {
    int whichEditor = ((cyrilApp*)_o)->editor.currentBuffer;
    ((cyrilApp*)_o)->running[whichEditor] =
      !((cyrilApp*)_o)->running[whichEditor];
  }
}

void
cyrilApp::runScript(void* _o)
{
  int whichEditor = ((cyrilApp*)_o)->editor.currentBuffer;
#ifdef DEBUG_PRINT
  cout << "run script in editor " << whichEditor << endl;
#endif
  Cyril* tempProg = CyrilParser::parseString(
    ((cyrilApp*)_o)->editor.buf[whichEditor]->getText());
  if (tempProg->valid) {
    ((cyrilApp*)_o)->prog[whichEditor] = tempProg;
    ((cyrilApp*)_o)->runningProg = true;
    ((cyrilApp*)_o)->running[whichEditor] = true;
    ((cyrilApp*)_o)->error[whichEditor] = false;
#ifdef DEBUG_PRINT
    ((cyrilApp*)_o)->prog[whichEditor]->print();
#endif
  } else {
    ((cyrilApp*)_o)->error[whichEditor] = true;
#ifdef DEBUG_PRINT
    cout << "Invalid program" << endl;
#endif
  }
  ((cyrilApp*)_o)->reportError = true;
}

std::string
removeExtension(const std::string filename)
{
  size_t lastdot = filename.find_last_of(".");
  if (lastdot == std::string::npos)
    return filename;
  return filename.substr(0, lastdot);
}

void
cyrilApp::toggleScript(int i, bool r)
{
  if (r) {
    editor.loadFile("code/" + ofToString(i) + ".cy", i);
    editor.currentBuffer = i;
    runScript(this);
  } else {
    running[i] = false;
  }
}

void
cyrilApp::reloadFileBuffer(std::string filePath)
{
  // cout << "File = " << filePath << endl;
  ofFile file = ofFile(filePath);
  if (file.getExtension() == "cy") {
    int whichEditor = ofToInt(removeExtension(file.getFileName()));
    if (whichEditor >= 0 && whichEditor <= 9) {
      editor.loadFile(filePath, whichEditor);
      // editor.update();
      if (running[whichEditor]) {
        editor.currentBuffer = whichEditor;
        runScript(this);
      }
    }
  }
  if (file.getExtension() == "png") {
    // cout << "Loading image " << file.getFileName() << endl;
    int whichImg = ofToInt(removeExtension(file.getFileName()));
    (*_state.img)[whichImg] = new ofImage(filePath);
    // cout << "Loaded image type = " << ((*_state.img)[whichImg]->type) <<
    // endl;
    //(*_state.img)[whichImg]->setImageType(OF_IMAGE_COLOR_ALPHA);
    (*_state.img)[whichImg]->setAnchorPercent(0.5, 0.5);
  }
}

//--------------------------------------------------------------
void
cyrilApp::keyPressed(int)
{}

//--------------------------------------------------------------
void
cyrilApp::keyReleased(int)
{}

//--------------------------------------------------------------
void
cyrilApp::mouseMoved(int, int)
{}

//--------------------------------------------------------------
void
cyrilApp::mouseDragged(int, int, int)
{}

//--------------------------------------------------------------
void
cyrilApp::mousePressed(int, int, int)
{}

//--------------------------------------------------------------
void
cyrilApp::mouseReleased(int, int, int)
{}

//--------------------------------------------------------------
void
cyrilApp::windowResized(int w, int h)
{
  (*_state.sym)[REG_X_MAX] = w;
  (*_state.sym)[REG_Y_MAX] = h;
  (*_state.sym)[REG_X_MID] = w / 2.0;
  (*_state.sym)[REG_Y_MID] = h / 2.0;
  _state.post.setWidth(w);
  _state.post.setHeight(h);
}

//--------------------------------------------------------------
void
cyrilApp::gotMessage(ofMessage)
{}

//--------------------------------------------------------------
void
cyrilApp::dragEvent(ofDragInfo )
{}

void
cyrilApp::audioReceived(float* input, int bufferSize, int nChannels)
{
  beat.audioReceived(input, bufferSize, nChannels);
}

