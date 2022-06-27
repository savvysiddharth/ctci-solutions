#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

int stackOfBoxes(vector<vector<int>> &boxes, int topIndex, vector<int> &mem) {
  vector<int> &top = boxes[topIndex];
  int maxHeight = 0;
  for(int i=topIndex+1; i<boxes.size(); i++) {
    vector<int> &nbox = boxes[i]; // potential next box
    if(top[0] >= nbox[0] && top[1] >= nbox[1] && top[2] >= nbox[2]) {
      int height;
      if(mem[i] == -1) {
        height = stackOfBoxes(boxes, i, mem);
        mem[i] = height;
      } else height = mem[i];
      maxHeight = max(height, maxHeight);
    }
  }
  return top[2] + maxHeight;
}

static bool comp(const vector<int> &vec1, const vector<int> &vec2){
  if(vec1[2] > vec2[2]) return true;
  else if(vec1[2] == vec2[2]) { // handle height equal case
    if(vec1[1] > vec2[1]) return true;
    else if(vec1[1] == vec2[1]) { // handle depth equal case
      return vec1[0] > vec2[0]; // width is tie breaker
    } else return false;
  } else return false;
}

int stackOfBoxes(vector<vector<int>> boxes) {
  int maxHeight = 0;
  for(auto &box : boxes) sort(box.begin(), box.end());
  sort(boxes.begin(), boxes.end(), comp);
  vector<int> mem(boxes.size(), -1);
  for(int i=0; i<boxes.size(); i++) {
    maxHeight = max(stackOfBoxes(boxes, i, mem), maxHeight);
  }
  return maxHeight;
}

int main() {
  vector<vector<int>> iboxes {{2,51,2},{71,44,77},{42,26,29},{4,3,24},{47,47,81},{11,2,28},{64,72,72},{75,74,18},{10,67,13},{6,87,45},{93,22,50},{60,37,78},{48,9,51},{25,84,1},{7,75,94},{76,79,70},{14,55,5},{9,44,54},{49,66,62},{48,28,52},{37,11,7},{41,43,28},{72,54,94},{4,19,85},{81,46,72},{63,90,28},{41,47,4},{81,64,97},{1,48,78},{65,55,37},{43,74,99},{16,40,66},{90,15,83},{54,47,53},{98,63,50},{74,36,19},{10,2,10},{95,35,28},{76,87,75},{60,63,55},{75,87,2},{16,59,74},{67,19,27},{13,22,57},{13,16,37},{84,53,80},{70,13,1},{65,100,22},{70,78,8},{70,82,78},{58,29,23},{34,51,40}};

  cout << stackOfBoxes(iboxes) << endl;
}

// Tested on: https://leetcode.com/problems/maximum-height-by-stacking-cuboids/