#include <Magick++.h>
#include <complex>
#include <vector>
#include <pair>
#include <string>

namespace drg {
  namespace modulation {

    class psk {
    private:
      // The interval between phase shifts in cycles.
      double interval;
      // The number of bits per transition.
      const unsigned int baud;
      double frequancy;
      std::map<unsigned char, complex<double> > constellation;



    public:
      psk()
	: interval(1), baud(1), frequancy(1) {
	constillation[0] = std::complex<double>(1, 0);
	constillation[1] = std::complex<double>(-1, 0);
      }
      psk(std::map<unsigned char, complex<double> > constellation_)
	: interval(1), baud(1), frequancy(1), constellation(contellation_) { }

      psk(double interval_, insigned int baud_, double frequancy_, std::map<unsigned char, complex<double> > constellation_)
	:: interval(interval_), baud(baud_), frequancy(frequancy_), constellation(contellation_) { }



      std::queue<unsigned int> split_message(std::string mesg);

      std::vector<std::pair<double, double> > generate(string s, double sample_rate) const;
    }
  }
}
