#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

// Time: O(n)
// Using streamstream is faster, as we avoid concat operation at each iteration
string compressString(string str) {
  stringstream result;
  int currCount = 0;
  for(int i=0; i<str.length(); i++) {
    currCount++;
    if(str[i] != str[i+1]) {
      result << str[i] << to_string(currCount);
      currCount = 0;
    }
  }
  if(result.str().length() < str.length()) return result.str();
  else return str;
}

int main() {
  cout << compressString("aabcccccaaa") << endl;
}