#pragma once

//  Created by Darren Mothersele on 19/11/2013.

#include "ClipBoard.h"
#include "EditorBuffer.h"

#include <ofMain.h>

typedef void (*EditorCommand)(void*);

class ofxEditor
{
public:
  ofxEditor(int noBuffers = 1, string fontname = "DroidSansMono.ttf");

  void addCommand(int key, void* _o, EditorCommand _c)
  {
    cmds[key] = make_pair(_o, _c);
  }

  void handleKeyPress(ofKeyEventArgs&);

  void draw();
  void update();

  void windowResized(ofResizeEventArgs&);

  vector<EditorBuffer*> buf;
  int currentBuffer;
  int maxBuffer;

  bool loadFile(string filename, int whichBuffer);
  bool saveFile(string filename, int whichBuffer);

private:
  ofFbo editorFbo;
  ofTrueTypeFont m_font;

  ofColor textColor;
  ofColor textBorderColor;
  ofColor cursorColor;
  ofColor highlightColor;

  map<int, pair<void*, EditorCommand>> cmds;
};

