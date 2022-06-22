#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// Time: O(logN)
// All integers are distinct
int findMagicIndex(vector<int> vec) {
  int low = 0, high = vec.size()-1;
  while(low <= high) {
    int mid = (low + high)/2;
    if(vec[mid] == mid) return mid;
    else if(vec[mid] < mid) low = mid+1;
    else if(vec[mid] > mid) high = mid-1;
  }
  return -1;
}

void findMagicIndex(vector<int> &vec, int low, int high) {
  if(low > high) return;
  int mid = (low + high) / 2;
  if(vec[mid] == mid) cout << "Magic index: " << mid << endl;
  findMagicIndex(vec, max(vec[mid], mid+1), high);
  findMagicIndex(vec, low, min(vec[mid], mid-1));  
}

// Time: O(........)
// Integers may be duplicated
void findMagicIndex_II(vector<int> &vec) {
  findMagicIndex(vec, 0, vec.size()-1);
}

int main() {
  vector<int> ivec {-4,-1,1,3,4,5,6,7,8,9,10,11};
  
  vector<int> ivec2 {-10, -5, 2, 2, 2, 3, 4, 7, 9, 12, 13};

  // cout << findMagicIndex(ivec) << endl;

  findMagicIndex_II(ivec2);
}

