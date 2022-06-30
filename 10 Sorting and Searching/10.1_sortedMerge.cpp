#include <iostream>
#include <vector>
using namespace std;

void printArray(int arr[], int n) {
  cout << "Vec: [ ";
  for(int i=0; i<n; i++) {
    cout << arr[i] << " ";
  } cout << "]" << endl;
}

// Time: O(m+n)
// Space: O(1)
void merge(int arr1[], int arr2[], int a1_len, int a2_len) {
  int m = a1_len + a2_len - 1;
  int i = a1_len - 1, j = a2_len - 1;
  while(j >= 0) {
    if(arr1[i] == arr2[j]) {
      arr1[m--] = arr1[i--];
      arr1[m--] = arr2[j--];
    } else if(arr1[i] > arr2[j]) arr1[m--] = arr1[i--];
    else arr1[m--] = arr2[j--];
  }
}

int main() {
  int arr1[] = {1,3,8,11,39 -1, -1, -1};
  int arr2[] = {2,6,9};

  merge(arr1, arr2, 5, 3);

  printArray(arr1, 8);
}