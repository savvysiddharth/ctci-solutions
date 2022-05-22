// palindrom permutation
#include <bits/stdc++.h>
using namespace std;

// Time: O(N)
// Space: O(N)
bool isPalindromPerm(string istr) {
  unordered_map<char, int> charmap;
  int oneCount = 0;
  int twoCount = 0;
  for(int i=0; i<istr.length(); i++) {
    if(istr[i] == ' ') continue;
    if(charmap.find(istr[i]) == charmap.end()) { // not found
      charmap[istr[i]] = 1;
      oneCount++;
    } else {
      if(charmap[istr[i]] == 1) {
        oneCount--;
        twoCount++;
        charmap.erase(istr[i]);
      }
    }
  }
  if(oneCount <= 1) return true;
  else return false;
}

bool isPalindromePermV2(string istr) {
  int checker = 0; // 32 bits
  for(int i=0; i<istr.length(); i++) {
    if(istr[i] == ' ') continue;
    int curr = istr[i] - 'a';
    int temp = 1;
    temp = temp << curr;
    if((checker & temp) == 0) {
      checker = checker | temp;
    } else {
      checker = checker & ~temp;
    }
  }
  // cout << "checker : " << checker << endl;
  if((checker & (checker-1)) == 0 || checker == 0) return true;
  else return false;
}

int main() {
  if(isPalindromePermV2("tact coa")) {
    cout << "yep\n";
  } else {
    cout << "nope\n";
  }
}