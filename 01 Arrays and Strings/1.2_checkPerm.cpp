#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> mylist;

  double num = 0;
  while(true) {
    mylist.push_back(num);
    num += 0.01;
  }
}