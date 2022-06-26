#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
using namespace std;

// Time: O(n^2) <- for valid configuration
// Space: O(n)
bool onDiagonal(vector<int> &queen, vector<vector<int>> &queens) {
  for(auto &otherQueen: queens) {
    if(otherQueen[1] == queen[1] || otherQueen[0] == queen[0]) continue;
    double slope = 1.0*(otherQueen[0] - queen[0])/(otherQueen[1] - queen[1]);
    if(slope == 1.0 || slope == -1.0) return true;
  }
  return false;
}

void printQueens(vector<vector<int>> &matrix) {
  for(int i=0; i<matrix.size(); i++) {
    cout << "(" << matrix[i][0] << " " << matrix[i][1] << "), ";
  } cout << endl;
}

void nQueens(int row, vector<vector<int>> queens, int &n, int &count, vector<vector<vector<int>>> &result, unordered_set<int> cols) {
  if(row == n) {
    result.push_back(queens);
    count++;
    return;
  }
  for(int i=0; i<n; i++) {
    if(cols.find(i) == cols.end()) {
      vector<int> nextQueen {row, i};
      if(!onDiagonal(nextQueen, queens)) {
        cols.insert(i);
        queens.push_back(nextQueen);
        nQueens(row+1, queens, n, count, result, cols);
        queens.pop_back();
        cols.erase(i);
      }
    }
  }
}

void printAnswers(vector<vector<string>> answers) {
  for(auto &board : answers) {
    for(auto &row : board) {
      cout << row << endl;
    } cout << "---------------" << endl;
  }
}

int nQueens(int n) {
  vector<vector<int>> queens{};
  vector<vector<vector<int>>> result;
  int count = 0;
  unordered_set<int> cols;
  nQueens(0, queens, n, count, result, cols);
  vector<vector<string>> answer {};
  for(int i=0; i<count; i++) {
    vector<string> currentBoard {};
    for(auto &queen : result[i]) {
      string rowString = "";
      for(int j=0; j<n; j++) {
        if(j == queen[1]) rowString += "Q";
        else rowString += ".";
      }
      currentBoard.push_back(rowString);
    }
    answer.push_back(currentBoard);
  }
  return count;
}

// queens[i][0] <= x-cord of i'th queen
// queens[i][1] <= y-cord of i'th queen
int main() {
  int n = 8;
  cout << nQueens(n) << endl;

  // Example queens vector
  // vector<vector<int>> queens {{0,5},{1,3},{2,6},{3,0},{4,7},{5,1},{6,4},{7,2}};
}

// Tested on: https://leetcode.com/problems/n-queens/