#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <climits>
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

  BinaryTree() {
    root = NULL;
  }

  // adds to first place possible
  Node *addNode(int data) {
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

  // Level order traversal - BFS
  void printBFS() {
    if(root == NULL) return;
    queue<Node*> myqueue;
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

  
  int successor(Node *curr) {
    if(curr->right != NULL) { // just look up leftmost element in right subtree
      curr = curr->right;
      while(curr->left != NULL) curr = curr->left;
      return curr->data;
    } else { // in this case, find applicable right subtree
      Node *prev;
      while(true) {
        prev = curr;
        curr = curr->parent;
        if(curr->right != prev && curr->right != NULL) break;
        if(curr->parent == NULL) return INT_MIN; // No Successor
      }
      return curr->data;
    }
  }
};

int main() {
  BinaryTree bt;
  
  bt.addNode(8);

  bt.addNode(4);
  bt.addNode(12);

  bt.addNode(2);
  bt.addNode(6);
  bt.addNode(10);
  bt.addNode(14);

  bt.addNode(1);
  bt.addNode(3);
  bt.addNode(5);
  Node *thisNode = bt.addNode(7);
  bt.addNode(9);
  bt.addNode(11);
  bt.addNode(13);
  bt.addNode(15);

  bt.printBFS();

  cout << "------------------------" << endl;

  cout << "Input: " << thisNode->data << endl;
  cout << "Successor: ";
  cout << bt.successor(thisNode) << endl;
}