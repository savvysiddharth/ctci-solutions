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

  // Time: O(N) (where N is total number of nodes in the tree)
  // idea is to do DFS and be alert when you find first occurrence
  // Issue with this approach: rechecks same subtree again and again..
  void firstCommonAncestor(Node *itemOne, Node *itemTwo) {
    if(root == itemOne) {
      cout << "no common ancestor" << endl;
      return; 
    }
    Node *curr = root;
    while(true) {
      if(findBelow(curr->left, itemOne) && findBelow(curr->right, itemTwo)) {
        cout << curr->data << " is common ancestor!" << endl;
        return;
      } else if(findBelow(curr->left, itemOne) && findBelow(curr->left, itemTwo)) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
  }

  bool findBelow(Node *curr, Node *key) {
    if(curr == NULL) return false;
    bool statusLeft = false, statusRight = false;
    statusLeft = findBelow(curr->left, key);
    statusRight = findBelow(curr->right, key);
    if(curr == key) return true;
    return statusLeft || statusRight;
  }

  // Time: O(N)
  // Does it optimially, without any unnecessary duplicate computations
  Node *deepestCommonAncestor(Node *curr, Node *itemOne, Node *itemTwo) {
    if(curr == NULL || curr == itemOne || curr == itemTwo) return curr;
    Node *dcaLeft = deepestCommonAncestor(curr->left, itemOne, itemTwo);
    Node *dcaRight = deepestCommonAncestor(curr->right, itemOne, itemTwo);
    if(dcaLeft == itemOne && dcaRight == itemTwo || dcaLeft == itemTwo && dcaRight == itemOne) return curr;
    else return dcaLeft != NULL ? dcaLeft : dcaRight;
  }

};

int main() {
  BinaryTree bt;
  
  bt.addNode(8, NULL);
  
  bt.addNode(4, bt.root);
  bt.addNode(12, bt.root);
  
  bt.addNode(2, bt.root->left);
  bt.addNode(6, bt.root->left);
  bt.addNode(10, bt.root->right);
  bt.addNode(14, bt.root->right);
  
  bt.addNode(1, bt.root->left->left);
  Node *t2 = bt.addNode(3, bt.root->left->left);
  Node *t1 = bt.addNode(5, bt.root->left->right);
  bt.addNode(7, bt.root->left->right);

  bt.addNode(9, bt.root->right->left);
  bt.addNode(11, bt.root->right->left);
  bt.addNode(13, bt.root->right->right);
  bt.addNode(15, bt.root->right->right);

  bt.printBFS();
  cout << "-----------" << endl;

  Node *result = bt.deepestCommonAncestor(bt.root, t1, t2);

  cout << result->data << " is first common ancestor of " << t1->data << " and " << t2->data << "." << endl;
}