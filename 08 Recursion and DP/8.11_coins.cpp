#include <iostream>
#include <vector>
#define long long long int
using namespace std;

// Goes through each unique coin sequences 
// Exponential Time
int ways(int n, vector<int> &coins, int coinIndex) {
  cout << n << " " << coinIndex << endl;
  if(n == 0) return 1;
  if(coinIndex == coins.size()) return 0;
  int coin = coins[coinIndex];
  int count = 0;
  for(int i=0; i<=n; i+=coin)
    if(n-i >= 0) count += ways(n-i, coins, coinIndex+1);
  return count;
}

int coinsWays(int n, vector<int> coins) {
  return ways(n, coins, 0);
}

// DP Approach
// Time: O(n^3)
int coinsWays_fast(int n, vector<int> coins) {
  vector<vector<int>> dp(n+1, vector<int>(coins.size()+1, 0));
  for(int i=0; i<=coins.size(); i++) dp[0][i] = 1; //first row set to 1
  
  for(int j=coins.size()-1; j>=0; j--) {
    for(int i=1; i<=n; i++) { // i amount, j'th coin
      for(int k=0; k<=i; k+=coins[j])
        dp[i][j] += dp[i-k][j+1];
    }
  }
  return dp[n][0];
}

int main() {
  int n = 5;
  vector<int> coins {1,2,5};
  cout << coinsWays_fast(n, coins) << endl;
}