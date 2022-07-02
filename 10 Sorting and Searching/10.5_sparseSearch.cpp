#include <iostream>
#include <vector>
using namespace std;

int sparseSearch(int low, int high, string &target, vector<string> &vec) {
  if(high < low) return 0;
  int mid = (low+high)/2;
  int result = 0;
  if(vec[mid] == target) return mid;
  else if(vec[mid] == "") { // search both sides
    int left = sparseSearch(0, mid-1, target, vec);
    int right = sparseSearch(mid+1, high, target, vec);
    result = left | right;
  } else if(target > vec[mid]) {
    result = sparseSearch(mid+1, high, target, vec);
  } else {
    result = sparseSearch(0, mid-1, target, vec);
  }
  return result;
}

int sparseSearch(vector<string> &vec, string &target) {
  return sparseSearch(0, vec.size()-1, target, vec);
}


int main() {
  vector<string> vec{"at","","","","ball","","","car","","","dad","",""};
  vector<string> vec2{"ab","aac","aaz","car"};

  string target = "car";

  cout << sparseSearch(vec2, target) << endl;
}