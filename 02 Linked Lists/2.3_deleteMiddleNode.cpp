#include <iostream>
#include <unordered_set>
using namespace std;

class Node {
  public:
  int data;
  Node *next;

  Node(int data) {
    this->data = data;
    this->next = NULL;
  }
};

class LinkedList {
  public:
  Node *head;

  LinkedList() {
    this->head = NULL;
  }

  void append(int data) {
    Node *newnode = new Node(data);
    if(this->head == NULL) {
      this->head = newnode;
      return;
    }
    Node *ptr = head;
    while(ptr->next != NULL) ptr = ptr->next;
    ptr->next = newnode;
  }

  void prepend(int data) {
    Node *newnode = new Node(data);
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
    Node *ptr = this->head;
    while(ptr != NULL) {
      cout << ptr->data << " -> ";
      ptr = ptr->next;
    }
    cout << endl;
  }

  // Time: O(1)
  // Space: O(1)
  // middleNode can be anything but last and first
  void deleteMiddle(Node *middleNode) {
    if(middleNode == NULL || middleNode->next == NULL) return;
    int nextNodeData = middleNode->next->data;
    middleNode->data = nextNodeData;
    middleNode->next = middleNode->next->next;
  }

};

int main() {
  LinkedList mylist;
  mylist.append(1);
  mylist.append(2);
  mylist.append(3);
  mylist.append(4);
  mylist.append(5);
  mylist.append(6);
  mylist.print();
  Node* someMiddleNode = mylist.head->next->next;
  mylist.deleteMiddle(someMiddleNode);
  mylist.print();

}