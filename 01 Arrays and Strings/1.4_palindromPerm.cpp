// palindrom permutation
#include <iostream>
#include <unordered_map>
using namespace std;

// Whether a given string is permutation of a palindrome?

// Time: O(N)
// Space: O(N)
// Logic: For each character count should be even except for atmost one character
bool isPalindromePerm(string istr) {
  unordered_map<char,int> charmap;
  int oneCount = 0;
  for(int i=0; i<istr.length(); i++) {
    char currChar = istr[i];
    if(currChar == ' ') continue;
    if(charmap.find(currChar) == charmap.end()) {
      oneCount++;
      charmap[currChar] = 1;
    } else { // pair complete
      if(charmap[currChar] == 1) {
        oneCount--;
        charmap.erase(currChar);
      }
    }
  }
  if(oneCount <= 1) return true;
  else return false;
}


// Time: O(N)
// Space: O(1)
// Using Bit Manipulation, assuming only small letters will be used
bool isPalindromePerm_lowMem(string istr) {
  int checker = 0; // 32 bits
  for(int i=0; i<istr.length(); i++) {
    if(istr[i] == ' ') continue;
    int alphaIndex = istr[i] - 'a'; // a=0, b=1, c=2, ....
    int temp = 1; 
    temp = temp << alphaIndex;
    checker = checker ^ temp;
  }
  if((checker & (checker-1)) == 0 || checker == 0) return true;
  else return false;
}

int main() {
  if(isPalindromePerm_lowMem("taco cat")) {
    cout << "yep\n";
  } else {
    cout << "nope\n";
  }
}