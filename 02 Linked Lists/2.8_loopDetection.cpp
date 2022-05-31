#include <iostream>
#include <unordered_set>
#include <vector>
#include <cmath>
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
  // Floyd Loop Detection Algorithm
  Node* detectLoop() {
    Node *turtoise = this->head, *hare = this->head;
    while(hare != NULL) {
      if(hare->next != NULL) hare = hare->next->next;
      else {
        hare = NULL;
        break;
      }
      turtoise = turtoise->next;
      if(hare == turtoise) break;
    }

    if(hare == turtoise) {
      Node *head = this->head;
      while(head != turtoise) {
        head = head->next;
        turtoise = turtoise->next;
      }
      return turtoise;
    } else return NULL;
  }
};

int main() {
  LinkedList l1;
  l1.append(1);
  l1.append(2);
  l1.append(3);
  l1.append(4);
  l1.append(5);
  l1.append(6);
  l1.append(7);

  Node *l1end = l1.head;
  while(l1end->next != NULL) l1end = l1end->next;

  int loopPoint = 5; // from the begining, must be less than length of the list
  Node *ptr = l1.head;
  while(loopPoint--) ptr = ptr->next;
  l1end->next = ptr; // connecting end of l1 to some node at l2 (hence achieving intersection)

  Node *loopStart = l1.detectLoop();
  if(loopStart != NULL) {
    cout << "loop starts: " << loopStart->data << endl;
  } else {
    cout << "no loop" << endl;
  }

}