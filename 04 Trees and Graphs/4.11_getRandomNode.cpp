#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <list>
#include <climits>
#include <unordered_map>
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

  // Time: O(N)
  // Space: O(1)
  Node* getRandomNode() {
    double randVal = rand()%size + 1;
    if(root == NULL) return NULL;
    queue<Node*> myqueue;
    myqueue = {};
    myqueue.push(root);
    while(!myqueue.empty()) {
      Node *curr = myqueue.front();
      myqueue.pop();
      if(!(--randVal)) return curr;
      if(curr->left != NULL) myqueue.push(curr->left);
      if(curr->right != NULL) myqueue.push(curr->right);
    }
    return NULL;
  }

  // Algorithm with O(logN) time, O(Depth) space is possible,
  // if each node maintains their subtree size
  // then for each node we can get 1/N probability

};

int main() {
  srand(time(0));
  BinaryTree bt;
  
  bt.addNode(43);
  bt.addNode(25);
  bt.addNode(66);
  bt.addNode(72);
  bt.addNode(89);
  bt.addNode(16);
  bt.addNode(98);
  bt.addNode(11);
  bt.addNode(12);
  bt.addNode(13);
  bt.addNode(14);
  // bt.addNode(31);
  // bt.addNode(32);
  // bt.addNode(33);
  // bt.addNode(34);

  bt.printBFS();

  cout << "-----------" << endl;
  
  cout << "Performing random selections..." << endl;

  unordered_map<int,int> counts;

  double iterations = 10000;

  for(int i=0; i<iterations; i++){
    int nodeData = bt.getRandomNode()->data;
    // cout << nodeData << " ";
    if(counts.find(nodeData) == counts.end()) counts.insert({nodeData, 1});
    else counts[nodeData]++;
  }
  // cout << endl;

  cout << "-----------" << endl;
  cout << "Occurrences: " << endl;
  cout << "-----------" << endl;
  for(auto pair : counts) {
    double percn = pair.second/iterations;
    cout << pair.first << " : " << (pair.second/iterations)*100 << "%" << endl;
  }

}