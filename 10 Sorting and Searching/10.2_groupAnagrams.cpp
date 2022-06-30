#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

void printVector(vector<string> &arr) {
  cout << "[ ";
  for(auto &item : arr) {
    cout << item << " ";
  }
  cout << "]" << endl;
}

void printVecOfVec(vector<vector<string>> ivec) {
  for(auto &item : ivec) {
    printVector(item);
  }
}


vector<vector<string>> groupAnagrams(vector<string> words) {
  vector<vector<string>> result;
  vector<string> wordsCopy = words;
  for(auto &word : wordsCopy) sort(word.begin(), word.end());
  unordered_map<string, vector<int>> map;
  for(int i=0; i<wordsCopy.size(); i++) map[wordsCopy[i]].push_back(i);
  for(auto &item: map) {
    vector<string> tempRes {};
    for(auto &index: map[item.first]) {
      tempRes.push_back(words[index]);
    }
    result.push_back(tempRes);
  }
  return result;
}


int main() {
  vector<string> iwords {"eat","tea","tan","ate","nat","bat"};

  vector<vector<string>> answer = groupAnagrams(iwords);

  printVecOfVec(answer);
}


// Tested on: https://leetcode.com/problems/group-anagrams/