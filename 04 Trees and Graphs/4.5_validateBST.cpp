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
  void addNode(int data) {
    Node *newnode = new Node(data);
    if(root == NULL) {
      root = newnode;
      return;
    } else {
      queue<Node*> q;
      q.push(root);
      while(!q.empty()) {
        Node *curr = q.front();
        q.pop();
        if(curr->left == NULL) {
          newnode->parent = curr;
          curr->left = newnode;
          return;
        } else if(curr->right == NULL) {
          newnode->parent = curr;
          curr->right = newnode;
          return;
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
  }

  void addNode(int data, Node *parent) {
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

  bool isBST() {
    return isBST(root, INT_MIN, INT_MAX);
  }

  // Works in O(N) without any issues
  bool isBST(Node *curr, int min, int max) {
    if(curr == NULL) return true;
    bool statusRight = true, statusLeft = true;
    if(curr->left != NULL) statusLeft = curr->data >= curr->left->data;
    if(curr->right != NULL) statusRight = curr->data < curr->right->data;

    bool currentStatus = statusLeft  && statusRight && curr->data  > min && curr->data  < max;
    return currentStatus && isBST(curr->left, min, curr->data) && isBST(curr->right, curr->data, max);
  }

  // It works in O(N) time but FAILS in case where duplicates are present..
  // inorder can't distinguish between whether equal numbers were from left branch or right
  // while left is usually valid one and other is invalid BST
  bool isBST_inorder() {
    stack<Node *> stack;
    Node *curr = root;
    int prev;
    bool leftEndHit = false;
    while(true) {
      if(curr != NULL) {
        stack.push(curr);
        curr = curr->left;
      } else {
        if(stack.empty()) break;
        curr = stack.top();
        stack.pop();
        if(!leftEndHit) {
          leftEndHit = true;
          prev = curr->data;
        }
        if(curr->data < prev) return false; 
        prev = curr->data;
        curr = curr->right;
      }
    }
    return true;
  }
};

int main() {
  BinaryTree bt;
  
  bt.addNode(4);

  bt.addNode(2);
  bt.addNode(6);

  bt.addNode(1);
  bt.addNode(3);
  bt.addNode(5);
  bt.addNode(7);

  bt.printBFS();

  cout << "------------------------" << endl;
  
  if(bt.isBST_inorder()) cout << "is BST :)" << endl;
  else cout << "is NOT BST :(" << endl;

}