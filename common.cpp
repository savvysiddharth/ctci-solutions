#include <bits/stdc++.h>
using namespace std;

void printArray(long arr[], int n) {
  for(int i=0; i<n; i++) {
    cout << arr[i] << " ";
  } cout << endl;
}

void print2DVector(vector<vector<int>> &matrix) {
  for(int i=0; i<matrix.size(); i++) {
    for(int j=0; j<matrix[0].size(); j++) {
      if(matrix[i][j] < 10) cout << "0";
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

void initSquareMatrix(vector<vector<int>> &matrix, int n) {
  matrix.clear(); // sets size of matrix to 0
  for(int i=0; i<n; i++) matrix.push_back(vector<int>(n));
  int val = 1;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      matrix[i][j] = val++;
    }
  }
}