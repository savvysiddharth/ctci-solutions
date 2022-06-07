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
  Node *left;
  Node *right;
  Node *parent;

  Node(int data) {
    this->data = data;
    left = NULL;
    right = NULL;
    parent = NULL;
  }
};


class BinaryTree {
  public:
  Node *root;

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
  }

  void addNode(int data, Node *parent) {
    if(parent == NULL) root = new Node(data);
    else if(parent->left == NULL) parent->left = new Node(data);
    else if(parent->right == NULL) parent->right = new Node(data);
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

  int getHeight(Node *curr) {
    if(curr == NULL) return 0;
    return 1 + max(getHeight(curr->left), getHeight(curr->right));
  }

  bool checkBalanced() {
    if(root == NULL) return true;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    if(abs(leftHeight - rightHeight) <= 1) return true;
    else return false;
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
  
  if(bt.checkBalanced()) cout << "BALANCED :)" << endl;
  else cout << "NOT BALANCED :(" << endl;
}