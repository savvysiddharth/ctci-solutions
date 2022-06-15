#include <iostream>
#include <vector>
using namespace std;


void decFracToBin(double x) {
  int bitsCount = 0;
  int bitsLimit = 32;
  string bits = "0.";
  while(x != 0) {
    x = x*2;
    int bit = x;
    if(++bitsCount > bitsLimit) break;
    bits += to_string(bit);
    x = x - bit;
  }
  if(bitsCount > bitsLimit) cout << "ERROR." << endl;
  else cout << bits << endl;
}

int main() {
  double x = 0.375;
  decFracToBin(x);
}