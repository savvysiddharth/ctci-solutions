#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

void printVector(vector<int> arr) {
  cout << "Data: [ ";
  for(int item : arr) {
    cout << item << " ";
  }
  cout << " ]" << endl;
}

class Graph {
  public:
  vector<vector<int>> adjList;

  void addNode() {
    adjList.push_back(vector<int>{});
  }

  void addEdge(int i, int j) {
    adjList[i].push_back(j);
    adjList[j].push_back(i);
  }

  void print() {
    for(int i=0; i<adjList.size(); i++) {
      cout << "node " << i << ": ";
      for(int j=0; j<adjList[i].size(); j++) {
        cout << adjList[i][j] << " ";
      }
      cout << endl;
    }
  }

  void printBFS() {
    vector<int> visited (adjList.size(), 0);
    queue<int> q;
    q.push(0); // starting with node 0
    visited[0] = 1;
    while(!q.empty()) {
      int curr = q.front();
      q.pop();
      cout << curr << " ";
      for(int child : adjList[curr]) {
        if(visited[child] == 0) {
          q.push(child);
          visited[child] = 1;
        }
      }
    }
    cout << endl;
  }

  void findPath(int start, int target) {
    vector<int> visited (adjList.size(), 0);
    vector<int> parent (adjList.size(), -1);
    queue<int> q;
    q.push(start); // starting with node 0
    visited[start] = 1;
    while(!q.empty()) {
      int curr = q.front();
      q.pop();
      // cout << curr << " ";
      for(int child : adjList[curr]) {
        if(visited[child] == 0) {
          if(parent[child] == -1) parent[child] = curr;
          q.push(child);
          visited[child] = 1;
        }
      }
    }
    printVector(parent);
    int curr = target;
    stack<int> path;
    while(curr != start && curr != -1) {
      path.push(curr);
      curr = parent[curr];
    }
    if(curr == start) path.push(start);
    else if(curr == -1) {
      cout << "no path found!" << endl;
      return;
    }
    while(!path.empty()) {
      cout << path.top();
      if(path.size() != 1) cout << " -> ";
      path.pop();
    }
    cout << endl;
  }

  void printDFS() {
    vector<int> visited (adjList.size(), 0);
    stack<int> stack;
    stack.push(0);
    visited[0] = 1;
    while(!stack.empty()) {
      int curr = stack.top();
      stack.pop();
      cout << curr << " ";
      for(int child : adjList[curr]) {
        if(visited[child] == 0) {
          stack.push(child);
          visited[child] = 1;
        }
      }
    }
    cout << endl;
  }
};

int main() {
  Graph graph;
  
  for(int i=0; i<6; i++) graph.addNode();

  //   0
  // /   \ 
  // 1   2
  // | \ |
  // 3---4
  // \   /
  //   5
  
  graph.addEdge(0,1);
  graph.addEdge(0,2);
  graph.addEdge(1,3);
  graph.addEdge(1,4);
  graph.addEdge(2,4);
  graph.addEdge(3,4);
  graph.addEdge(3,5);
  graph.addEdge(4,5);

  graph.findPath(0,5);
}