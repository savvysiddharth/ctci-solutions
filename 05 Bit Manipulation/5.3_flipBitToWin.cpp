#include <iostream>
using namespace std;

// Time: O(logN)
// N is the input integer
// Space: O(1)
int maxFlipSeq(int num) {
  int max = -1, currCount = 0, lastZeroSeenAt = -1, i = 0;
  while(num != 0) {
    int bit = num%2;
    num /= 2;
    cout << bit;

    if(bit  == 1) currCount++;
    else if(bit == 0) {
      if(lastZeroSeenAt == -1) {
        lastZeroSeenAt = i;
        currCount++;
      } else {
        if(currCount > max) max = currCount;
        currCount = i - lastZeroSeenAt;
        lastZeroSeenAt = i;
      }
    }

    i++;
  } if(currCount > max) max = currCount;

  cout << endl;

  cout << "max: " << max << endl;

  return max;
}

int main() {
  maxFlipSeq(3487);
}