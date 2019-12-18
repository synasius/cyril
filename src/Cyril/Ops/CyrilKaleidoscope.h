#pragma once

#include "Cyril.h"

class CyrilKaleidoscope : public Cyril
{
protected:
  std::unique_ptr<Cyril> m_e;
  int m_s;

public:
  CyrilKaleidoscope(std::unique_ptr<Cyril> e);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
  void update(CyrilState&) override;
};
