#include <iostream>
using namespace std;

// prints in reverse direction
// LSB is printed first, MSB last
void printBits(int x) {
  int count = 0;
  while(1) {
    count++;
    if(count > 32) break;
    int bit = x & 1;
    cout << bit;
    x >>= 1;
  } cout << endl;
}

void pairWiseSwap(int x) {
  int oddMask = 2;
  for(int i = 0; i<64; i++) { // optimize it by hardcoding mask with relevant 32 bit number
    oddMask <<= 2;
    oddMask |= 1;
  } oddMask <<= 1;
  int evenMask = (oddMask << 1) | 1;
  // oddMask = 0xAAAAAAAA;
  // evenMask = 0x55555555;
  int result = ((x & oddMask) >> 1) | ((x & evenMask) << 1);
  printBits(oddMask);
  printBits(evenMask);
  printBits(x);
  printBits(result);
}

int main() {
  pairWiseSwap(4215236347);
}