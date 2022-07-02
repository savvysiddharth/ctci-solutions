#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// Time: O(nlogn)
// Space: O(n)
vector<int> alternatePeakAndValley(vector<int> ivec) {
  sort(ivec.begin(), ivec.end());
  int i=0, j=ivec.size()-1;
  vector<int> result {};
  while(i<=j) {
    if(i == j) {
      result.push_back(ivec[i]);
      return result;
    } else {
      result.push_back(ivec[j--]);
      result.push_back(ivec[i++]);
    }
  }
  return result;
}

void printVector(vector<int> arr) {
  cout << "Vec: [ ";
  for(auto item : arr) {
    cout << item << " ";
  }
  cout << "]" << endl;
}

// Time: O(n)
// Space: O(1)
void alternateFaster() {
  // sliding window approach
  // window of 3, rearrange these 3 to have max at middle
  // move the window by 2 steps, and repeat above
  // too lazy to code it now.. will do it later..
  // Zzzz...
}

int main() {
  // vector<int> ivec{5,3,1,2,3};
  // vector<int> ivec{5,8,6,2,3,4,6};
  vector<int> ivec{0,1,4,7,8,9};

  vector<int> result = alternatePeakAndValley(ivec);

  printVector(result);
}