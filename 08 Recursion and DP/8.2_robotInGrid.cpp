#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct hash_pair {
  template <class T1, class T2>
  size_t operator()(const pair<T1, T2> &p) const {
    auto hash1 = hash<T1>{}(p.first);
    auto hash2 = hash<T2>{}(p.second);
    if (hash1 != hash2) return hash1 ^ hash2;             
    return hash1;
  }
};

// Time: O(RC)
// Space: O(RC)
// Optimized using memoization
bool reachThere(int row, int col, vector<vector<int>> &grid, bool &found, vector<pair<int,int>> &path, unordered_map<pair<int,int>, bool, hash_pair> &mem) {
  if(row > grid.size()-1 || col > grid[0].size()-1 || grid[row][col] == 1) return false;
  if(row == grid.size()-1 && col == grid[0].size()-1) {
    found = true;
    path.push_back(make_pair(row,col));
    return true;
  }
  bool s1 = false, s2 = false;
  if(!found) {
    if(mem.find(make_pair(row+1,col)) == mem.end()) {
      s1 = reachThere(row+1, col, grid, found, path, mem);
      mem.insert({make_pair(row+1,col), s1});
    }
    else s1 = mem[make_pair(row+1,col)];
  }
  if(!found) {
    if(mem.find(make_pair(row,col+1)) == mem.end()) {
      s2 = reachThere(row, col+1, grid, found, path, mem);
      mem.insert({make_pair(row,col+1), s2});
    }
    else s2 = mem[make_pair(row,col+1)];
  }
  if(s1 || s2) path.push_back(make_pair(row,col));
  return s1 || s2;
}

void printVectorOfPairs(vector<pair<int,int>> vec) {
  for(int i=0; i<vec.size(); i++) {
    cout << "(" << vec[i].first << "," << vec[i].second << ")" << " < ";
  } cout << endl;
}

int main() {
  vector<vector<int>> grid {{0,0,0,0}, // 0 means free cell, 1 is obstacle
                            {0,1,0,0},
                            {1,0,0,0},
                            {0,1,0,0}};

  vector<pair<int,int>> path;
  bool found = false;

  unordered_map<pair<int,int>, bool, hash_pair> mem;

  if(reachThere(0,0, grid, found, path, mem)) printVectorOfPairs(path);
  else cout << "no path exists :(" << endl;
}

