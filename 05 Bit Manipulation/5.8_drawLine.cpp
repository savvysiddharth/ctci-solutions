#include <iostream>
using namespace std;

const int height = 12;
const int width = 12;

void printBits(char x) {
  int count = 0;
  string str = "";
  while(1) {
    count++;
    if(count > 8) break;
    int bit = x & 1;
    str = to_string(bit) + str;
    x >>= 1;
  }
  cout << str;
}

void displayScreen(char screen[][width]) {
  for(int i=0; i<height; i++) {
    for(int j=0; j<width; j++) {
      printBits(screen[i][j]); cout << " ";
    } cout << endl;
  }
}

void drawLine(char screen[][width], int x1, int x2, int y) {
  int arrayX1 = x1/8;
  int arrayX2 = x2/8;

  if(arrayX1 > arrayX2) swap(arrayX1, arrayX2);
  else if(arrayX1 == arrayX2) {
    x1 = 7 - (x1 % 8);
    x2 = 7 - (x2 % 8);
    if(x1 > x2) swap(x1, x2);
    char left = -1;
    left = left << (x2+1);
    char right = 1;
    right = (right << x1) - 1;
    screen[y][arrayX1] = ~(left | right);
    return;
  }

  for(int i=arrayX1; i <= arrayX2; i++) {
    if(i != arrayX1 && i != arrayX2) screen[y][i] = -1;
    else if(i == arrayX1) {
      int bitPos = 7 - (x1 % 8);
      screen[y][i] = 1;
      screen[y][i] = (screen[y][i] << (bitPos+1)) - 1;
    } else if(i == arrayX2) {
      int bitPos = 7 - (x2 % 8);
      screen[y][i] = -1;
      screen[y][i] = screen[y][i] << bitPos;
    }
  }
}

int main() {
  char screen[height][width] = {};
  displayScreen(screen); cout << "-------------\n";

  drawLine(screen, 4, 88, 5);
  
  displayScreen(screen); cout << "-------------\n";

}