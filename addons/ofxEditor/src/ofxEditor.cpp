//  Created by Darren Mothersele on 19/11/2013.

#include "ofxEditor.h"

ofxEditor::ofxEditor(int noBuffers, string fontname)
  : textColor(ofColor::white, 200)
  , textBorderColor(ofColor::white, 200)
  , cursorColor(ofColor::white, 200)
  , highlightColor(ofColor::white, 200)
{
  // here we load path from the current resource folder
  // TODO: on macOS resource folder is in a different path (see bundle)
  auto resourcesPath =
    ofFilePath::join(ofFilePath::getCurrentExeDir(), "resources");
  auto fontPath = ofFilePath::join(resourcesPath, fontname);
  if (!m_font.load(fontPath, 30, true, true, false, 0.3f, 0)) {
    std::cout << "Could not load font '" << fontPath << "'\n";
  }

  // Reserve text buffers
  buf.reserve(noBuffers);
  for (int i = 0; i < noBuffers; ++i) {
    buf[i] = new EditorBuffer(&m_font);
    buf[i]->setTextColor(textColor, textBorderColor);
    buf[i]->setCursorColor(cursorColor);
    buf[i]->setHighlightColor(highlightColor);
  }
  currentBuffer = 0;
  maxBuffer = noBuffers - 1;

  // Create a frame buffer to render to
  ofFbo::Settings settings;
  settings.width = ofGetWidth();
  settings.height = ofGetHeight();
  editorFbo.allocate(settings);
  editorFbo.begin();
  ofClear(0, 0, 0, 0);
  editorFbo.end();

  // Add listener for key events
  ofAddListener(ofEvents().keyPressed, this, &ofxEditor::handleKeyPress);
  // Add listener for window size event
  ofAddListener(ofEvents().windowResized, this, &ofxEditor::windowResized);

  update();
}

void
ofxEditor::handleKeyPress(ofKeyEventArgs& _key)
{
  int key = _key.key;
  bool shift = (bool)(ofGetKeyPressed(OF_KEY_SHIFT));

  // TODO: cmd and ctrl are the same when OS is not MacOS
  bool cmd = (bool)(ofGetKeyPressed(OF_KEY_CONTROL));

  // Add printable ASCII characters to buffer text
  if (!cmd && key < 127 && key > 31) {
    buf[currentBuffer]->insert(key);
  }

  // Add new line to buffer text
  if (key == OF_KEY_RETURN) {
    buf[currentBuffer]->insert('\n');
  }

  // Pass backspace delete to text buffer
  if (key == OF_KEY_BACKSPACE) {
    buf[currentBuffer]->backspace();
  }

  // Pass clear command to text buffer
  if (cmd && key == 'n') {
    buf[currentBuffer]->clear();
  }

  // Move cursor around with arrow keys
  if (key == OF_KEY_UP) {
    buf[currentBuffer]->moveCursorRow(-1, shift, cmd);
  }
  if (key == OF_KEY_DOWN) {
    buf[currentBuffer]->moveCursorRow(1, shift, cmd);
  }
  if (key == OF_KEY_LEFT) {
    buf[currentBuffer]->moveCursorCol(-1, shift, cmd);
  }
  if (key == OF_KEY_RIGHT) {
    buf[currentBuffer]->moveCursorCol(1, shift, cmd);
  }

  if (cmd && key == 'x') {
    ClipBoard::setText(buf[currentBuffer]->getSelection());
    buf[currentBuffer]->removeSelection();
  }
  if (cmd && key == 'c') {
    ClipBoard::setText(buf[currentBuffer]->getSelection());
  }
  if (cmd && key == 'v') {
    buf[currentBuffer]->insert(ClipBoard::getText());
  }

  // Tab through buffers
  // Cmd/Ctrl + Tab: goes to the next buffer
  // Cmd/Ctrl + Shift + Tab: goes to the previous buffer
  if (cmd && key == OF_KEY_TAB) {
    if (shift) {
      if (--currentBuffer < 0) {
        currentBuffer = maxBuffer;
      }
    } else if (++currentBuffer > maxBuffer) {
      currentBuffer = 0;
    }
  }

  // If only Tab is pressed we insert 2 spaces
  // TODO: this is hard coded at the moment
  if (!cmd && !shift && key == OF_KEY_TAB) {
    buf[currentBuffer]->insert("  ");
  }

  // Switch buffer using cmd + number
  if (cmd && key >= '0' && key <= '9') {
    // 0 key always goes to the last buffer
    if (key == '0') {
      currentBuffer = maxBuffer;
    } else {
      auto newBuffer = key - 49;
      currentBuffer = std::min(newBuffer, maxBuffer);
    }
  }

  // TODO: figure out why this code is here
  if (cmd) {
    if (cmds.count(key) > 0) {
      pair<void*, EditorCommand> callback = cmds[key];
      (*callback.second)(callback.first);
    }
  }

  // Key has been pressed so update the editor fbo
  update();
}

void
ofxEditor::draw()
{
  ofPushStyle();
  ofDisableLighting();
  ofSetColor(255, 255, 255, 255);
  editorFbo.draw(0, 0);
  ofPopStyle();
}

void
ofxEditor::update()
{
  ofPushStyle();
  editorFbo.begin();
  ofClear(0, 0, 0, 0);

  // ofSetColor(255, 0, 0, 200);
  // ofRect(40,20,ofGetWidth() - 100, ofGetHeight() - 50);
  ofSetColor(255, 255, 255, 255);
  ofFill();
  buf[currentBuffer]->draw(40, 20, ofGetWidth() - 100, ofGetHeight() - 50);

  editorFbo.end();
  ofPopStyle();
}

void
ofxEditor::windowResized(ofResizeEventArgs& resize)
{
  ofFbo::Settings settings;
  settings.width = resize.width;
  settings.height = resize.height;
  editorFbo.allocate(settings);
  editorFbo.begin();
  ofClear(0, 0, 0, 0);
  editorFbo.end();
}

bool
ofxEditor::loadFile(string filename, int whichBuffer)
{

  if (whichBuffer < 0 || whichBuffer > maxBuffer)
    return false;

  string path = ofToDataPath(filename);
  ofFile file;
  if (!file.open(ofToDataPath(path), ofFile::ReadOnly)) {
    return false;
  }
  buf[whichBuffer]->setText(file.readToBuffer().getText());
  file.close();
  return true;
}

bool
ofxEditor::saveFile(string filename, int whichBuffer)
{

  if (whichBuffer < 0 || whichBuffer > maxBuffer)
    return false;

  string path = ofToDataPath(filename);

  ofFile file;
  if (!file.open(path, ofFile::WriteOnly)) {
    return false;
  }

  file << buf[whichBuffer]->getText();
  file.close();

  return true;
}

