#include <iostream>
using namespace std;

#define N 10

// Using given array[N] as linear memory, and implementing stack like linked list
class ThreeStack {
  public:
  int array[N]; // stores actual stack element
  int stackHead[3]; // Maintains head of 3 stacks
  int prev[N]; // Maintains previous element index of each element in stack
  int free = 0;

  ThreeStack() {
    for(int i=0; i<N; i++) {
      array[i] = 0; // unnecessary
      prev[i] = -2; // to indicate that relevant cell in array is empty
      if(i<3) stackHead[i] = -1; // simulataneously initializing stackHeads
    }
  }

  void updateFree() {
    int i = free;
    while(i<N) {
      if(prev[i] == -2) {
        free = i;
        return;
      }
      i++; 
    }
    free = -1; // no free space available
  }

  // returns 0 on success, -1 on stack overflow
  // This might get O(N) in worst case
  // can be improved to O(1) if we introduce an array of nextFree
  int push(int k, int stackIndex) {
    if(free == -1) return -1;
    array[free] = k;
    prev[free] = stackHead[stackIndex];
    stackHead[stackIndex] = free;
    if(prev[free+1] == -2) free++;
    else updateFree();
    return 0;
  }

  // Time: O(1)
  int pop(int stackIndex) {
    int value = array[stackHead[stackIndex]];
    if(free > stackHead[stackIndex]) free = stackHead[stackIndex];
    int prevIndex = prev[stackHead[stackIndex]];
    prev[stackHead[stackIndex]] = -2;
    stackHead[stackIndex] = prevIndex;
    return value;
  }

  void printStatus() {
    cout << "       ";
    for(int i=0; i<N; i++) {
      if(i <= 9 && i > -1) cout << "0";
      cout << i << " ";
    }
    cout << endl;

    cout << "       ";
    for(int i=0; i<N; i++) {
      cout << "---";
    }
    cout << endl;

    cout << "Array: ";
    for(int i=0; i<N; i++) {
      if(array[i] <= 9 && array[i] > -1) cout << "0";
      cout << array[i] << " ";
    }
    cout << endl;

    cout << " Prev: ";
    for(int i=0; i<N; i++) {
      if(prev[i] <= 9 && prev[i] > -1) cout << "0";
      cout << prev[i] << " ";
    }
    cout << endl;
  }
};

int main() {
  ThreeStack mystack;
  mystack.push(11,0);
  mystack.push(21,1);
  mystack.push(31,2);

  mystack.push(12,0);

  mystack.push(32,2);
  mystack.push(33,2);

  mystack.pop(0);

  mystack.push(34,2);
  mystack.printStatus();
}