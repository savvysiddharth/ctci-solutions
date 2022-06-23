#include <iostream>
using namespace std;

// At every step, you make atmost two choices..
// Put '(' into the string.. or put ')' into the string..
// recurse this, and make choices based on availability
void parens(int open, int close, string str) {
  if(open == 0 && close == 0) cout << str << endl;
  if(open) parens(open-1, close+1, str + '(');
  if(close) parens(open, close-1, str + ')');
}

int main() {
  int n = 5;
  parens(n, 0, "");
}