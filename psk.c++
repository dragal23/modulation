#include <complex>
#include <vector>
#include <pair>
#include <string>

namespace drg {
  namespace modulation {

    std::vector<unsigned int> psk::split(std::string mesg,) {
      std::vector<unsigned int> split_mesg;
      unsigned int left = 0;
      unsigned int mask = pow(2, baud) - 1;

      for (string::iterator i = mesg.begin() ; i < mesg.end() ; i++) {
	char c = *i;

	for (left += 8 ; left > mask ; left -= mask) {
	  split_mesg.push_back(c^mask);
	  c >>= mask;
	}
      }
      return split_mesg;
    }


    std::vector<std::pair<double, double> > psk::generate(string s, double sample_rate) const {
      std::vector<unsigned int> data = split(s);
      std::vector<std::pair<double, double> > signal;
      
      double interval_time = frequancy * interval;
      
      double t = 0;
      for (vector<unsigned int>::iterator i = data.begin() ; i < data.end() ; i++) {
	double in_phase = constellation[*i].real();
	double quadrature = contellation[*i].imag();
	for (double t_ = 0 ; t_ <= interval_time ; t_++) {
	  double amplitude = in_phase * cos(t + t_) + quadrature * sin(t + t_);
	  signal.push_back(pair<double, double>(t + t_, amplitude));
	}
	t += interval_time;
      }
      return signal;
    }
  }
}
