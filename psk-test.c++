#include "psk.h++"

#include <iostream>
#include <Magick++.h>

using namespace drg::modulation;
using namespace std;
using namespace Magick;


constellations c;

int main(int argc, char **argv) {
  psk modulator(.5, 2, 2, c.get("4qam"));

  vector<pair<double, double> > data;
  Image im("1056x400", "black");


  vector<unsigned int> split = modulator.split("foo");
  for (vector<unsigned int>::iterator i = split.begin() ; i < split.end() ; i++) {
    cout << *i << endl;
  }

  data = modulator.generate("baz", .001);

  cout << data.size() << endl;
  
  double t_max = data.back().first;
  cout << "t_max = " << t_max << endl;


  for ( double t = 0 ; t < t_max ; t++) {
    im.strokeColor("blue");
    unsigned int x = 1050 * t / t_max;
    im.draw(DrawableLine(x, 1, x, 399));
  } 

  for (vector<pair<double, double> >::iterator i = data.begin() ; i < data.end() ; i++) {
    double t = (*i).first;
    im.pixelColor(1050 * t / t_max, 200 + ((*i).second * 100), "white");
  }

  im.display();

  



  return 0;
}
