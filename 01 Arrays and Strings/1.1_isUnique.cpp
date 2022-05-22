#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

// O(n) time, O(n) space
bool isUnique(string &istr) {
  unordered_map<char,int> mymap;

  for(int i=0; i<istr.length(); i++) {
    if(mymap.find(istr[i]) != mymap.end()) return false;
    else mymap.insert({istr[i],1});
  }
  return true;
}

// O(nlogn) time, O(1) space
bool isUnique_lowMem(string &istr) {
  if(istr.length() < 2) return true;
  sort(istr.begin(), istr.end());
  
  char lastChar = istr[0];
  for(int i=1; i<istr.length(); i++) {
    if(istr[i] == lastChar) return false;
    else lastChar = istr[i];
  }
  return true;
}

int main() {
  string mystr;
  cout << "Enter string: ";
  getline(cin, mystr);
  if(isUnique(mystr)) cout << "isUnique() => TRUE" << endl;
  else cout << "isUnique() -> FALSE" << endl;

  if(isUnique_lowMem(mystr)) cout << "isUnique_lowMem() => TRUE" << endl;
  else cout << "isUnique_lowMem() -> FALSE" << endl;

  cout << mystr << endl;
}