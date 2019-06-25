#pragma once

//  Created by Darren Mothersele on 19/11/2013.

#include <ofMain.h>

class EditorBuffer
{
public:
  EditorBuffer(ofTrueTypeFont* f);

  void insert(int);
  void insert(const string);
  void backspace();
  void clear();

  std::string getText();
  void setText(string);

  void moveCursorRow(int direction, bool shift, bool cmd);
  void moveCursorCol(int direction, bool shift, bool cmd);

  void setTextColor(ofColor, ofColor);
  void setCursorColor(ofColor);
  void setHighlightColor(ofColor);

  const std::string getSelection();
  void removeSelection();

  void setCursorPosition(int, int);
  int getCurrentRow();
  int getCurrentCol();

  void draw(float, float, float, float);
  ofRectangle getBoundingBox();
  void updateShapes();
  void updateBounds();
  void drawStrings();
  void drawCursor();

private:
  void updateSelect(bool);

  std::string m_text;
  std::string::iterator m_cursorPosition;
  std::string::iterator m_selectStart;
  std::string::iterator m_selectEnd;

  ofColor m_textColor;
  ofColor m_textBorderColor;
  ofColor m_cursorColor;
  ofColor m_highlightColor;

  float m_lineHeight;
  float m_charWidth;
  ofTrueTypeFont* m_font;

  std::vector<ofPath> m_shapes;
  ofRectangle m_bounds;
  ofPoint m_cursorPoint;

};
