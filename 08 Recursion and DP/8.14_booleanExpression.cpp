#include <iostream>
#include <vector>
using namespace std;

// supports only 2 operands at max
int evalExp(string exp) {
  if(exp.size() > 3) return -1;
  if(exp.size() == 1) {
    if(exp == "1") return 1;
    else return 0;
  }
  int a = exp[0] == '1' ? 1 : 0;
  int b = exp[2] == '1' ? 1 : 0;
  switch(exp[1]) {
    case '&':
    return a & b;
    case '|':
    return a | b;
    case '^':
    return a ^ b;
  }
  return -1;
}

int calcEval(int i, int j, string &exp, int target, vector<vector<vector<int>>> mem) {
  if(j-i+1 <= 3) {
    if(evalExp(exp.substr(i, j-i+1)) == target) return 1;
    else return 0;
  }
  if(mem[i][j][target] != -1) return mem[i][j][target];
  int count = 0;
  for(int k=i+1; k<j; k+=2) {
    char opr = exp[k];
    int leftCount, rightCount;
    if(opr == '&') {
      if(target == 1) {
        leftCount = calcEval(i, k-1, exp, 1, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 1, mem);
        count += leftCount*rightCount;
      } else if(target == 0) {
        leftCount = calcEval(i, k-1, exp, 0, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 1, mem);
        count += leftCount*rightCount;
        leftCount = calcEval(i, k-1, exp, 1, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 0, mem);
        count += leftCount*rightCount;
        leftCount = calcEval(i, k-1, exp, 0, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 0, mem);
        count += leftCount*rightCount;
      }
    } else if(opr == '|') {
      if(target == 1) {
        leftCount = calcEval(i, k-1, exp, 1, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 1, mem);
        count += leftCount*rightCount;
        leftCount = calcEval(i, k-1, exp, 0, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 1, mem);
        count += leftCount*rightCount;
        leftCount = calcEval(i, k-1, exp, 1, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 0, mem);
        count += leftCount*rightCount;
      } else if(target == 0) {
        leftCount = calcEval(i, k-1, exp, 0, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 0, mem);
        count += leftCount*rightCount;
      }
    } else if(opr == '^') { // xor case
      if(target == 0) {
        leftCount = calcEval(i, k-1, exp, 0, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 0, mem);
        count += leftCount*rightCount;
        leftCount = calcEval(i, k-1, exp, 1, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 1, mem);
        count += leftCount*rightCount;
      } else if(target == 1) {
        leftCount = calcEval(i, k-1, exp, 1, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 0, mem);
        count += leftCount*rightCount;
        leftCount = calcEval(i, k-1, exp, 0, mem);
        if(leftCount != 0) rightCount = calcEval(k+1, j, exp, 1, mem);
        count += leftCount*rightCount;
      }
    }
  }
  // mem[i][j][target] = count;
  return count;
}

int evalBoolExp(string exp, int target) {
  int n = exp.size();
  vector<vector<vector<int>>> mem(n, vector<vector<int>> (n, vector<int>(2,-1)));
  int count = calcEval(0, exp.size()-1, exp, target, mem);
  return count;
}

int main() {
  // string istr = "1^0|0|1";
  string istr = "0&0&0&1^1|0";

  cout << evalBoolExp(istr, true) << endl;
}