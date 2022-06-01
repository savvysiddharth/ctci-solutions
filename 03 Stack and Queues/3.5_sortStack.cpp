#include <iostream>
#include <stack>
using namespace std;

void sortStack(stack<int> &istack) {
  stack<int> tempStack;

  while(!istack.empty()) {
    tempStack.push(istack.top());
    istack.pop();
  }
  
  while(!tempStack.empty()) {
    int curr = tempStack.top();
    tempStack.pop();
    if(istack.empty()) {
      istack.push(curr);
      continue;
    }
    int count = 0;
    while(!istack.empty() && curr > istack.top()) {
      int temp = istack.top();
      istack.pop();
      tempStack.push(temp);
      count++;
    }
    istack.push(curr);
    while(count--) {
      int temp = tempStack.top();
      tempStack.pop();
      istack.push(temp);
    }
  }
}

void printStack(stack<int> &istack) {
  stack<int> temp;
  while(!istack.empty()) { // pop and print it..
    int value = istack.top();
    istack.pop();
    cout << value << " ";
    temp.push(value);
  }
  cout << endl;

  while(!temp.empty()) { // push
    istack.push(temp.top());
    temp.pop();
  }
}

int main() {
  stack<int> mystack;
  
  mystack.push(1);
  mystack.push(4);
  mystack.push(5);
  mystack.push(2);
  mystack.push(3);

  printStack(mystack);

  sortStack(mystack);

  printStack(mystack);
}