#include <iostream>
using namespace std;

int rmult(int a, int b, int shift, int psum) {
  if(b >> shift == 0) return psum;
  int bit = (b >> shift) & 1;
  if(bit) psum += a << shift;
  int ans = rmult(a, b, shift+1, psum);
  return ans;
}

int mult(int a, int b) {
  return rmult(a,b,0,0);
}

int main() {
  int a = 13;
  int b = 13;

  cout << mult(a,b) << endl;
}