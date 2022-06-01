#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class setOfStacks {
  public:
  vector<stack<int>> stacks;
  int threshold = 3;

  setOfStacks() {
    stack<int> firstStack;
    stacks.push_back(firstStack);
  }

  void push(int data) {
    if(stacks[stacks.size()-1].size() == threshold) {
      stack<int> newStack;
      stacks.push_back(newStack);
    }
    stacks[stacks.size()-1].push(data);
  }

  int pop() {
    int value = stacks[stacks.size()-1].top();
    stacks[stacks.size()-1].pop();
    if(stacks[stacks.size()-1].size() == 0) stacks.pop_back();
    return value;
  }

  int popAt(int index) {
    int value = stacks[index].top();
    stacks[index].pop();
    return value;
  }
};

int main() {
  setOfStacks stacks;

  stacks.push(1);
  stacks.push(2);
  stacks.push(3);
  stacks.push(4);
  stacks.push(5);
  stacks.push(6);

  for(int i=0; i<6; i++) {
    cout << stacks.pop() << endl;
  }
}