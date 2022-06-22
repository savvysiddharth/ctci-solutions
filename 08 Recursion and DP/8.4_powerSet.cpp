#include <set>
#include <iostream>
using namespace std;

void subset(set<int> currSet, set<set<int>> &powerset) {
  if(currSet.size() == 0) return;
  powerset.insert(currSet);
  for(auto item : currSet) {
    set<int> tempSet = currSet;
    tempSet.erase(item);
    subset(tempSet, powerset);
  }
}

void printPowerSet(set<set<int>> &powerset) {
  for(auto set : powerset) {
    cout << "{ ";
    for(auto setItem : set) {
      cout << setItem << " ";
    } cout << "}" << endl;
  }
}

int main() {
  set<set<int>> powerset {{}};
  set<int> iset {1,2,3};
  
  subset(iset, powerset);

  printPowerSet(powerset);
}