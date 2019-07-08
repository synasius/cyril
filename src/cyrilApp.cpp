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
  m_doResetTimers = true;

  ofSoundStreamSettings settings;
  settings.numOutputChannels = 0;
  settings.numInputChannels = 1;
  settings.sampleRate = 44100;
  settings.bufferSize = m_beat.getBufferSize();
  settings.numBuffers = 4;
  settings.setInListener(this);

  m_soundStream.setup(settings);

  // Switch back to external data folder
  // ofSetDataPathRoot("../../../data/");

  ofBackground(0);
  m_pauseProg = false;
  m_lightsOn = false;
  m_isOrtho = false;
  m_fxOn = false;

  m_runningProg = false;
  m_running[0] = false;
  m_running[1] = false;
  m_running[2] = false;
  m_running[3] = false;
  m_running[4] = false;
  m_running[5] = false;
  m_running[6] = false;
  m_running[7] = false;
  m_running[8] = false;
  m_running[9] = false;
  m_error[0] = false;
  m_error[1] = false;
  m_error[2] = false;
  m_error[3] = false;
  m_error[4] = false;
  m_error[5] = false;
  m_error[6] = false;
  m_error[7] = false;
  m_error[8] = false;
  m_error[9] = false;

#ifdef FULL_DEBUG
  ofSetLogLevel("ofxGLEditor", OF_LOG_VERBOSE);
