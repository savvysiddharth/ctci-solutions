#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

#define N 10 // N-ary tree

class TreeNode {
  public:
  int data;
  int childCount;
  TreeNode *children[N]; // N-ary tree

  TreeNode(int data) {
    this->data = data;
    childCount = 0;
  }
};

class Tree {
  public:
  TreeNode *root;

  Tree() {
    root = NULL;
  }

  void addNode(int data, TreeNode *parent) {
    if(parent->childCount < N)
      parent->children[parent->childCount] = new TreeNode(data);
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

// Inefficient implementation of by using Binary Tree
class Heap_Lite {
  public:
  // vector<int> heap;
  BinaryTree heap;
  int size;
  Node *lastNode;

  Heap_Lite() {
    size = 0;
    lastNode = NULL;
  }

  // Time: O(N)
  void add(int data) {
    size++;
    Node *newnode = new Node(data);
    lastNode = newnode;
    if(heap.root == NULL) {
      heap.root = newnode;
      return;
    } else {
      queue<Node*> q;
      q.push(heap.root);
      while(!q.empty()) {
        Node *curr = q.front();
        q.pop();
        if(curr->left == NULL) {
          newnode->parent = curr;
          curr->left = newnode;
          heapifyUp(newnode);
          return;
        } else if(curr->right == NULL) {
          newnode->parent = curr;
          curr->right = newnode;
          heapifyUp(newnode);
          return;
        } else {
          q.push(curr->left);
          q.push(curr->right);
        }
      }
    }
  }


  // Time: O(logN)
  int extractMin() {
    if(heap.root == NULL) return -1;
    else {
      size--;
      int MIN = heap.root->data;
      heap.root->data = lastNode->data;
      if(lastNode->parent->right != NULL) lastNode->parent->right = NULL;
      else lastNode->parent->left = NULL;
      heapifyDown(heap.root);
      return MIN;
    }
  }

  void print() {
    heap.printBFS();
  }

  private:
  // Time: O(logN)
  // Bottom to Up
  void heapifyUp(Node *curr) {
    if(curr == heap.root) return;
    if(curr->data < curr->parent->data) {
      int temp =curr->data; 
      curr->data = curr->parent->data;
      curr->parent->data = temp;
      heapifyUp(curr->parent);
    } else return;
  }

  // Time: O(logN)
  // Top to Down
  void heapifyDown(Node *curr) {
    if(curr->left == NULL && curr->right == NULL) return; // Reached at the bottom
    Node *left = curr->left, *right=curr->right;
    if(right == NULL) {
      if(curr->data > left->data) {
        int temp = curr->data;
        curr->data = left->data;
        left->data = temp;
        return;
      }
    } else {
      if(curr->data <= left->data && curr->data <= right->data) return;
      Node *minChild;
      if(curr->left->data < curr->right->data) minChild = curr->left;
      else minChild = curr->right;
      int temp = curr->data;
      curr->data = minChild->data;
      minChild->data = temp;
      heapifyDown(minChild);
    }
  }
};

// This implements Binary Heap using contagious array
// this is optimal implementation
class MinHeap {
  public:
  vector<int> heap;
  int size;

  MinHeap() {
    size = 0;
  }

  // Time: O(logN)
  void add(int data) {
    size++;
    heap.push_back(data);
    heapifyUp(size-1);
  }

  // Time: O(1)
  int getMin() {
    if(size == 0) return -1;
    return heap[0];
  }

  // Time: O(logN)
  int extractMin() {
    if(size == 0) return -1;
    int MIN = heap[0];
    heap[0] = heap[size-1];
    size--;
    heapifyDown(0);
    return MIN;
  }

  // Prints heap array in Level order form
  void print() {
    int count = 1;
    int currentCount = 0;
    for(int i=0; i<size; i++) {
      cout << heap[i] << " ";
      if(++currentCount == count) {
        if(i != size-1) cout << endl;
        count *= 2;
        currentCount = 0;
      }
    }
    cout << endl; 
  }

  private:
  int left(int i) {
    return 2*i + 1;
  }

  int right(int i) {
    return 2*i + 2;
  }

  int parent(int i) {
    return ceil((i+1)/2.0) - 1; 
  }

  // Time: O(logN)
  void heapifyUp(int i) {
    if(i == 0) return;
    if(heap[i] < heap[parent(i)]) {
      int temp = heap[i];
      heap[i] = heap[parent(i)];
      heap[parent(i)] = temp;
      heapifyUp(parent(i));
    } else return;
  }

  // Time: O(logN)
  void heapifyDown(int i) {
    if(i >= size) return;
    if(left(i) >= size && right(i) >= size) return;
    if(right(i) >= size) { // only left child exists
      if(heap[i] > heap[left(i)]) {
        int temp = heap[i];
        heap[i] = heap[left(i)];
        heap[left(i)] = temp;
        heapifyDown(left(i));
      }
    } else { // both child exists
      int minIndex;
      if(heap[left(i)] < heap[right(i)]) minIndex = left(i);
      else minIndex = right(i);
      int temp = heap[i];
      heap[i] = heap[minIndex];
      heap[minIndex] = temp;
      heapifyDown(left(i));
    }
  }
};

void printVector(vector<int> arr) {
  cout << "Data: [ ";
  for(int item : arr) {
    cout << item << " ";
  }
  cout << " ]" << endl;
}

class Graph {
  public:
  vector<vector<int>> adjList;

  void addNode() {
    adjList.push_back(vector<int>{});
  }

  void addEdge(int i, int j) {
    adjList[i].push_back(j);
    adjList[j].push_back(i);
  }

  void print() {
    for(int i=0; i<adjList.size(); i++) {
      cout << "node " << i << ": ";
      for(int j=0; j<adjList[i].size(); j++) {
        cout << adjList[i][j] << " ";
      }
      cout << endl;
    }
  }

  void printBFS() {
    vector<int> visited (adjList.size(), 0);
    queue<int> q;
    q.push(0); // starting with node 0
    visited[0] = 1;
    while(!q.empty()) {
      int curr = q.front();
      q.pop();
      cout << curr << " ";
      for(int child : adjList[curr]) {
        if(visited[child] == 0) {
          q.push(child);
          visited[child] = 1;
        }
      }
    }
    cout << endl;
  }

  void printDFS() {
    vector<int> visited (adjList.size(), 0);
    stack<int> stack;
    stack.push(0);
    visited[0] = 1;
    while(!stack.empty()) {
      int curr = stack.top();
      stack.pop();
      cout << curr << " ";
      for(int child : adjList[curr]) {
        if(visited[child] == 0) {
          stack.push(child);
          visited[child] = 1;
        }
      }
    }
    cout << endl;
  }
};

void buildExampleTree(BinaryTree bt) {
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

  bt.addNode(12, bt.root->right->left);
  bt.addNode(13, bt.root->right->left);
  bt.addNode(14, bt.root->right->right);
  bt.addNode(15, bt.root->right->right);
}

int main() {

  cout << "\n--------------BINARY TREE------------\n\n";

  BinaryTree bt;
  
  for(int i=1; i<=15; i++) bt.addNode(i);

  cout << "Level Order Traversal: " << endl;
  bt.printBFS();
  cout << "-----------------\n";
  
  cout << "postorder: "; bt.my_postorder_iterative();
  cout << "inorder: "; bt.my_inorder_iterative();
  cout << "preorder: "; bt.my_preorder_iterative();

  cout << "\n--------------HEAP------------\n\n";

  MinHeap myheap;

  for(int i=15; i>=1; i--) myheap.add(i);

  myheap.print();
  cout << "--" << endl;

  for(int i=0; i<3; i++) {
    myheap.extractMin();
    myheap.print();
    cout << "--" << endl;
  }

  cout << "\n--------------GRAPH------------\n\n";

  Graph graph;
  
  for(int i=0; i<6; i++) graph.addNode();
  
  graph.addEdge(0,1);
  graph.addEdge(0,2);
  graph.addEdge(1,3);
  graph.addEdge(1,4);
  graph.addEdge(2,4);
  graph.addEdge(3,4);
  graph.addEdge(3,5);
  graph.addEdge(4,5);

  graph.print();
  cout << "---------------\n";
  cout << "bfs: "; graph.printBFS();
  cout << "dfs: "; graph.printDFS();
}