#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <list>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include<time.h>
using namespace std;

void printVector(vector<int> arr) {
  cout << "Data: [ ";
  for(int item : arr) {
    cout << item << " ";
  }
  cout << " ]" << endl;
}

class Node {
  public:
  int data;
  int subtreeHeight;
  Node *left;
  Node *right;
  Node *parent;

  Node(int data) {
    this->data = data;
    left = NULL;
    right = NULL;
    parent = NULL;
    subtreeHeight = 1;
  }
};


class BinaryTree {
  public:
  Node *root;
  int deepestLevel = 0;
  int size = 0;

  BinaryTree() {
    root = NULL;
  }

  // adds to first place possible
  Node *addNode(int data) {
    size++;
    Node *newnode = new Node(data);
    if(root == NULL) {
      root = newnode;
      return newnode;
    } else {
      queue<Node*> q;
      q.push(root);
      while(!q.empty()) {
        Node *curr = q.front();
        q.pop();
        if(curr->left == NULL) {
          newnode->parent = curr;
          curr->left = newnode;
          return newnode;
        } else if(curr->right == NULL) {
          newnode->parent = curr;
          curr->right = newnode;
          return newnode;
        } else {
          q.push(curr->left);
          q.push(curr->right);
        }
      }
    }
    Node *curr = newnode->parent;
    int prevHeight = 1;
    while(curr != root && curr != NULL) {
      curr->subtreeHeight = ++prevHeight;
      curr = curr->parent;
    }
    if(curr != NULL) curr->subtreeHeight++;
    return newnode;
  }

  Node *addNode(int data, Node *parent) {
    size++;
    Node *newnode = new Node(data);
    if(parent == NULL) root = newnode;
    else if(parent->left == NULL) parent->left = newnode;
    else if(parent->right == NULL) parent->right = newnode;
    newnode->parent = parent;

    Node *curr = newnode->parent;
    int prevHeight = 1;
    while(curr != root && curr != NULL) {
      curr->subtreeHeight =  ++prevHeight;
      curr = curr->parent;
    }
    if(curr != NULL) curr->subtreeHeight++;
    return newnode;
  }

  // Caller function for recursive addBST() method
  Node *addBSTNode(int data) {
    size++;
    if(root == NULL) {
      root = new Node(data);
      return root;
    }
    return addBST(root, data);
  }

  // Time: O(logN)
  Node *addBST(Node *curr , int data) {
    size++;
    if(curr->data >= data) {
      if(curr->left == NULL) {
        curr->left = new Node(data);
        return curr->left;
      }
      else return addBST(curr->left, data);
    } else {
      if(curr->right == NULL) {
        curr->right = new Node(data);
        return curr->right;
      }
      else return addBST(curr->right, data);
    }
  }

  // Level order traversal - BFS
  void printBFS() {
    if(root == NULL) return;
    queue<Node*> myqueue;
    myqueue = {};
    myqueue.push(root);
    myqueue.push(NULL); // to add newline after second level
    while(!myqueue.empty()) {
      Node *curr = myqueue.front();
      myqueue.pop();
      if(curr == NULL) { // for newline after each level
        cout << endl;
        if(myqueue.front() != NULL) myqueue.push(NULL); // to ensure "NULL NULL" doesn't happen in queue
        continue;
      }
      cout << curr->data << " ";
      if(curr->left != NULL) myqueue.push(curr->left);
      if(curr->right != NULL) myqueue.push(curr->right);
    }
    // myqueue = {};
  }

  void printInorder() {
    printInorder(root);
    cout << endl;
  }

  void printInorder(Node *curr) { // DFS - Inorder
    if(curr != NULL) {
      printInorder(curr->left);
      cout << curr->data << " ";
      printInorder(curr->right);
    }
  }

  int getHeight() {
    return getHeight(root);
  }

  // Time : O(N)
  int getHeight(Node *curr) {
    if(curr == NULL) return 0;
    return 1 + max(getHeight(curr->left), getHeight(curr->right));
  }

  // Time: O(NlogN)
  // Space: O(logN)
  int pathsWithSum(int target) {
    int count = 0;
    do_with_inorder(root, target, count);
    cout << "count: " << count << endl;
    return count;
  }

  // Does DFS calls the recursive pathsWithSum() function for each node
  void do_with_inorder(Node *curr, int &target, int &count) {
    if(curr == NULL) return;
    do_with_inorder(curr->left, target, count);
    pathsWithSum(curr, 0, target, count);
    do_with_inorder(curr->right, target, count);
  }

  // Time: O(N)
  void pathsWithSum(Node *curr, int currSum, int &target, int &count) {
    if(curr == NULL) return;
    currSum += curr->data;
    if(currSum == target) {
      count++;
      cout << "incremented at " << curr->data << endl;
    }
    pathsWithSum(curr->left, currSum, target, count);
    pathsWithSum(curr->right, currSum, target, count);
    return;
  }

  // Time: O(N)
  // Space: O(logN)
  int pathsWithSum_Fast(int target) {
    int count = 0;
    unordered_map<int,int> map;
    do_with_inorder(root, target, count, 0, map);
    cout << "count: " << count << endl;
    return count;
  }

  void do_with_inorder(Node *curr, int &target, int &count, int currSum, unordered_map<int,int> &map) {
    if(curr == NULL) return;
    currSum += curr->data;
    if(currSum == target) count++;
    if(map.find(currSum-target) != map.end()) count+= map[currSum-target];
    if(map.find(currSum) == map.end()) map.insert({currSum,1});
    else map[currSum]++;
    do_with_inorder(curr->left, target, count, currSum, map);
    do_with_inorder(curr->right, target, count, currSum, map);
    map.erase(currSum);
  }

};

void buildExampleTree(BinaryTree &bt) {
  bt.addNode(1, NULL);
  
  bt.addNode(2, bt.root);
  bt.addNode(3, bt.root);
  
  bt.addNode(1, bt.root->left);
  bt.addNode(3, bt.root->left);

  bt.addNode(3, bt.root->left->left);

  bt.addNode(-1, bt.root->left->right);

  bt.addNode(1, bt.root->left->right->left);

  bt.addNode(3, bt.root->right);
  bt.addNode(1, bt.root->right);
}

int main() {
  srand(time(0));
  BinaryTree bt;
  
  buildExampleTree(bt);

  bt.printBFS();

  cout << "-----------" << endl;

  bt.pathsWithSum_Fast(6);

}