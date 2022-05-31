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
};

// Time: O(N)
// Space: O(1)
// Go to end of both list to find if intersection exists
// if exists, find difference of length and act accordingly to find the intersecting node
Node* isIntersection(Node *l1, Node *l2) {
  Node *ptr1 = l1;
  Node *ptr2 = l2;

  int l1_length=1, l2_length=1;
  while(ptr1->next != NULL || ptr2->next != NULL) {
    if(ptr1->next != NULL) {
      ptr1 = ptr1->next;
      l1_length++;
    }
    if(ptr2->next != NULL) {
      ptr2 = ptr2->next;
      l2_length++;
    }
  }

  cout << ptr1 << " : " << ptr1->data << " len: " << l1_length << endl;
  cout << ptr2 << " : " << ptr2->data << " len: " << l2_length << endl;

  if(ptr1 == ptr2) { // intersection exists somewhere
    int diff = l1_length-l2_length;
    Node *longer = l2, *shorter = l1;
    if(diff > 0) { // l1 is bigger
      longer = l1;
      shorter = l2;
    }
    diff = abs(diff);
    while(diff--) {
      longer = longer->next;
    }

    while(longer != shorter) {
      longer = longer->next;
      shorter = shorter->next;
    }
    return longer; // or return shorter; (both are same at this point)
  } else return NULL;

  return NULL;
}

int main() {
  LinkedList l1,l2;
  l1.append(1);
  l1.append(2);
  l1.append(3);

  l2.append(4);
  l2.append(5);
  l2.append(6);
  l2.append(7);

  Node *l1end = l1.head;
  while(l1end->next != NULL) l1end = l1end->next;

  int intersectionPoint = 1; // must be less than length of l2
  Node *ptr = l2.head;
  while(intersectionPoint--) ptr = ptr->next;

  l1end->next = ptr; // connecting end of l1 to some node at l2 (hence achieving intersection)

  l1.print();
  l2.print();

  Node *intersectingNode = isIntersection(l1.head, l2.head);
  cout << "result: " << endl << intersectingNode << " = " << intersectingNode->data << endl; 

}