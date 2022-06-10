#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
using namespace std;

void printVector(vector<int> arr) {
  cout << "Data: [ ";
  for(int item : arr) {
    cout << item << " ";
  }
  cout << " ]" << endl;
}

void printStack(stack<int> istack) {
  stack<int> temp;
  while(!istack.empty()) { // pop and print it..
    int value = istack.top();
    istack.pop();
    cout << value << " ";
    temp.push(value);
  }
  cout << endl;
}

class Graph {
  public:
  vector<vector<int>> adjList;

  void addNode() {
    adjList.push_back(vector<int>{});
  }

  // adds directed edge
  void addEdge(int i, int j) {
    adjList[i].push_back(j);
  }

  void addUndirectedEdge(int i, int j) {
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

  // Building nodes with zero incoming edges, and then remove their outgoing edges...
  // recursively follow above logic...
  void buildOrder() {
    vector<int> buildOrder;
    unordered_map<int, unordered_set<int>> incomingEdges;

    for(int i=0; i < adjList.size(); i++) incomingEdges.insert({i, unordered_set<int> {}});

    for(int i=0; i < adjList.size(); i++) {
      for(int j=0; j < adjList[i].size(); j++) {
        int node = adjList[i][j];
        incomingEdges[node].insert(i);
      }
    }

    updateIncomingSet(incomingEdges, buildOrder);

    if(buildOrder.size() != 0) {
      cout << "Order: ";
      for(auto item : buildOrder) {
        cout << item << " ";
      } cout << endl;
    }
  }

  void updateIncomingSet(unordered_map<int, unordered_set<int>> &incomingEdges, vector<int> &buildOrder) {
    vector<int> toDelete;
    bool flag = true;
    for(auto item : incomingEdges) {
      if(item.second.size() == 0) {
        flag = false;
        toDelete.push_back(item.first);
      }
    }
    if(flag) {
      cout << "NO ORDER EXISTS!" << endl;
      buildOrder.clear();
      return;
    }

    for(auto itemToDelete : toDelete) { // deleting toDelete and pushing it in buildOrder
      buildOrder.push_back(itemToDelete);
      incomingEdges.erase(itemToDelete);
    }

    if(incomingEdges.size() == 0) return;

    for(auto &node : incomingEdges) { // deleting toDelete from each node's incomingSet if exists
      for(auto itemToDelete: toDelete) {
        node.second.erase(itemToDelete);
      }
    }

    updateIncomingSet(incomingEdges, buildOrder);
  }

  // Using DFS to do Topological Sort
  // When you reach at the end of path during DFS.. 
  // ...that node can be last in to topological order
  // use this intuition.. to build the order
  void buildOrder_v2() {
    vector<int> visited(adjList.size(), 0);
    stack<int> buildOrder;
    for(int i=0; i<adjList.size(); i++) {
      if(visited[i] == 0) {
        int ret = buildDFS(i, visited, buildOrder);
        if(ret == -1) return;
      }
    }
    printStack(buildOrder);
  }

  int buildDFS(int node, vector<int> &visited, stack<int> &buildOrder) {
    int ret;
    for(auto child : adjList[node]) {
      if(visited[child] == 2) return -1; // cycle exists
      if(visited[child] == 0) { // if unvisited
        visited[child] = 2; // visiting
        ret = buildDFS(child, visited, buildOrder);
        visited[child] = 1; // visited
        buildOrder.push(child);
      }
    }
    if(visited[node] == 0) {
      visited[node] = 1;
      buildOrder.push(node);
    }
    return ret;
  }
};

int main() {
  Graph graph;
  
  for(int i=0; i<6; i++) graph.addNode();
  
  // dependencies.. (a,b)... b depends on a
  graph.addEdge(0,3);
  graph.addEdge(3,2);
  graph.addEdge(1,3);
  graph.addEdge(5,1);
  graph.addEdge(5,0);
  // graph.addEdge(0,5);

  graph.buildOrder_v2();

}