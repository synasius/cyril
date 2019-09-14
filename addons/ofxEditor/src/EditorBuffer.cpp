//  Created by Darren Mothersele on 19/11/2013.

#include "EditorBuffer.h"

EditorBuffer::EditorBuffer(ofTrueTypeFont* _f)
  : m_text()
  , m_cursorPosition(m_text.end())
  , m_selectStart(m_text.end())
  , m_selectEnd(m_text.end())
  , m_font(_f)
{
  m_lineHeight = m_font->getLineHeight();
  m_charWidth = m_font->stringWidth("X") + m_font->getLetterSpacing();
  m_cursorPosition = m_text.end();
  m_selectStart = m_cursorPosition;
  m_selectEnd = m_cursorPosition;
}

string
EditorBuffer::getText()
{
  return m_text;
}

void
EditorBuffer::setText(string t)
{
  m_text = t;
  m_cursorPosition = m_text.end();
  m_selectStart = m_cursorPosition;
  m_selectEnd = m_cursorPosition;
}

void
EditorBuffer::insert(int key)
{
  if (m_selectStart != m_selectEnd) {
    m_cursorPosition = m_text.erase(m_selectStart, m_selectEnd);
  }
  m_cursorPosition = m_text.insert(m_cursorPosition, key);
  m_cursorPosition++;
  updateSelect(false);
}

void
EditorBuffer::insert(const string s)
{
  int loc = m_cursorPosition - m_text.begin();
  m_text.insert(m_cursorPosition, s.begin(), s.end());
  m_cursorPosition = m_text.begin() + loc + s.size();
  updateSelect(false);
}

void
EditorBuffer::updateSelect(bool shift)
{
  if (shift) {
    if (m_cursorPosition > m_selectEnd) {
      m_selectEnd = m_cursorPosition;
    } else if (m_cursorPosition < m_selectStart) {
      m_selectStart = m_cursorPosition;
    }
  } else {
    m_selectStart = m_cursorPosition;
    m_selectEnd = m_cursorPosition;
  }
}

void
EditorBuffer::backspace()
{
  if (m_selectStart == m_selectEnd) {
    if (m_cursorPosition != m_text.begin()) {
      m_cursorPosition--;
      if (m_cursorPosition != m_text.end()) {
        m_cursorPosition = m_text.erase(m_cursorPosition);
      }
    }
  } else {
    m_cursorPosition = m_text.erase(m_selectStart, m_selectEnd);
  }
  updateSelect(false);
}

void
EditorBuffer::setCursorPosition(int c, int r)
{
  if (c >= 0 && r >= 0) {
    int currentRow = 0;
    m_cursorPosition = m_text.begin();
    while (currentRow < r) {
      if (*m_cursorPosition == '\n')
        currentRow++;
      m_cursorPosition++;
    }
    int currentCol = 0;
    while (currentCol < c && *m_cursorPosition != '\n') {
      m_cursorPosition++;
      currentCol++;
    }
  } else {
    m_cursorPosition = m_text.begin();
  }
  // Prevent cursor from moving outside of text
  if (m_cursorPosition < m_text.begin())
    m_cursorPosition = m_text.begin();
  if (m_cursorPosition > m_text.end())
    m_cursorPosition = m_text.end();
}

void
EditorBuffer::clear()
{
  m_text.clear();
  m_cursorPosition = m_text.end();
  m_selectStart = m_cursorPosition;
  m_selectEnd = m_cursorPosition;
}

void
EditorBuffer::moveCursorRow(int direction, bool shift, bool)
{
  setCursorPosition(getCurrentCol(), getCurrentRow() + direction);
  updateSelect(shift);
}

