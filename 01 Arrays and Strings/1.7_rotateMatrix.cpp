#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void printVector(vector<vector<int>> &matrix) {
  for(int i=0; i<matrix.size(); i++) {
    for(int j=0; j<matrix[0].size(); j++) {
      if(matrix[i][j] < 10) cout << "0";
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

// Time: O(N^2)
// Space: O(N^2)
void rotateMatrix(vector<vector<int>> &matrix) {
  vector<vector<int>> rotMatrix(matrix.size());
  for(int i=0; i<matrix.size(); i++) rotMatrix[i] = vector<int>(matrix.size());

  for(int i=2,k=0; i<matrix.size(); i--,k++) {
    for(int j=0,l=0; j<matrix.size(); j++,l++) {
      rotMatrix[k][l] = matrix[j][i];      
    }
  }

  printVector(rotMatrix);
}

// Time: O(N^2)
// Space: O(1)
void rotateMatrix_lowMem(vector<vector<int>> &matrix) {
  int n = matrix.size();
  
  // first corners
  int start = 0, end = n-1;
  while(n > 1) { // one iteration per each layer
    int left[2] = {start,start};
    int bottom[2] = {end,start};
    int right[2] = {end,end};
    int top[2] = {start,end};
    for(int i=0; i < end-start; i++) { // swapping one cell from each edge at once
      const int TEMP = matrix[left[0]][left[1]];
      matrix[left[0]][left[1]] = matrix[top[0]][top[1]];
      matrix[top[0]][top[1]] = matrix[right[0]][right[1]];
      matrix[right[0]][right[1]] = matrix[bottom[0]][bottom[1]];
      matrix[bottom[0]][bottom[1]] = TEMP;
      left[0]++; // only row increases for left edge
      bottom[1]++; // only col increases for bottom edge
      right[0]--; // only row decreases for right edge
      top[1]--; // only col decreases for top edge
    }

    n -= 2;
    start +=1;
    end = start + n - 1; // update corners for next layer
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

int main() {
  vector<vector<int>> matrix;
  initSquareMatrix(matrix, 9);
  printVector(matrix);
  cout << "-----------\n";
  rotateMatrix_lowMem(matrix);
  printVector(matrix);
  
}