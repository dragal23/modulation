#include "psk.h++"
#include <iostream>

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
      // Produces a vector of time, amplitude pairs.

      std::vector<unsigned int> data = split(s);
      std::vector<std::pair<double, double> > signal;
      
      double interval_time = interval / frequancy;
      
      double t = 0, t_ = 0;
      for (std::vector<unsigned int>::iterator i = data.begin() ; i < data.end() ; i++) {
	double in_phase = (*constellation.find(*i)).second.real();
	double quadrature = (*constellation.find(*i)).second.imag();
	
	//std::cout << "t = " << t << ", t_ = " << t_ << ", " << "I = " << in_phase << ", quadrature = " << quadrature << std::endl;

	for ( ; t_ < interval_time ; t_ += sample_rate) {
	  double amplitude = in_phase   * cos(2 * M_PI * frequancy * (t + t_)) 
	                   + quadrature * sin(2 * M_PI * frequancy * (t + t_));
	  signal.push_back(std::pair<double, double>(t + t_, amplitude));
	}
	t += interval_time;
	t_ -= interval_time;
      }
      return signal;
    }
  }
}
