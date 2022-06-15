#include <iostream>
using namespace std;

void clearBit(int &x, int i) {
  x = x & ~(1 << i);
}

// Time: O(j-i)
int doInsert(int M, int N, int i, int j) {
  for(int k=i; k<=j; k++) clearBit(N,k);
  return N | (M << i); 
}

// Time: O(1)
int doInsert_fast(int M, int N, int i, int j) {
  int right = (1 << i) - 1;
  int left = ~0 << (j+1);
  N = N & (left|right);
  return N | (M << i); 
}

int main() {
  int N = 0b10000100000;
  int M = 0b10011;

  int ans = 0b10001001100;

  cout << M << " " << N << endl;
  cout << "expected answer: " << ans << endl;

  cout << "actual answer: " << doInsert_fast(M,N,2,6) << endl;
}