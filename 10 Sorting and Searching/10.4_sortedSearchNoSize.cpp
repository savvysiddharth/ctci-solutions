#include <iostream>
#include <vector>
#include<time.h>
using namespace std;

class Listy {
  private:
  int N = 100;
  vector<int> arr;

  public:
  Listy() { // generates a random sorted array of positive integers
    int k=rand()%4;
    for(int i=0; i<N; i++) {
      arr.push_back(k);
      int increment = rand()%5;
      k+=increment;
    }
    this->arr = arr;
  }

  void print() {
    cout << "Listy: [ ";
    for(auto item : arr) {
      cout << item << " ";
    }
    cout << "]" << endl;
  }

  int elementAt(int i) {
    if(i < N) return arr[i];
    else return -1;
  }
};

// Time: O(logN)
// Space: O(1)
int listySearch(Listy &listy, int target) {
  int j = 1; // curr
  int i = 0; // prev
  while(listy.elementAt(j) != -1) {
    i = j;
    j *= 2;
  }
  while(i <= j) {
    int mid = (i+j)/2;
    if(listy.elementAt(mid) == -1) j = mid-1;
    else i = mid+1;
  }
  int lastArrayIndex = j;
  i = 0;
  j = lastArrayIndex;
  while(i<=j) {
    int mid = (i+j)/2;
    if(listy.elementAt(mid) == target) return mid;
    if(target > listy.elementAt(mid)) i = mid+1;
    else j = mid-1;
  }
  return -1;
}

int main() {
  srand(time(0));
  Listy listy;
  listy.print();
  int target;
  cout << "\nEnter target: ";
  cin >> target;
  if(listySearch(listy, target) >= 0) cout << "found :)\n";
  else cout << "not found :(\n";
}