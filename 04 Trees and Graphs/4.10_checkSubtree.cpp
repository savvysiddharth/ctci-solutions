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

  // Time: O(N^2)
  bool checkIfSubtree(Node *tree2) {
    int tree2top = tree2->data;
    queue<Node*> q;
    q = {};
    q.push(root);
    while(!q.empty()) {
      Node *curr = q.front();
      q.pop();
      if(curr->data == tree2top)
        if(compareTrees(curr, tree2)) return true;
      if(curr->left != NULL) q.push(curr->left);
      if(curr->right != NULL) q.push(curr->right);
    }
    return false;
  }

  // Time: O(NM)
  // N : Size of big tree
  // M : Size of small tree
  // Tighter Time: O(N + KM)
  // K : Occurrence of root of small tree in big tree
  // recursively traverse both trees in same way..
  // ..and return true if all nodes are exactly same
  // else false
  bool compareTrees(Node *tree1, Node *tree2) {
    if(tree1 == NULL || tree2 == NULL)
      if(tree1 == NULL && tree2 == NULL) return true;
      else return false;
    return tree1->data == tree2->data && compareTrees(tree1->left, tree2->left) && compareTrees(tree1->right, tree2->right);
  }

};

int main() {
  BinaryTree bt1;
  
  bt1.addNode(4);
  bt1.addNode(2);
  bt1.addNode(6);
  bt1.addNode(1);
  bt1.addNode(3);
  bt1.addNode(5);
  bt1.addNode(7);

  BinaryTree bt2;

  bt2.addNode(6);
  bt2.addNode(5);
  bt2.addNode(7);

  bt1.printBFS();
  cout << "-----------" << endl;

  bt2.printBFS();
  cout << "-----------" << endl;

  if(bt1.checkIfSubtree(bt2.root)) cout << "Yea, tree-2 is subtree of tree-1.." << endl; 
  else cout << "Nope, it ain't it..." << endl;
}