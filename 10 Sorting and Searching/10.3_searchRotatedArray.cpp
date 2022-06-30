#include <iostream>
#include <vector>
using namespace std;

int search(vector<int> &arr, int target) {
  int low = 0, high = arr.size()-1;
  while(low <= high) {
    int mid = (low + high)/2;
    if(arr[mid] == target) return mid;
    if(target > arr[mid]) {
      if(arr[mid] > arr[high]) low = mid+1; // if right is non-sorted, it must be there
      else if(target > arr[high]) high = mid-1; // go left, if right sorted and target exceeds highest right
      else low = mid+1; // go right
    }
    if(target < arr[mid]) {
      if(arr[mid] < arr[low]) high = mid-1; // if left is non-sorted, it must be there
      else if(target < arr[low]) low = mid+1; // go right, if left sorted and target is lower than lowest left
      else high = mid-1; // go left
    }
  }
  return -1;
}

int main() {
  vector<int> iarr {15,16,19,20,25,1,3,4,5,7,10};
  int target = 4;
  cout << search(iarr, target) << endl;
}

// Tested on: https://leetcode.com/problems/search-in-rotated-sorted-array/