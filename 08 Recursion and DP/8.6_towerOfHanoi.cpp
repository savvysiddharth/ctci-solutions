#include <iostream>
#include <vector>
#include <stack>
using namespace std;

stack<int> a{}, b{}, c{};

void printStack(stack<int> istack) {
  vector<int> vals;
  while(!istack.empty()) { // pop and print it..
    int value = istack.top();
    istack.pop();
    vals.push_back(value);
  }
  for(int i=vals.size()-1; i>=0; i--) cout << vals[i] << " ";
  cout << endl;
}

void printTowers(stack<int> &A, stack<int> &B, stack<int> &C) {
  cout << "A: "; printStack(A);
  cout << "B: "; printStack(B);
  cout << "C: "; printStack(C);
  cout << "-------------" << endl;
}

// Move top 'n' disks from A to C using B as a buffer
void hanoi(int n, stack<int> &A, stack<int> &C, stack<int> &B) {
  if(n > 1) hanoi(n-1, A, B, C);
  int A_top = A.top();
  A.pop();
  C.push(A_top);
  system("sleep 1");
  system("clear");
  printTowers(a,b,c);
  if(n > 1) hanoi(n-1, B, C, A);
}

int main() {
  system("clear");
  int n = 3;
  for(int i=n; i>=1; i--) a.push(i);
  
  printTowers(a,b,c);
  hanoi(n, a, c, b);
}