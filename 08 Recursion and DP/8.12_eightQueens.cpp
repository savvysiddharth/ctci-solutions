#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
using namespace std;

// Time: O(n^2) <- for valid configuration
// Space: O(n)
bool onDiagonal(vector<int> queen, vector<vector<int>> &queens) {
  for(auto otherQueen: queens) {
    if(otherQueen[1] == queen[1] || otherQueen[0] == queen[0]) continue;
    double slope = 1.0*(otherQueen[0] - queen[0])/(otherQueen[1] - queen[1]);
    if(slope == 1.0 || slope == -1.0) return true;
  }
  return false;
}

bool isValid(vector<vector<int>> &queens) {
  unordered_set<int> rows, cols;
  for(auto queen : queens) { // checking for row/cols
    if(rows.find(queen[0]) != rows.end() || cols.find(queen[1]) != cols.end())
      return false;
    rows.insert(queen[0]);
    cols.insert(queen[1]);
  }
  for(auto queen: queens) { // checking for diagonal
    if(onDiagonal(queen, queens)) return false;
  }
  return true;
}

void printQueens(vector<vector<int>> &matrix) {
  for(int i=0; i<matrix.size(); i++) {
    cout << "(" << matrix[i][0] << " " << matrix[i][1] << "), ";
  } cout << endl;
}

void nQueens(int row, vector<vector<int>> queens, int &n, int &count, vector<vector<vector<int>>> &result) {
  if(row == n) {
    if(isValid(queens)) {
      result.push_back(queens);
      count++;
      return;
    } else return;
  }
  for(int i=0; i<n; i++) {
    vector<vector<int>> newQueens = queens;
    queens.push_back(vector<int>{row, i});
    if(isValid(queens)) nQueens(row+1, queens, n, count, result);
    queens.pop_back();
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
  nQueens(0, queens, n, count, result);
  // for(auto config : result) {
  //   printQueens(config);
  // }
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
  // printAnswers(answer);
  return count;
}

// queens[i][0] <= x-cord of i'th queen
// queens[i][1] <= y-cord of i'th queen
int main() {
  int n = 4;
  cout << nQueens(n) << endl;

  // vector<vector<int>> queens {{0,5},{1,3},{2,6},{3,0},{4,7},{5,1},{6,4},{7,2}};
  // if(isValid(queens)) cout << "is valid.." << endl;
  // else cout << "NOT valid.." << endl;
}