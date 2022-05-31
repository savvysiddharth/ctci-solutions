#include <iostream>
#include <unordered_set>
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
// Space: O(N)
// Converting each list to an integer
LinkedList sumList_reverseOrder(LinkedList &l1, LinkedList &l2) { // first node is unit place
  Node *ptr = l1.head;
  int num1 = 0;
  int power = 0;
  while(ptr != NULL) {
    num1 += pow(10,power++) * ptr->data;
    ptr = ptr->next;
  }


  ptr = l2.head;
  int num2 = 0;
  power = 0;
  while(ptr != NULL) {
    num2 += pow(10,power++) * ptr->data;
    ptr = ptr->next;
  }
  int sum = num1 + num2;

  LinkedList result;
  int temp = sum;
  while(temp > 0) {
    int digit = temp%10;
    result.append(digit);
    temp /= 10;
  }

  return result;
}

// Time: O(N)
// Space: O(N)
// Without converting list to integer
LinkedList sumList_reverseOrder_wo_int(LinkedList &l1, LinkedList &l2) { // first node is unit place
  Node *ptr1 = l1.head;
  Node *ptr2 = l2.head;
  int carry = 0;
  LinkedList result;
  while(ptr1 != NULL || ptr2 != NULL) {
    int digit1 = 0, digit2 = 0;
    if(ptr1 != NULL) digit1 = ptr1->data;
    if(ptr2 != NULL) digit2 = ptr2->data;
    int sum = digit1 + digit2 + carry;
    int currSumDigit = sum;
    if(sum > 9) {
      currSumDigit = sum%10;
      carry = sum/10;
    } else carry = 0;
    result.append(currSumDigit);
    if(ptr1 != NULL) ptr1 = ptr1->next;
    if(ptr2 != NULL) ptr2 = ptr2->next;
  }
  if(carry) result.append(carry);
  return result;
}

// Time: O(N)
// Space: O(N)
// Recursive apporach, where number are stored in reverse order (ie: 617 is 7->1->6->)
Node* sum_rec_rev(Node *l1, Node *l2, int carry) {
  if(l1 == NULL && l2 == NULL) {
    if(carry) {
      Node* result = new Node(carry);
      return result;
    } else return NULL;
  }

  int l1val = 0, l2val = 0;
  if(l1 != NULL) l1val = l1->data;
  if(l2 != NULL) l2val = l2->data;
  int sum = l1val + l2val + carry;
  if(sum > 9) {
    carry = 1;
    sum = sum % 10;
  }
  Node *l1next = NULL, *l2next = NULL;
  if(l1 != NULL) l1next = l1->next;
  if(l2 != NULL) l2next = l2->next;
  Node* result = new Node(sum);
  result->next = sum_rec_rev(l1next, l2next, carry);
  return result;
}

// Time: O(N)
// Space: O(N)
// Recursive apporach, where number are stored in forward order (ie: 617 is 6->1->7->)
Node* sum_rec_fwd(Node *l1, Node *l2, Node *root) {
  cout << l1->data << " " << l2->data << endl;
  if(l1->next == NULL && l2->next == NULL) {  // we are at last node of each list, that means LSB of each number
    int sum = l1->data + l2->data;
    return new Node(sum);
  }
  Node *l1next = l1, *l2next = l2;
  if(l1->next != NULL) l1next = l1->next;
  if(l2->next != NULL) l2next = l2->next;
  Node *nextNode = sum_rec_fwd(l1next, l2next, root);
  int carry = 0;
  if(nextNode->data > 9) {
    nextNode->data = nextNode->data %10;
    carry = 1;
  }
  int sum = l1->data + l2->data + carry;
  Node* result = new Node(sum);
  result->next = nextNode;
  if(l1 == root && sum > 9) {
    result->data = sum%10;
    Node *carryHead = new Node(1);
    carryHead->next = result;
    return carryHead;
  }
  return result;
}

int main() {
  LinkedList list1;
  list1.append(9);
  list1.append(0);
  list1.append(0);
  list1.append(0);
  list1.print();

  LinkedList list2;
  list2.append(2);
  list2.append(0);
  list2.append(0);
  list2.append(0);
  list2.print();

  // Iterative simple converting to int method
  // LinkedList result = sumList_reverseOrder_wo_int(list1,list2);
  // cout << "result: ";
  // result.print();

  // Recursive, but reverse order input
  // LinkedList result;
  // result.head = sum_rec_rev(list1.head, list2.head, 0);
  // cout << "result: ";
  // result.print();

  // Recursive, forward order input
  LinkedList result;
  result.head = sum_rec_fwd(list1.head, list2.head, list1.head);
  cout << "result: ";
  result.print();
}