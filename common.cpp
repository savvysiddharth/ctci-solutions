#include <bits/stdc++.h>
using namespace std;

// hash function for pair
// (STL doesn't have hash function of pair by default)
struct hash_pair {
  template <class T1, class T2>
  size_t operator()(const pair<T1, T2> &p) const {
    auto hash1 = hash<T1>{}(p.first);
    auto hash2 = hash<T2>{}(p.second);
    if (hash1 != hash2) return hash1 ^ hash2;             
    return hash1;
  }
};

void printArray(long arr[], int n) {
  for(int i=0; i<n; i++) {
    cout << arr[i] << " ";
  } cout << endl;
}

void printVectorOfPairs(vector<pair<int,int>> vec) {
  for(int i=0; i<vec.size(); i++) {
    cout << vec[i].first << "," << vec[i].second << " ";
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