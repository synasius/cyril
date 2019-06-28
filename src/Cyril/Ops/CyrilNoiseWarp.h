
#include "Cyril.h"

class CyrilNoiseWarp : public Cyril
{
protected:
  Cyril* e;
  int s;

public:
  CyrilNoiseWarp(Cyril* _e);
  CyrilNoiseWarp(const CyrilNoiseWarp& other);
  ~CyrilNoiseWarp() override;
  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
  void update(CyrilState&) override;
};
