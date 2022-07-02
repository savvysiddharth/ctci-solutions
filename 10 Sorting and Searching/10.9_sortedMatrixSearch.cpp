#include <iostream>
#include <vector>
using namespace std;

// Time: O(m+n)
bool searchMatrix(vector<vector<int>>& matrix, int target) {
  int row = 0;
  int col = matrix[0].size()-1;
  while(row < matrix.size() && col >= 0) {
    if(matrix[row][col] == target) return true;
    else if(matrix[row][col] < target) row++;
    else col--;
  }
  return false;
}

int main() {
  vector<vector<int>> matrix {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
  int target = 5;
  if(searchMatrix(matrix, target)) {
    cout << "found :)" << endl;
  } else cout << "not found :(" << endl;
}

// Tested on : https://leetcode.com/problems/search-a-2d-matrix-ii/