void
EditorBuffer::moveCursorCol(int direction, bool shift, bool cmd)
{
  if (cmd) {
    std::string tofind = " {}[]()\n";

    if (direction == -1) {
      // do not move if cursor is at the beginning fo the text
      if (m_cursorPosition == m_text.begin()) {
        return;
      }

      std::string textToSearch(m_text.begin(), m_cursorPosition - 1);
      auto pos = textToSearch.find_last_of(tofind);
      if (pos != std::string::npos) {
        auto posShift = textToSearch.length() - pos;
        m_cursorPosition -= posShift;
      } else {
        m_cursorPosition = m_text.begin();
      }
      updateSelect(shift);
    }

    if (direction == 1) {
      // do not move if cursor is at the end fo the text
      if (m_cursorPosition == m_text.end()) {
        return;
      }

      std::string textToSearch(m_cursorPosition + 1, m_text.end());
      auto pos = textToSearch.find_first_of(tofind);
      if (pos != std::string::npos) {
        m_cursorPosition += (pos + 1);
      } else {
        m_cursorPosition = m_text.end();
      }
      updateSelect(shift);
    }

  } else {
    if (direction == -1 && m_cursorPosition != m_text.begin()) {
      m_cursorPosition--;
      updateSelect(shift);
    }
    if (direction == 1 && m_cursorPosition != m_text.end()) {
      m_cursorPosition++;
      updateSelect(shift);
    }
  }
}

const string
EditorBuffer::getSelection()
{
  return string(m_selectStart, m_selectEnd);
}

void
EditorBuffer::removeSelection()
{
  m_cursorPosition = m_text.erase(m_selectStart, m_selectEnd);
  updateSelect(false);
}

int
EditorBuffer::getCurrentRow()
{
  // To get current row count number of '\n' characters between
  // m_text.begin and cursorPosition
  int rowNo = 0;
  for (string::iterator i = m_text.begin(); i < m_cursorPosition; i++) {
    if (*i == '\n')
      rowNo++;
  }
  return rowNo;
}

int
EditorBuffer::getCurrentCol()
{
  // To get the current column count the number of characters between
  // cursorPosition and previous '\n' or m_text.begin()
  int colNo = 0;
  for (string::iterator i = m_cursorPosition - 1;
       i >= m_text.begin() && *i != '\n';
       --i) {
    colNo++;
  }
  return colNo;
}

void
EditorBuffer::setTextColor(ofColor _c1, ofColor _c2)
{
  m_textColor = _c1;
  m_textBorderColor = _c2;
}

void
EditorBuffer::setCursorColor(ofColor _c)
{
  m_cursorColor = _c;
}

void
EditorBuffer::setHighlightColor(ofColor _c)
{
  m_highlightColor = _c;
}

void
EditorBuffer::updateBounds()
{
  m_bounds = ofRectangle(0, 0, 0, m_lineHeight);
  std::string ss;
  bool foundCursor = false;

  // keep track of selection areas
  m_shapes.clear();
  ofPath selection;
  ofPoint select;
  bool inHighlight = false;

  for (string::iterator i = m_text.begin(); i < m_text.end(); ++i) {
    if (i == m_cursorPosition) {
      m_cursorPoint = ofPoint(m_font->stringWidth(ss), m_bounds.height);
      foundCursor = true;
    }
    if (i == m_selectStart) {
      select = ofPoint(m_font->stringWidth(ss), m_bounds.height);
      select.y -= m_lineHeight;
      inHighlight = true;
    }
    if (i == m_selectEnd) {
      selection.rectangle(select.x,
                          select.y,
                          m_font->stringWidth(ss) - select.x,
                          m_bounds.height - select.y);
      inHighlight = false;
    }
    if (*i == '\n') {
      if (inHighlight) {
        selection.rectangle(select.x,
                            select.y,
                            m_font->stringWidth(ss) - select.x,
                            m_bounds.height - select.y);
      }
      m_bounds.growToInclude(m_font->stringWidth(ss), m_bounds.height);
      m_bounds.height += m_lineHeight;
      ss.clear();
      if (inHighlight) {
        select = ofPoint(m_font->stringWidth(ss), m_bounds.height);
        select.y -= m_lineHeight;
      }
    } else if (*i == ' ') {
      ss.push_back('_');
    } else {
      ss.push_back(*i);
    }
  }
  if (inHighlight) {
    selection.rectangle(select.x,
                        select.y,
                        m_font->stringWidth(ss) - select.x,
                        m_bounds.height - m_lineHeight - select.y);
  }
  if (!foundCursor) {
    m_cursorPoint = ofPoint(m_font->stringWidth(ss), m_bounds.height);
  }
  m_bounds.growToInclude(m_font->stringWidth(ss), m_bounds.height);

  selection.setColor(m_highlightColor);
  m_shapes.push_back(selection);
}

