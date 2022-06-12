#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <list>
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

  void bstSeq() {
    list<Node*> startingList, emptyList;
    startingList.push_back(root);
    bstSeq(startingList, emptyList);
  }
  
  // Reference: https://gist.github.com/kean/40a1e592a608154b117a0dac48baf25f#file-ctci-6h-problem-4-9-markdown
  // Time: O(N) 
  // Space: O(NlogN)
  void bstSeq(list<Node *> currChoices, list<Node *> output) {
    if(currChoices.size() == 0) {
      for(auto node : output) {
        cout << node->data << " ";
      }
      cout << endl;
    } else {
      for(auto node : currChoices) {
        list<Node*> temp1 = currChoices;
        list<Node*> temp2 = output;
        temp1.remove(node);
        if(node->left != NULL) temp1.push_back(node->left);
        if(node->right != NULL) temp1.push_back(node->right);
        temp2.push_back(node);
        bstSeq(temp1, temp2);
      }
    }
  }

};

int main() {
  BinaryTree bt;
  
  bt.addBSTNode(4);
  bt.addBSTNode(2);
  bt.addBSTNode(6);
  bt.addBSTNode(1);
  bt.addBSTNode(3);
  bt.addBSTNode(5);
  bt.addBSTNode(7);

  bt.printBFS();
  cout << "-----------" << endl;

  bt.bstSeq();
}