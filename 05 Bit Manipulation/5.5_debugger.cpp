// Though this is a not a coding question...
// But writing it in a form of coding answer
#include <iostream>
using namespace std;

// This function checks whether n is power of 2 or not.
bool checkIfPowerOf2(int n) {
  int test = n & (n-1);
  return (n & (n-1)) == 0;
}


int main() {
  int n = 256;
  if(checkIfPowerOf2(n)) cout << "yes, " << n << " is power of 2." << endl;
  else cout << "nope, it ain't it." << endl;
}