void
EditorBuffer::drawStrings()
{
  float h = m_lineHeight;
  string ss;
  for (string::iterator i = m_text.begin(); i < m_text.end(); ++i) {
    if (*i == '\n') {
      m_font->drawString(ss, 0, h);
      h += m_lineHeight;
      ss.clear();
    } else {
      ss.push_back(*i);
    }
  }
  m_font->drawString(ss, 0, h);
}

void
EditorBuffer::drawCursor()
{

  ofPushMatrix();
  ofPushStyle();

  ofPopStyle();
  ofPopMatrix();
}

void
EditorBuffer::draw(float x, float y, float w, float h)
{
  ofPushMatrix();
  ofPushStyle();
  ofTranslate(x, y);

  // Need to calculate size of editor before drawing
  updateBounds();

  // Move editor content if cursor is off screen
  float offsetY = h - m_cursorPoint.y;
  if (offsetY < 0) {
    ofTranslate(0, offsetY);
  }
  float offsetX = w - m_cursorPoint.x;
  if (offsetX < 0) {
    ofTranslate(offsetX, 0);
  }

  // Draw selected text highlight
  for (const auto& path: m_shapes) {
    path.draw();
  }

  // Draw text buffer content
  ofSetColor(m_textColor);
  drawStrings();

  // Draw cursor
  ofSetColor(m_cursorColor);
  ofDrawRectangle(m_cursorPoint, 10, -m_lineHeight);

  ofPopStyle();
  ofPopMatrix();
}

void
EditorBuffer::updateShapes()
{
  m_shapes.clear();
  ofPoint location(0, m_lineHeight);
  bool foundCursor = false;
  bool inHighlight = false;
  ofPoint select;
  ofPath selection;
  selection.setColor(m_highlightColor);
  ofPath cursor;
  cursor.setColor(m_cursorColor);
  string ss;

  for (string::iterator i = m_text.begin(); i < m_text.end(); ++i) {
    if (i == m_cursorPosition) {
      m_cursorPoint = ofPoint(location.x, location.y);
      cursor.rectangle(location.x, location.y, 10, -m_lineHeight);
      foundCursor = true;
    }
    if (i == m_selectStart) {
      select = location;
      select.y -= m_lineHeight;
      inHighlight = true;
    }
    if (i == m_selectEnd) {
      selection.rectangle(
        select.x, select.y, location.x - select.x, location.y - select.y);
      inHighlight = false;
    }
    if (*i == '\n') {
      m_font->drawString(ss, 0, location.y);
      ss.clear();
      if (inHighlight) {
        selection.rectangle(
          select.x, select.y, location.x - select.x, location.y - select.y);
      }
      location.x = 0;
      location.y += m_lineHeight;
      if (inHighlight) {
        select = location;
        select.y -= m_lineHeight;
      }
    } else if (*i == ' ') {
      ss.push_back(' ');
      location.x += m_charWidth;
    } else {
      /*
      ofTTFCharacter c = font->getCharacterAsPoints(*i);
      c.setStrokeColor(textBorderColor);
      c.setStrokeWidth(1);
      ofSetColor(textColor);
      shapes.push_back(c);
      shapes.back().translate(location);
      */
      // font->drawString(*i, location.x, location.y);
      ss.push_back(*i);
      location.x += m_charWidth;
    }
  }
  if (inHighlight) {
    selection.rectangle(
      select.x, select.y, location.x - select.x, location.y - select.y);
  }
  if (!foundCursor) {
    m_cursorPoint = ofPoint(location.x, location.y);
    // cursor.rectangle(location.x, location.y, 10, -lineHeight);
    cursor.rectangle(m_font->stringWidth(ss), location.y, 10, -m_lineHeight);
  }
  m_font->drawString(ss, 0, location.y);
  m_shapes.push_back(cursor);
  m_shapes.push_back(selection);

  m_bounds = ofRectangle(0, 0, 0, 0);
  for (const auto& shape : m_shapes) {
    for (const auto& line : shape.getOutline()) {
      m_bounds.growToInclude(line.getBoundingBox());
    }
  }
}
