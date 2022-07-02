#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

class Node {
  public:
  int data, leftCount, rightCount;
  Node *left;
  Node *right;
  Node *parent;

  Node(int data) {
    this->data = data;
    left = NULL;
    right = NULL;
    parent = NULL;
    leftCount = 0;
    rightCount = 0;
  }
};

class BinaryTree {
  public:
  Node *root;

  BinaryTree() {
    root = NULL;
  }

  // Caller function for recursive addBST() method
  Node *addBSTNode(int data) {
    if(root == NULL) {
      root = new Node(data);
      return root;
    }
    return addBST(root, data);
  }

  // Time: O(logN)
  Node *addBST(Node *curr , int data) {
    if(curr->data >= data) {
      if(curr->left == NULL) {
        curr->leftCount++;
        curr->left = new Node(data);
        curr->left->parent = curr;
        return curr->left;
      }
      else {
        curr->leftCount++;
        return addBST(curr->left, data);
      }
    } else {
      if(curr->right == NULL) {
        curr->right = new Node(data);
        curr->right->parent = curr;
        return curr->right;
      }
      else {
        return addBST(curr->right, data);
      }
    }
  }

  Node* findBSTNode(int target) {
    Node *curr = root;
    while(curr != NULL) {
      if(curr->data == target) return curr;
      else if(target > curr->data) curr = curr->right;
      else curr = curr->left;
    }
    return NULL;
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
      cout << curr->data << "," << curr->leftCount << " ";
      if(curr->left != NULL) myqueue.push(curr->left);
      if(curr->right != NULL) myqueue.push(curr->right);
    }
  }

  int getRank(int key) {
    Node *curr = findBSTNode(key);
    if(curr == NULL) return -1;
    int rank = curr->leftCount;
    Node *ptr = curr->parent;
    Node *prev = curr;
    while(ptr != NULL) {
      if(ptr->left != prev) rank += (ptr->leftCount + 1);
      prev = ptr;
      ptr = ptr->parent;
    }
    return rank;
  }
};

int main() {
  BinaryTree bt;

  vector<int> stream {5,1,4,4,5,9,7,13,3}; 

  for(auto &data : stream) bt.addBSTNode(data);

  vector<int> test{1,3,4,5,7,9,13};
  
  for(auto &x : test) cout << "rank of " << x << " : " << bt.getRank(x) << endl;

}