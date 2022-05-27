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
  // Space: O(1)
  // Trivial: Two pass approach
  int kthLast(int k) {
    Node *ptr = this->head;
    int size = 0;
    while(ptr != NULL) {
      size++;
      ptr = ptr->next;
    }
    int target = size - k + 1; // target position w.r.t. head
    ptr = this->head;
    int current = 0;
    while(ptr != NULL) {
      if(++current == target) return ptr->data;
      ptr = ptr->next;
    }
    return -1;
  }

  // Time: O(N)
  // Space: O(N)
  // Recursive Approach
  int kthLast(Node *curr, int k) {
    if(curr == NULL) return 0;
    int currIndex = kthLast(curr->next, k) + 1;
    if(currIndex == k) {
      cout << k << "-th last: " << curr->data << endl;
    }
    return currIndex;
  }

  // Time: O(N)
  // Space: O(1)
  // Two pointer approach : Almost single pass approach... (k + N)
  void kthLast_Itr(int k) {
    Node *first = this->head;
    Node *second = this->head;
    int count = 0;
    while(count != k) {
      second = second->next;
      count++;
    } // now first and second are 'k' apart

    while(second != NULL) {
      second = second->next;
      first = first->next;
    } // second has hit NULL, so first is 'kth' last

    cout << k << "-th pos: " << first->data << endl;
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
  int k = 1;
  // cout << k << "-th pos: " << mylist.kthLast(k) << endl;
  // mylist.kthLast(mylist.head, k);
  mylist.kthLast_Itr(k);
}