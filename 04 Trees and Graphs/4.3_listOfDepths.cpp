#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

class ListNode {
  public:
  int data;
  ListNode *next;

  ListNode(int data) {
    this->data = data;
    this->next = NULL;
  }
};

class LinkedList {
  public:
  ListNode *head;

  LinkedList() {
    this->head = NULL;
  }

  void append(int data) {
    ListNode *newnode = new ListNode(data);
    if(this->head == NULL) {
      this->head = newnode;
      return;
    }
    ListNode *ptr = head;
    while(ptr->next != NULL) ptr = ptr->next;
    ptr->next = newnode;
  }

  void prepend(int data) {
    ListNode *newnode = new ListNode(data);
    if(this->head == NULL) {
      this->head = newnode;
      return;
    }
    newnode->next = this->head;
    this->head = newnode;
  }

  void deleteAtFront() {
    if(this->head == NULL) return;
    this->head = this->head->next;
  }

  void print() {
    if(this->head == NULL) return;
    ListNode *ptr = this->head;
    while(ptr != NULL) {
      cout << ptr->data << " -> ";
      ptr = ptr->next;
    }
    cout << endl;
  }
};

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

  vector<LinkedList*> listOfDepths() {
    queue<Node*> q;
    q.push(root);
    q.push(NULL); // to differentiate between levels
    vector<LinkedList*> lists;
    LinkedList *currList = new LinkedList();
    while(!q.empty()) {
      Node *curr = q.front();
      q.pop();
      if(curr != NULL) {
        currList->append(curr->data);
        if(curr->left != NULL) q.push(curr->left);
        if(curr->right != NULL) q.push(curr->right);
      } else {
        lists.push_back(currList);
        currList = new LinkedList();
        if(!q.empty()) q.push(NULL);
      }
    }
    return lists;
  }
};

int main() {
  BinaryTree bt;
  
  for(int i=1; i<=15; i++) bt.addNode(i);

  bt.printBFS();

  cout << "--------------------------\n";

  vector<LinkedList*> lists = bt.listOfDepths();
  for(auto list : lists) {
    list->print();
  }
}