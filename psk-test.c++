#include "psk.h++"

#include <iostream>
#include <Magick++.h>

using namespace drg::modulation;
using namespace std;
using namespace Magick;


constellations c;

int main(int argc, char **argv) {
  psk modulator(1, 2, 1, c.get("4qam"));

  vector<pair<double, double> > data;
  Image im("1056x400", "black");


  vector<unsigned int> split = modulator.split("foo");
  for (vector<unsigned int>::iterator i = split.begin() ; i < split.end() ; i++) {
    cout << *i << endl;
  }

  data = modulator.generate("baz", .08);

  cout << data.size() << endl;
  
  /*  unsigned int cnt = 0;
  for (unsigned int x = 40 ; x < 1056 ; x += 40) {
    cnt++;
    if (cnt==8) {
      im.strokeColor("blue");
      cnt = 0;
    } else {
      im.strokeColor("red");
    }
    im.draw(DrawableLine(x, 1, x, 399));
    
  } */


  unsigned int x = 0 ;
  for (vector<pair<double, double> >::iterator i = data.begin() ; i < data.end() ; i++) {
    im.pixelColor(x, 200 + ((*i).second * 100), "white");

    x++;

  }

  im.display();

  



  return 0;
}
