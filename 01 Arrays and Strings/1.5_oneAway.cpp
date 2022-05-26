#include <iostream>
#include <cstdlib>
using namespace std;

bool isOneAway(string str1, string str2) {
  int diff = str1.length() - str2.length();
  if(abs(diff) > 1) return false;
  int i=0, j=0, count=0;
  while(i<str1.length() && j<str2.length()) {
    if(str1[i] != str2[j]) {
      if(++count > 1) return false;
      if(i+1 < str1.length() && str1[i+1] == str2[j]) { 
        i++; continue; 
      }
      if(j+1 < str2.length() && str2[j+1] == str1[i]) {
        j++; continue;
      }
    }
    i++; j++;
  }
  return true;
}

int main() {
  if(isOneAway("pale", "bale")) {
    cout << "one away\n";
  } else {
    cout << "far away\n";
  }
}