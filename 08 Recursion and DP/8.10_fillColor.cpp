#include <iostream>
#include <vector>
using namespace std;

int size = 6;

vector<vector<int>> screen {{1,1,1,1,1,1},
                            {1,1,0,0,1,1},
                            {1,1,0,0,0,1},
                            {1,1,0,0,0,0},
                            {1,1,0,0,0,0},
                            {1,1,0,0,0,0}};

void print2DVector(vector<vector<int>> matrix) {
  for(int i=0; i<matrix.size(); i++) {
    for(int j=0; j<matrix[0].size(); j++) {
      if(matrix[i][j] < 10) cout << "0";
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

void fill(int x, int y, int &col, int &baseColor) {
  if(x >= size || y >= size || x < 0 || y < 0) return;
  if(screen[x][y] == baseColor) screen[x][y] = col;
  else return;
  fill(x+1, y, col, baseColor);
  fill(x-1, y, col, baseColor);
  fill(x, y+1, col, baseColor);
  fill(x, y-1, col, baseColor);
}


int main() {
  print2DVector(screen);
  int color = 44;
  int x = 3;
  int y = 3;
  int baseColor = screen[x][y];
  fill(3, 3, color, baseColor);
  cout << "-----------" << endl;
  print2DVector(screen);
}