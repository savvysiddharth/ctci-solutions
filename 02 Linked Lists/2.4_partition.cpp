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

  int deleteAtFront() {
    if(this->head == NULL) return -1;
    int data = head->data;
    this->head = this->head->next;
    return data;
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

  // Time: O(N)
  // Space: O(1)
  // Iterate through the list, 
  // if element is less than key,
  // move it out and prepend it to the same list
  // (Elements order is not preserved)
  void partition(int key) {
    Node *prev = NULL;
    Node *ptr = this->head;
    while(ptr != NULL) {
      if(ptr->data < key && ptr != this->head) { // should move out from here and prepend it
        prev->next = ptr->next;
        ptr->next = this->head;
        this->head = ptr;
        ptr = prev->next; // moving ahead ptr pointer
      } else {
        prev = ptr;
        ptr = ptr->next;
      }
    }
  }

  // Time: O(N)
  // Space: O(1)
  // Elements order stays
  void partition_stable(int key) {
    // not implementing, because logic is simple..
    // make two empty likedlists.. (1) before (2) after
    // maintain head and tail of both lists
    // now iterate through given list
    // if value is lower than key, put it in before list
    // else put in after list
  }
};

int main() {
  LinkedList mylist;
  mylist.append(3);
  mylist.append(5);
  mylist.append(8);
  mylist.append(5);
  mylist.append(10);
  mylist.append(2);
  mylist.append(1);
  mylist.print();
  mylist.partition(5);
  mylist.print();

}