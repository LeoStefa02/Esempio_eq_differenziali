#include "./FunzioniUtili/FunzioneVettorialeBase.h"

class FunzioneVettoriale : public FunzioneVettorialeBase {

public:
  FunzioneVettoriale(double alpha) { m_alpha = alpha; };
  vector<double> eval(double t, const vector<double> &x) const override {
    double B = pow(x[0] * x[0] + x[1] * x[1], m_alpha);
    return vector<double>{x[2], x[3], B * x[3], - B * x[2]};
  }

  void set_alpha(double alpha) { m_alpha = alpha; }

private:
  double m_alpha;
};