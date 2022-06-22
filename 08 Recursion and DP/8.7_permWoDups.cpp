#include <iostream>
#include <vector>
#include <stack>
using namespace std;


// Without duplicates
void perms(string prefix, string str) {
  if(prefix.length() == 0) {
    cout << str << endl;
    return;
  }
  for(int i=0; i<prefix.length(); i++) {
    string newPrefix = prefix;
    string newStr = str;
    newPrefix.erase(newPrefix.find(prefix[i]), 1);
    newStr.push_back(prefix[i]);
    perms(newPrefix, newStr);
  }
}

int main() {
  perms("1234567890", "");
}