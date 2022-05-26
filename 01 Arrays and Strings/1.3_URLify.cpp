#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

// O(n) time, O(1) space (Doing it in place)
// Logic: Start processing from end
void URLify(string &str, int &len) {

  int spaceCount = 0;
  for(int i=0; i<len; i++) if(str[i] == ' ') spaceCount++; // actual word-spaces
  int spacesAtEnd = spaceCount*2; // spaces required at the end
  if(str.length() > len + spacesAtEnd) str[len + spacesAtEnd] = '\0'; // in case of excess space

  int i = len-1;
  int j = len + spacesAtEnd - 1;

  while(j>=0) {
    if(str[i] == ' ') {
      str[j--] = '0';
      str[j--] = '2';
      str[j--] = '%';
    } else {
      str[j] = str[i];
      j--;
    }
    cout << str << endl;
    i--;
  }
}

int main() {
  string mystr = "Mr John Smith                ";
  int len = 13;
  URLify(mystr,len);
  cout << mystr << endl;
}