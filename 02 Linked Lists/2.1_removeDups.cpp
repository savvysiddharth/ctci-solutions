#include <iostream>
#include <unordered_set>
using namespace std;

class LinkedList {
  private:
  class Node {
    public:
    int data;
    Node *next;

    Node(int data) {
      this->data = data;
      this->next = NULL;
    }
  };

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

  // Time: O(N)
  // Space: O(N)
  void deleteDups() {
    unordered_set<int> myset; // should store map from node->data to its parent node

    Node *ptr = this->head;
    Node *prev = NULL;
    while(ptr != NULL) {
      if(myset.find(ptr->data) == myset.end()) myset.insert(ptr->data);
      else {
        prev->next = ptr->next;
      }
      prev = ptr;
      ptr = ptr->next;
    }
  }

  // Time: O(N^2)
  // Space: O(1)
  void deleteDups_lowMem() {
    Node *curr = this->head;
    while(curr != NULL) { // iterate through each node
      Node *prev = curr;
      Node *ptr = curr->next;
      while(ptr != NULL) {
        if(ptr->data == curr->data) {
          prev->next = ptr->next;
          ptr = ptr->next;
          continue;
        }
        prev = ptr;
        ptr = ptr->next;
      }
      curr = curr->next;
    }
  }
};

int main() {
  LinkedList mylist;
  mylist.append(4);
  mylist.append(2);
  mylist.append(3);
  mylist.append(4);
  mylist.append(1);
  mylist.append(2);
  mylist.append(2);
  mylist.print();
  mylist.deleteDups_lowMem();
  mylist.print();
}