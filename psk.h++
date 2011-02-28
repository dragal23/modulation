
#if !defined __DRG_MODULATION_PSK_H
#define __DRG_MODULATION_PSK_H

#include <complex>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <cmath>
namespace drg {
  namespace modulation {


    class constellations {
    private:
      std::map<std::string, std::map<unsigned char, std::complex<double> > > lookup;
    public:
      constellations() {
	lookup["bpsk"][0] = std::complex<double>(1, 0);
	lookup["bpsk"][1] = std::complex<double>(-1, 0);
	
	double a = sqrt(0.5);
	lookup["4qam"][0] = std::complex<double>(-a, -a);
	lookup["4qam"][1] = std::complex<double>(-a, a);
	lookup["4qam"][2] = std::complex<double>(a, a);
	lookup["4qam"][3] = std::complex<double>(a, -a);
	
      }
      
      const std::map<unsigned char, std::complex<double> > &get(std::string name) {
	std::map<std::string, std::map<unsigned char, std::complex<double> > >::iterator i;
	return lookup[name];
      }
    };
    
    


    class psk {
    private:
      // The interval between phase shifts in cycles.
      double interval;
      // The number of bits per transition.
      const unsigned int baud;
      double frequancy;
      std::map<unsigned char, std::complex<double> > constellation;



    public:
      psk()
	: interval(1), baud(1), frequancy(1) {
	constellation[0] = std::complex<double>(1, 0);
	constellation[1] = std::complex<double>(-1, 0);
      }
      psk(std::map<unsigned char, std::complex<double> > constellation_)
	: interval(1), baud(1), frequancy(1), constellation(constellation_) { }

      psk(double interval_, unsigned int baud_, double frequancy_, std::map<unsigned char, std::complex<double> > constellation_)
	: interval(interval_), baud(baud_), frequancy(frequancy_), constellation(constellation_) { }



      std::vector<unsigned int> split(const std::string mesg) const;

      std::vector<std::pair<double, double> > generate(std::string s, double sample_rate) const;
    };
  }
}


#endif // #if !define __DRG_MODULATION_PSK_H
