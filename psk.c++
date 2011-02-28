#include "psk.h++"

namespace drg {
  namespace modulation {

    std::vector<unsigned int> psk::split(const std::string mesg) const {
      std::vector<unsigned int> split_mesg;
      unsigned int left = 0;
      unsigned int mask = pow(2, baud) - 1;

      for (std::string::const_iterator i = mesg.begin() ; i < mesg.end() ; i++) {
	char c = *i;

	/// DRG TODO need to modify to handle bauds which dont divide eigth!
	for (left = 8 ; left >= baud ; left -= baud) {
	  split_mesg.push_back(c&mask);
	  c >>= baud;
	}
      }
      return split_mesg;
    }
 

    std::vector<std::pair<double, double> > psk::generate(std::string s, double sample_rate) const {
      std::vector<unsigned int> data = split(s);
      std::vector<std::pair<double, double> > signal;
      
      double interval_time = frequancy * interval * 2 * M_PI;
      
      double t = 0;
      for (std::vector<unsigned int>::iterator i = data.begin() ; i < data.end() ; i++) {
	double in_phase = (*constellation.find(*i)).second.real();
	double quadrature = (*constellation.find(*i)).second.imag();
	for (double t_ = 0 ; t_ < interval_time ; t_ += sample_rate) {
	  double amplitude = in_phase * cos(t + t_) + quadrature * sin(t + t_);
	  signal.push_back(std::pair<double, double>(t + t_, amplitude));
	}
	t += interval_time;
      }
      return signal;
    }
  }
}
