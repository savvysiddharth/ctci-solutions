#include <iostream>
using namespace std;

// Time: O(logN)
// N is max(x,y)
// Comparing each bit of each number
int my_bitsToFlip(int x, int y) {
  int count = 0;
  while(x != 0 || y != 0) {
    int bit_x = 0, bit_y = 0;
    if(x != 0) {
      bit_x = x & 1;
      x >>= 1;
    }
    if(y != 0) { 
      bit_y = y & 1;
      y >>= 1;
    }
    if(bit_x != bit_y) count++;
    cout << bit_x << " " << bit_y << endl;
  }
  return count;
}

// Time: O(logN)
// N is max(x,y)
// Simply do XOR of inputs and count 1's
int bitsToFlip(int x, int y) {
  int count = 0;
  for(int z = x^y; z!=0; z >>= 1) count += z & 1;
  return count;
}

int main() {
  int x = 29;
  int y = 15;
  cout << bitsToFlip(x,y) << endl;
}