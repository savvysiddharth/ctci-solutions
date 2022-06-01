#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
  public:
  stack<int> s1, s2;

  // Time: O(1)
  void add(int data) {
    s1.push(data);
  }

  // Time: O(N)
  int remove() {
    if(s2.empty()) {
      if(s1.empty()) return -1;
      while(!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
      }
    }
    int value = s2.top();
    s2.pop();
    return value;
  }
};

int main() {
  MyQueue queue;
  
  queue.add(1);
  queue.add(2);
  queue.add(3);
  queue.add(4);
  queue.add(5);

  for(int i=0; i<5; i++) {
    cout << queue.remove() << endl;
  }

}