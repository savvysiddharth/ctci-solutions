#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Is given string permutation of other string?

// Time: O(nlogn), Space: O(1) (Assuming modifying input is allowed)
// Logic: Sorting both should make them exactly same
bool checkPermutation_lowMem(string &str1, string &str2) {
  if(str1.length() != str2.length()) return false;
  sort(str1.begin(), str1.end());
  sort(str2.begin(), str2.end());
  if(str1 == str2) return true;
  else return false;
}

// Time: O(n), Space: O(n)
// Logic: Character counts should be exactly same for both
bool checkPermutation(string &str1, string &str2) {
  if(str1.length() != str2.length()) return false;
  unordered_map<char,int> mymap;
  for(int i=0; i<str1.length(); i++) {
    if(mymap.find(str1[i]) != mymap.end()) {
      mymap[str1[i]] += 1;
    } else mymap[str1[i]] = 1;
  }

  for(int i=0; i<str1.length(); i++) {
    if(mymap.find(str2[i]) != mymap.end()) {
      if(mymap[str2[i]] == 0) return false;
      mymap[str2[i]] -= 1;
    } else return false;
  }
  return true;
}

int main() {
  string s1 = "helll";
  string s2 = "ehlol";
  if(checkPermutation(s1,s2)) cout << "is perm\n";
  else cout << "is NOT perm\n";
}