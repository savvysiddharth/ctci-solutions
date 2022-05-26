#include <iostream>
#include <vector>
using namespace std;

void printArray(vector<vector<int>> &matrix) {
  for(int i=0; i<matrix.size(); i++) {
    for(int j=0; j<matrix[0].size(); j++) {
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

  printArray(rotMatrix);
}

// Time: O(?)
// Space: O(1)
void rotateMatrix_lowMem(vector<vector<int>> &matrix) {
  for(int i=0;)
}

int main() {
  vector<vector<int>> matrix = {
    {1,2,3},
    {4,5,6},
    {7,8,9}
  };
  // printArray(matrix);
  rotateMatrix_lowMem(matrix);
}