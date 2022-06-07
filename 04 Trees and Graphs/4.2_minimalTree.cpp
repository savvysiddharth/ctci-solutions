#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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

  void preorder_iterative() {
    stack<Node*> stack;
    if(root == NULL) return;
    stack.push(root);
    while(!stack.empty()) {
      Node *curr = stack.top();
      stack.pop();
      cout << curr->data << " ";
      if(curr->right != NULL) stack.push(curr->right);
      if(curr->left != NULL) stack.push(curr->left);
    }
    cout << endl;
  }

  void inorder_iterative() {
    stack<Node *> stack;
    Node *curr = root;
    while(!stack.empty()) {
      if(curr != NULL) {
        stack.push(curr);
        curr = curr->left;
      } else {
        if(stack.empty()) return;
        curr = stack.top();
        stack.pop();
        cout << curr->data << " ";
        curr = curr->right;
      }
    }
    cout << endl;
  }

  // Striver's solution
  void postorder_iterative() {
    stack<Node *> stack;
    Node *curr = root;
    while(!stack.empty() || curr != NULL) {
      if(curr != NULL) {
        stack.push(curr);
        curr = curr->left;
      } else {
        Node *temp = stack.top()->right;
        if(temp == NULL) {
          temp = stack.top(); 
          stack.pop();
          cout << temp->data << " ";
          while(!stack.empty() || temp == stack.top()->right) {
            temp = stack.top(); stack.pop();
            cout << temp->data << " ";
          }
        } else {
          curr = temp;
        }
      }
    }
  }

  // Maintaining a stack similar to how it would be recursive approach
  void my_postorder_iterative() {
    class Item {
      public:
      Node *node;
      int status;

      Item(Node *node, int status) {
        this->node = node;
        this->status = status;
      }
    };
    stack<Item> stack;
    Item first(root, 0);
    stack.push(first);
    while(!stack.empty()) {
      Item *item = &stack.top();
      if(item->node != NULL) {
        if(item->status == 0) { // go left
          item->status++;
          Item temp(item->node->left, 0);
          stack.push(temp);
        } else if(item->status == 1) { // go right
          item->status++;
          Item temp(item->node->right, 0);
          stack.push(temp);
        } else if(item->status == 2) { // do print
          cout << item->node->data << " ";
          stack.pop();
        }
      } else stack.pop();
    }
    cout << endl;
  }

  // Maintaining a stack similar to how it would be recursive approach
  void my_inorder_iterative() {
    class Item {
      public:
      Node *node;
      int status;

      Item(Node *node, int status) {
        this->node = node;
        this->status = status;
      }
    };
    stack<Item> stack;
    Item first(root, 0);
    stack.push(first);
    while(!stack.empty()) {
      Item *item = &stack.top();
      if(item->node != NULL) {
        if(item->status == 0) { // go left
          item->status++;
          Item temp(item->node->left, 0);
          stack.push(temp);
        } else if(item->status == 1) { // do print
          cout << item->node->data << " ";
          item->status++;
        } else if(item->status == 2) { // go right
          stack.pop();
          Item temp(item->node->right, 0);
          stack.push(temp);
        }
      } else stack.pop();
    }
    cout << endl;
  }

  // Maintaining a stack similar to how it would be recursive approach
  void my_preorder_iterative() {
    class Item {
      public:
      Node *node;
      int status;

      Item(Node *node, int status) {
        this->node = node;
        this->status = status;
      }
    };
    stack<Item> stack;
    Item first(root, 0);
    stack.push(first);
    while(!stack.empty()) {
      Item *item = &stack.top();
      if(item->node != NULL) {
        if(item->status == 0) { // do print
          cout << item->node->data << " ";
          item->status++;
        } else if(item->status == 1) { // go left
          item->status++;
          Item temp(item->node->left, 0);
          stack.push(temp);
        } else if(item->status == 2) { // go right
          stack.pop();
          Item temp(item->node->right, 0);
          stack.push(temp);
        }
      } else stack.pop();
    }
    cout << endl;
  }
};

Node *buildMinimalTree(vector<int> arr, int i, int j) {
  if(i>j) return NULL;
  if(i == j) return new Node(arr[i]);
  int mid = ceil((i+j)/2.0);
  Node *leftSubTree = buildMinimalTree(arr, i, mid-1);
  Node *root = new Node(arr[mid]);
  Node *rightSubTree = buildMinimalTree(arr, mid+1, j);
  root->left = leftSubTree;
  root->right = rightSubTree;
  return root;
}

BinaryTree buildMinimalTree(vector<int> arr) {
  if(arr.size() == 0) {
    BinaryTree bt;
    return bt; // return empty tree
  }
  Node *root = buildMinimalTree(arr, 0, arr.size()-1);
  BinaryTree newTree;
  newTree.root = root;
  return newTree;
}

int main() {
  vector<int> arr{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

  BinaryTree bt = buildMinimalTree(arr);
  bt.printBFS(); 
}