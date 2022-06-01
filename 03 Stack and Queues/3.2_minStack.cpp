#include <iostream>
#include <stack>
using namespace std;

class minStack {
  public:
  stack<int> mainStack; // actual stack
  stack<int> min_stack; // stores minimum in form of stack

  void push(int data) {
    if(min_stack.empty()) min_stack.push(data);
    else if(data <= min_stack.top()) min_stack.push(data);
    mainStack.push(data);
  }

  int pop() {
    int value = mainStack.top();
    if(value == min_stack.top()) min_stack.pop();
    mainStack.pop();
    return value;
  }

  int getMin() {
    return min_stack.top();
  }
};

int main() {
  minStack mystack;

  mystack.push(5);
  mystack.push(6);
  mystack.push(3);
  mystack.push(7);

  cout << mystack.getMin() << endl;
  
  mystack.pop();
  cout << mystack.getMin() << endl;

  mystack.pop();
  cout << mystack.getMin() << endl;
}