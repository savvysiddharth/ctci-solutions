#include <iostream>
#include <unordered_map>
using namespace std;

void perms(string prefix, unordered_map<char,int> map) {
  if(map.size() == 0) {
    cout << prefix << endl;
    return;
  };
  for(auto chInt : map) {
    char ch = chInt.first;
    int count = chInt.second;
    string newPrefix = prefix;
    newPrefix.push_back(ch);
    unordered_map<char, int> newMap = map;
    if(count-1 > 0) newMap[ch] = count-1;
    else newMap.erase(ch);
    perms(newPrefix, newMap);
  }
}

int main() {
  unordered_map<char,int> map;

  string istr = "aaabc";

  for(auto ch : istr)
    if(map.find(ch) == map.end()) map.insert({ch,1});
    else map[ch]++;

  perms("", map);
}