#include <iostream>
#include <unordered_set>
#include <vector>
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
  // Space: O(N)
  // Iterative method
  bool isPalindrome() {
    Node *slowptr = this->head;
    Node *fastptr = this->head;
    bool oddCase = false;
    while(fastptr != NULL) { // to find the middle of linkedlist without knowing it's length
      // cout << "slow: " << slowptr->data << endl;
      // cout << "fast: " << fastptr->data << endl; 
      if(fastptr->next != NULL) fastptr = fastptr->next->next;
      else {
        fastptr = NULL;
        oddCase = true;
        break;
      }
      slowptr = slowptr->next;
    } // At this point, slow pointer is at middle of the linked list

    cout << "slowptr:" << slowptr->data << endl;
    if(oddCase) { // slowptr is at exactly the middle element
    } else { // slowptr is at last element of first half
      slowptr = slowptr; // to make the position equivalent (slowptr is immediately after first half) to oddcase
    }
    
    vector<int> stack;
    Node *ptr = this->head;
    while(ptr != slowptr) {
      stack.push_back(ptr->data);
      ptr = ptr->next;
    }

    cout << "stack content: ";
    for(auto item:stack) {
      cout << item << " ";
    } cout << endl;

    if(oddCase) ptr = slowptr->next;
    else ptr = slowptr;

    cout << "-----\n";
    while(ptr != NULL) {
      cout << ptr->data << endl;
      if(ptr->data == stack[stack.size()-1]) {
        stack.pop_back();
      } else {
        cout << "not palindrome!" << endl;
        return false;
      }
      ptr = ptr->next;
    }
    cout << "palindrome" << endl;
    return true;
  }
};

int main() {
  LinkedList mylist;
  mylist.append(1);
  mylist.append(2);
  mylist.append(3);
  mylist.append(3);
  mylist.append(2);
  mylist.append(1);
  // mylist.append(6);
  mylist.print();
  mylist.isPalindrome();
}