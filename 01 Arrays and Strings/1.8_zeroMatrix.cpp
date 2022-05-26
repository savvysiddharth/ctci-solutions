#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Modified to print 0 as "**" to make result more visible on terminal
void printMatrix(vector<vector<int>> &matrix) {
  for(int i=0; i<matrix.size(); i++) {
    for(int j=0; j<matrix[0].size(); j++) {
      if(matrix[i][j] == 0) {
        cout << "** "; continue;
      }
      if(matrix[i][j] < 10) cout << "0";
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

// Time: O(N^2)
// Space: O(N)
void zeroMatrix(vector<vector<int>> &matrix) {
  int rows[matrix.size()] = {};
  int cols[matrix[0].size()] = {};
  for(int i=0; i<matrix.size(); i++) {
    for(int j=0; j<matrix[0].size(); j++) {
      if(matrix[i][j] == 0) {
        rows[i] = 1;
        cols[j] = 1;
      }
    }
  }

  for(int row=0; row<matrix.size(); row++)
    if(rows[row])
      for(int j=0; j<matrix[0].size(); j++) // sets entire row to 0
        matrix[row][j] = 0;

  for(int col=0; col<matrix[0].size(); col++)
    if(cols[col])
      for(int i=0; i<matrix.size(); i++) // sets entire col to 0
        matrix[i][col] = 0;
}

// Time: O(N^2)
// Space: O(1)
void zeroMatrix_lowMem(vector<vector<int>> &matrix) {

  bool firstRowHasZero = false;
  for(int i=0; i<matrix[0].size(); i++){
    if(matrix[0][i] == 0) {
      firstRowHasZero = true;
      break;
    }
  }

  bool firstColHasZero = false;
  for(int i=0; i<matrix.size(); i++){
    if(matrix[i][0] == 0) {
      firstColHasZero = true;
      break;
    }
  }

  for(int i=1; i<matrix.size(); i++) {
    for(int j=1; j<matrix[0].size(); j++) {
      if(matrix[i][j] == 0) {
        matrix[0][j] = 0; // using first row as zero column indicator
        matrix[i][0] = 0; // using first col as zero row indicator
      }
    }
  }

  // zero-ing relevant columns
  for(int col=1; col<matrix[0].size(); col++) {
    if(matrix[0][col] == 0) {
      for(int i=0; i<matrix.size(); i++) // sets entire col to 0
        matrix[i][col] = 0;
    }
  }

  // zero-ing relevant rows
  for(int row=1; row<matrix.size(); row++) {
    if(matrix[row][0] == 0) {
      for(int j=0; j<matrix[0].size(); j++) // sets entire row to 0
        matrix[row][j] = 0;
    }
  }

  if(firstColHasZero) {
    for(int i=0; i<matrix.size(); i++)
        matrix[i][0] = 0;
  }

  if(firstRowHasZero) {
    for(int j=0; j<matrix[0].size(); j++) // sets entire row to 0
        matrix[0][j] = 0;
  }
}

int main() {
  vector<vector<int>> matrix = {
    {1,2,3,4,42},
    {5,6,7,0,51},
    {9,3,11,12,1},
    {0,1,11,12,1}
  };
  
  printMatrix(matrix);
  zeroMatrix_lowMem(matrix);
  cout << "------\n";
  printMatrix(matrix);
}