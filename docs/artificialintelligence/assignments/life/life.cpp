#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<bool>> board;

struct point
{
  point(int x, int y) {
    this->x = x;
    this->y = y;
  }
  int x;
  int y;
};


vector<vector<bool>> generateBoard(point p) {
  vector<vector<bool>> board;
  for (int l = 0; l < p.y; l++) 
  {
    vector<bool> line;
    line.reserve(p.x);
    for (int c = 0; c < p.x; c++)
    {
      line.push_back(false);
    }
    board.push_back(line);
  }

  return board;
}

void readBoard(point p)
{
  for (int l = 0; l < p.y; l++) {
    
    string line;
    cin >> line;
    
    for (int c = 0; c < p.x; c++) {
      board[l][c] = (line[c] == '#');
    }
  }
}

void printBoard(point p)
{
  for (int l = 0; l < p.y; l++) {
    for (int c = 0; c < p.x; c++) {
      if (board[l][c]) {
        cout << "#";
      } else {
        cout << ".";
      }
    }
  }
}

int main() {  
  int x, y, numSteps;
  cin >> x >> y >> numSteps;
 


}