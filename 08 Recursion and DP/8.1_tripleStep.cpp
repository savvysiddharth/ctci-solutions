#include <iostream>
#define long long long int
using namespace std;

// Time: O(n)
// Space: O(1)
long countWays_optimal(int n) {
  long prev[3] = {1,1,2};
  if(n <= 2) return prev[n];
  long curr;
  for(int i = 3; i<=n; i++) {
    curr = prev[0] + prev[1] + prev[2];
    prev[0] = prev[1];
    prev[1] = prev[2];
    prev[2] = curr;
  }
  return curr;
}

// Time : O(n)
// Space : O(n)
// Memoization approach
long countWays_memoz(long n, long *mem) {
  if(n == 0) return 1;
  long s1,s2,s3;

  if(n-1 >= 0) {
    if(mem[n-1] == 0) {
      s1 = countWays_memoz(n-1, mem);
      mem[n-1] = s1;
    } else s1 = mem[n-1];
  } else s1 = 0;

  if(n-2 >= 0) {
    if(mem[n-2] == 0) {
      s2 = countWays_memoz(n-2, mem);
      mem[n-1] = s2;
    } else s2 = mem[n-2];
  } else s2 = 0;

  if(n-3 >= 0) {
    if(mem[n-3] == 0) {
      s3 = countWays_memoz(n-3, mem);
      mem[n-3] = s3;
    } else s3 = mem[n-3];
  } else s3 = 0;
  
  return s1 + s2 + s3;
}

// Time : O(3^n)
long countWays_slow(long n) {
  if(n == 0) return 1;
  long s1 = 0, s2 = 0, s3 = 0;
  if(n-1 >= 0) s1 = countWays_slow(n-1);
  if(n-2 >= 0) s2 = countWays_slow(n-2);
  if(n-3 >= 0) s3 = countWays_slow(n-3);
  return s1+s2+s3;
}

long countWays(long n) {
  long mem[n+1] = {};
  mem[1] = 1;
  long result = countWays_memoz(n, mem);
  // long result = countWays_slow(n);
  return result;
}

int main() {
  long n = 50;
  cout << countWays_optimal(n) << endl;
}