#endif

  m_editor.addCommand('z', this, &cyrilApp::toggleFx);
  m_editor.addCommand('f', this, &cyrilApp::toggleFullscreen);
  m_editor.addCommand('a', this, &cyrilApp::toggleEditor);
  m_editor.addCommand('d', this, &cyrilApp::toggleBackground);
  m_editor.addCommand('k', this, &cyrilApp::toggleLights);
  m_editor.addCommand('l', this, &cyrilApp::loadFile);
  m_editor.addCommand('s', this, &cyrilApp::saveFile);
  m_editor.addCommand('e', this, &cyrilApp::resetTimers);
  m_editor.addCommand('p', this, &cyrilApp::pauseProgram);
  m_editor.addCommand('r', this, &cyrilApp::runScript);
  m_editor.addCommand('o', this, &cyrilApp::toggleOrtho);

  m_editorVisible = true;

  m_lastSignalReport = -1;

  // Init evaluation stack to empty
  m_state.stk = new std::stack<float>;
  // Initialise our own matrix stack
  // TODO: replace with call to get from current renderer?
  m_state.ms = new ofMatrixStack(ofGetWindowPtr());
  // Initialise empty paticle system
  m_state.ps = new std::vector<Particle*>;
  // Initialise empty variable/register map
  m_state.sym = new std::map<int, float>;
  // Initialise palettes
  m_state.cs = new std::map<int, Palette*>;
  // Initialise sprites
  m_state.img = new std::map<int, ofImage*>;
  m_state.parent = nullptr;
  m_state.light = new ofLight();
  //_state.light = NULL;

  (*m_state.sym)[REG_X_MAX] = 640;
  (*m_state.sym)[REG_Y_MAX] = 480;
  (*m_state.sym)[REG_X_MID] = (*m_state.sym)[REG_X_MAX] / 2.0;
  (*m_state.sym)[REG_Y_MID] = (*m_state.sym)[REG_Y_MAX] / 2.0;

  (*m_state.sym)[REG_X_SCALE] = 100;
  (*m_state.sym)[REG_Y_SCALE] = 100;
  (*m_state.sym)[REG_Z_SCALE] = 100;

  (*m_state.sym)[REG_PI] = PI;
  (*m_state.sym)[REG_TWO_PI] = TWO_PI;

  (*m_state.sym)[REG_PARTICLE_HEALTH] = 1;
  (*m_state.sym)[REG_PARTICLE_DECAY] = 0.1;

  (*m_state.sym)[OSC_X] = 0;
  (*m_state.sym)[OSC_Y] = 0;
  (*m_state.sym)[OSC_F1] = 0;
  (*m_state.sym)[OSC_F2] = 0;
  (*m_state.sym)[OSC_F3] = 0;
  (*m_state.sym)[OSC_F4] = 0;

  // Reserve some space for Particle System
  m_state.ps->reserve(2000);

  // Global settings
  ofEnableDepthTest();
  ofSetVerticalSync(true);
  if (m_lightsOn) {
    ofEnableLighting();
    m_state.light->setAmbientColor(ofColor(0, 0, 0));
    m_state.light->setDiffuseColor(ofColor(255, 255, 255));
    m_state.light->setSpecularColor(ofColor(255, 255, 255));
    m_state.light->setPointLight();
    m_state.light->setAttenuation(1.f, 0.f, 0.f);
  }

  m_autoClearBg = true;
  ofSetBackgroundAuto(true);

  m_cursorVisible = true;

  (*m_state.sym)[REG_FRAME] = 0;

  //  edBuf.allocate();
  //  edBuf.begin();
  //  ofClear(0,0,0,0);
  //  edBuf.end();

  ofEnableAlphaBlending();
  ofEnableAntiAliasing();
  ofEnableSmoothing();

  m_isFullScreen = false;

  // mainOutputSyphonServer.setName("Cyril Main Output");
  // mClient.setup();
  // mClient.set("","Cyril Server");

  // listen on the given port
  //	cout << "listening for osc messages on " + getIpAddress() + ":" << PORT
  //<< endl; 	receiver.setup(PORT);

  // Configure the ofxPostProcessing effects
  m_state.post = ofxPostProcessing();
  m_state.post.init(ofGetWidth(), ofGetHeight());
  m_state.post.setFlip(false);
  m_state.kaleido = m_state.post.createPass<KaleidoscopePass>();
  m_state.noisewarp = m_state.post.createPass<NoiseWarpPass>();

  m_state.pixelate = m_state.post.createPass<PixelatePass>();
  m_state.bloom = m_state.post.createPass<BloomPass>();

  for (int i = 0; i < 10; ++i) {
    m_modTimes[i] = 0;
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
      //            if (t > m_modTimes[i]) {
      //                m_modTimes[i] = t;
      //                reloadFileBuffer("code/" + ofToString(i) + ".cy");
      //            }
    } else {
      // cout << "file " + ofToString(i) << ".cy not found" << endl;
    }
  }

  // Disable all ofxPostProcessing effects so they only activate
  // if command is present in a running program
  m_state.post[FX_KALEIDOSCOPE]->disable();
  m_state.post[FX_NOISE_WARP]->disable();
  m_state.post[FX_PIXELATE]->disable();
  m_state.post[FX_BLOOM]->disable();

  for (int i = 0; i < 10; ++i) {
    if (m_running[i]) {
      if (m_prog[i]->valid) {
        m_prog[i]->update(m_state);
      }
    }
  }

  if (m_doResetTimers) {
    (*m_state.sym)[REG_FRAME] = 0;
    ofResetElapsedTimeCounter();
    m_doResetTimers = false;
  } else {
    (*m_state.sym)[REG_FRAME]++;
  }

  (*m_state.sym)[REG_TIME] = ofGetElapsedTimeMillis();
  (*m_state.sym)[REG_SECS] = ofGetElapsedTimef();
  (*m_state.sym)[REG_FAST] = ofGetElapsedTimef() * 10;
  (*m_state.sym)[REG_SLOW] = ofGetElapsedTimef() * 2;

  // For beat detection
  m_beat.update((*m_state.sym)[REG_TIME]);
  (*m_state.sym)[REG_BEAT_MAGNITUDE] = m_beat.getMagnitude();
  (*m_state.sym)[REG_BEAT_KICK] = m_beat.kick();
  (*m_state.sym)[REG_BEAT_SNARE] = m_beat.snare();
  (*m_state.sym)[REG_BEAT_HIHAT] = m_beat.hihat();
  for (int i = REG_BEAT_FFT_START; i < REG_BEAT_FFT_MAX; ++i) {
    (*m_state.sym)[i] = m_beat.getBand(i - REG_BEAT_FFT_START);
  }

  for (vector<Particle*>::iterator it = m_state.ps->begin();
       it != m_state.ps->end();
       ++it) {
    (*it)->update();
  }
  ofRemove(*m_state.ps, Particle::isDead);

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

  if (m_fxOn) {
    m_state.post.begin();
  }

  ofEnableDepthTest();

  if (m_lightsOn) {
    m_state.light->enable();
    // The default position of the light (apply z-scale)
    m_state.light->setPosition(0, 0, 1000);
  } else {
    ofDisableLighting();
  }

  // ofEnableAlphaBlending();

  m_state.ms->clearStacks();
  float X_MID = (*m_state.sym)[REG_X_MID];
  float Y_MID = (*m_state.sym)[REG_Y_MID];
  float X_SCALE = (*m_state.sym)[REG_X_SCALE];
  float Y_SCALE = (*m_state.sym)[REG_Y_SCALE];
  float Z_SCALE = (*m_state.sym)[REG_Z_SCALE];

  for (int i = 0; i < 10; ++i) {
    if (m_running[i]) {
      if (m_prog[i]->valid) {
        ofPushMatrix();
        ofTranslate(X_MID, Y_MID);
        m_state.ms->pushMatrix();
        m_state.ms->translate(X_MID, Y_MID);

        ofScale(X_SCALE, Y_SCALE, Z_SCALE);
        m_state.ms->scale(X_SCALE, Y_SCALE, Z_SCALE);

        m_prog[i]->eval(m_state);

        m_state.ms->popMatrix();
        ofPopMatrix();
      }
    }
  }

  for (vector<Particle*>::iterator it = m_state.ps->begin();
       it != m_state.ps->end();
       ++it) {
    (*it)->draw(&m_state);
  }

  if (m_lightsOn) {
    m_state.light->disable();
  }

  if (m_fxOn) {
    m_state.post.end();
  }

  // mainOutputSyphonServer.publishScreen();

  // Draw the editor if enabled
  if (m_editorVisible) {
    ofDisableDepthTest();
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255);
    ofFill();
    m_editor.draw();
    ofTranslate(X_MID - 50, 10);
    for (int i = 0; i < 10; ++i) {
      if (m_error[i]) {
        ofSetColor(255, 0, 0);
      } else if (m_running[i]) {
        ofSetColor(255);
      } else {
        ofSetColor(150);
      }
      ofDrawRectangle(i * 10, 0, 8, 8);
      if (m_editor.currentBuffer == i) {
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
  ((cyrilApp*)_o)->m_fxOn = !((cyrilApp*)_o)->m_fxOn;
}

void
cyrilApp::toggleFullscreen(void* _o)
{
  ((cyrilApp*)_o)->m_isFullScreen = !((cyrilApp*)_o)->m_isFullScreen;
  ofSetFullscreen(((cyrilApp*)_o)->m_isFullScreen);

  if (((cyrilApp*)_o)->m_isFullScreen) {
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
  ((cyrilApp*)_o)->m_editorVisible = !((cyrilApp*)_o)->m_editorVisible;
}
void
cyrilApp::toggleOrtho(void* _o)
{
  ((cyrilApp*)_o)->m_isOrtho = !((cyrilApp*)_o)->m_isOrtho;
  if (((cyrilApp*)_o)->m_isOrtho) {
    // ofSetupScreenOrtho();
    ofSetupScreenOrtho(1200, 1200, 0, 10);
  } else {
    ofSetupScreenPerspective(1200, 1200, 0, 0, 0);
  }
}
void
cyrilApp::toggleBackground(void* _o)
{
  ((cyrilApp*)_o)->m_autoClearBg = !((cyrilApp*)_o)->m_autoClearBg;
}
void
cyrilApp::toggleLights(void* _o)
{
  ((cyrilApp*)_o)->m_lightsOn = !((cyrilApp*)_o)->m_lightsOn;
  ofEnableLighting();
  ofSetSmoothLighting(true);
  ((cyrilApp*)_o)->m_state.light->setAmbientColor(ofColor(0, 0, 0));
  ((cyrilApp*)_o)->m_state.light->setDiffuseColor(ofColor(255, 255, 255));
  ((cyrilApp*)_o)->m_state.light->setSpecularColor(ofColor(255, 255, 255));
  ((cyrilApp*)_o)->m_state.light->setPointLight();
  ((cyrilApp*)_o)->m_state.light->setAttenuation(1.f, 0.f, 0.f);
}

void
cyrilApp::loadFile(void* _o)
{
  int whichEditor = ((cyrilApp*)_o)->m_editor.currentBuffer;
  ((cyrilApp*)_o)
    ->m_editor.loadFile("code/" + ofToString(whichEditor) + ".cy", whichEditor);
  ((cyrilApp*)_o)->m_editor.update();
}

void
cyrilApp::saveFile(void* _o)
{
  int whichEditor = ((cyrilApp*)_o)->m_editor.currentBuffer;
  ((cyrilApp*)_o)
    ->m_editor.saveFile("code/" + ofToString(whichEditor) + ".cy", whichEditor);
}

void
cyrilApp::resetTimers(void* _o)
{
  ((cyrilApp*)_o)->m_doResetTimers = true;
}

void
cyrilApp::pauseProgram(void* _o)
{
  if (((cyrilApp*)_o)->m_prog[((cyrilApp*)_o)->m_editor.currentBuffer] &&
      ((cyrilApp*)_o)->m_prog[((cyrilApp*)_o)->m_editor.currentBuffer]->valid) {
    int whichEditor = ((cyrilApp*)_o)->m_editor.currentBuffer;
    ((cyrilApp*)_o)->m_running[whichEditor] =
      !((cyrilApp*)_o)->m_running[whichEditor];
  }
}

void
cyrilApp::runScript(void* _o)
{
  int whichEditor = ((cyrilApp*)_o)->m_editor.currentBuffer;
#ifdef DEBUG_PRINT
  cout << "run script in editor " << whichEditor << endl;
#endif
  Cyril* tempProg = CyrilParser::parseString(
    ((cyrilApp*)_o)->m_editor.buf[whichEditor]->getText());
  if (tempProg->valid) {
    ((cyrilApp*)_o)->m_prog[whichEditor] = tempProg;
    ((cyrilApp*)_o)->m_runningProg = true;
    ((cyrilApp*)_o)->m_running[whichEditor] = true;
    ((cyrilApp*)_o)->m_error[whichEditor] = false;
#ifdef DEBUG_PRINT
    ((cyrilApp*)_o)->prog[whichEditor]->print();
#endif
  } else {
    ((cyrilApp*)_o)->m_error[whichEditor] = true;
#ifdef DEBUG_PRINT
    cout << "Invalid program" << endl;
#endif
  }
  ((cyrilApp*)_o)->m_reportError = true;
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
    m_editor.loadFile("code/" + ofToString(i) + ".cy", i);
    m_editor.currentBuffer = i;
    runScript(this);
  } else {
    m_running[i] = false;
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
      m_editor.loadFile(filePath, whichEditor);
      // editor.update();
      if (m_running[whichEditor]) {
        m_editor.currentBuffer = whichEditor;
        runScript(this);
      }
    }
  }
  if (file.getExtension() == "png") {
    // cout << "Loading image " << file.getFileName() << endl;
    int whichImg = ofToInt(removeExtension(file.getFileName()));
    (*m_state.img)[whichImg] = new ofImage(filePath);
    // cout << "Loaded image type = " << ((*_state.img)[whichImg]->type) <<
    // endl;
    //(*_state.img)[whichImg]->setImageType(OF_IMAGE_COLOR_ALPHA);
    (*m_state.img)[whichImg]->setAnchorPercent(0.5, 0.5);
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
  (*m_state.sym)[REG_X_MAX] = w;
  (*m_state.sym)[REG_Y_MAX] = h;
  (*m_state.sym)[REG_X_MID] = w / 2.0;
  (*m_state.sym)[REG_Y_MID] = h / 2.0;
  m_state.post.setWidth(w);
  m_state.post.setHeight(h);
}

//--------------------------------------------------------------
void cyrilApp::gotMessage(ofMessage) {}

//--------------------------------------------------------------
void cyrilApp::dragEvent(ofDragInfo) {}

void
cyrilApp::audioIn(ofSoundBuffer& buffer)
{
  m_beat.audioReceived(
    buffer.getBuffer().data(), buffer.size(), buffer.getNumChannels());
}
