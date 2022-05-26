#include <iostream>
using namespace std;

bool isSubstring(string s1, string s2) { // from gfg
  int M = s1.length(); // smaller string
  int N = s2.length();

  for (int i = 0; i <= N - M; i++) {
    int j;
    for (j = 0; j < M; j++)
      if (s2[i + j] != s1[j])
        break;
    if (j == M)
        return true;
  }

  return false;
}

// Time: O(N), Space: O(N)
// if s2 is rotation of s1 then s1 must be a subtring of s2+s2
bool isRotation(string s1, string s2) {
  if(s1.length() != s2.length()) return false;

  string two_s2 = s2 + s2;
  if(isSubstring(s1, two_s2)) return true;
  else return false;
}

int main() {
  if(isRotation("waterbottle", "erbottlewat")) cout << "yep\n";
  else cout << "nope\n";
}