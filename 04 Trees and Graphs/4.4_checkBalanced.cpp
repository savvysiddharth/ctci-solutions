#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
using namespace std;

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

  // Time: O(NlogN) (Checks height of each subtree for each node)
  bool checkBalanced(Node *curr) {
    if(curr == NULL) return true;
    int leftHeight = getHeight(curr->left);
    int rightHeight = getHeight(curr->right);
    if(abs(leftHeight - rightHeight) > 1) return false;
    else return checkBalanced(curr->left) && checkBalanced(curr->right);
  }


  // Time: O(N)
  // Actual implementation is in addNode() function
  // Height of subtree is updated during insertion
  // This adds extra overhead of O(logN) in insertion
  bool checkBalancedFaster(Node *curr) {
    if(curr == NULL) return true;
    int leftTreeHeight = curr->left == NULL ? 0 : curr->left->subtreeHeight;
    int rightTreeHeight = curr->right == NULL ? 0 : curr->right->subtreeHeight;
    if(abs(leftTreeHeight - rightTreeHeight) > 1) return false;
    else return checkBalancedFaster(curr->left) && checkBalancedFaster(curr->right);
  }

  int checkHeight(Node *curr) {
    if(curr == NULL) return 0;
    int leftHeight = checkHeight(curr->left);
    int rightHeight = checkHeight(curr->right);
    if(leftHeight == -1 || rightHeight == -1) return -1;
    if(abs(leftHeight - rightHeight) > 1) return -1;
    else return 1 + max(leftHeight, rightHeight);
  }

  // Time: O(N)
  // No need for any overhead on insertion
  // checkHeight() function checks for subtree height difference while calculating height
  bool checkBalancedBetter() {
    if(checkHeight(root) == -1) return false;
    else return true;
  }
};

void buildExampleTree(BinaryTree &bt) {
  bt.addNode(1, NULL);
  
  bt.addNode(2, bt.root);
  bt.addNode(3, bt.root);
  
  bt.addNode(4, bt.root->left);
  bt.addNode(5, bt.root->left);
  bt.addNode(6, bt.root->right);
  bt.addNode(7, bt.root->right);
  
  bt.addNode(8, bt.root->left->left);
  bt.addNode(9, bt.root->left->left);
  bt.addNode(10, bt.root->left->right);
  bt.addNode(11, bt.root->left->right);

  // bt.addNode(12, bt.root->right->left);
  // bt.addNode(13, bt.root->right->left);
  // bt.addNode(14, bt.root->right->right);
  // bt.addNode(15, bt.root->right->right);
}

int main() {
  BinaryTree bt;
  
  buildExampleTree(bt);

  bt.printBFS();

  cout << "------------------------" << endl;
  
  if(bt.checkBalanced(bt.root)) cout << "BALANCED :) (took O(NlogN) time)" << endl;
  else cout << "NOT BALANCED :( (took O(NlogN) time)" << endl;
  
  cout << "------------------------" << endl;

  if(bt.checkBalancedFaster(bt.root)) cout << "BALANCED :) (said it faster than above subroutine)" << endl;
  else cout << "NOT BALANCED :( (said it faster than above subroutine)" << endl;

  cout << "------------------------" << endl;

  if(bt.checkBalancedBetter()) cout << "BALANCED :) (said it without being burden on anyone else)" << endl;
  else cout << "NOT BALANCED :( (said it without being burden on anyone else)" << endl;

}