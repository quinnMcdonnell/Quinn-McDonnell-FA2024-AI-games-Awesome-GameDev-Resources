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
    cout << endl;
  }
}

point getTop(point p, point l) {
  p.y--;

  if (p.y < 0) {
    p.y = l.y - 1;
  }

  return p;
}

point getBottom(point p, point l) { 
    p.y++;
    p.y %= l.y;
    return p;
}

point getRight(point p, point l) {
  p.x++;
  p.x %= l.x;
  return p;
}

point getLeft(point p, point l) {
  p.x--;

  if (p.x < 0) {
    p.x = l.x - 1;
  }

  return p;
}

int getNeighbors(point p, point lim)
{ 
    int count = 0;

    auto t = getTop(p, lim);
    auto b = getBottom(p, lim);
    auto r = getRight(p, lim);
    auto l = getLeft(p, lim);

    auto tr = getRight(t, lim);
    auto tl = getLeft(t, lim);
    auto br = getRight(b, lim);
    auto bl = getLeft(b, lim);
    
    if (board[t.y][t.x])
    {
      count++;
    }
    if (board[b.y][b.x]) {
      count++;
    }
    if (board[r.y][r.x]) {
      count++;
    }
    if (board[l.y][l.x]) {
      count++;
    }

     if (board[tr.y][tr.x]) {
      count++;
    }
    if (board[tl.y][tl.x]) {
      count++;
    }
    if (board[br.y][br.x]) {
      count++;
    }
    if (board[bl.y][bl.x]) {
      count++;
    }

    return count;
}

void Step(point l)
{ 
    auto nBoard = board;

    for(int line = 0; line < l.y; line++) 
    {
      for (int col = 0; col < l.x; col++) 
      {
        auto neighbor = getNeighbors({col, line}, l);
        auto alive = board[line][col];

        if (alive && (neighbor == 2 || neighbor == 3))
        {
            nBoard[line][col] = true;
        } else if (!alive && neighbor == 3) 
        {
            nBoard[line][col] = true;
        } else 
        {
          nBoard[line][col] = false;
        }

      } 
    }

    board = nBoard;
}

int main() {  
  int c, l, numSteps;
  cin >> c >> l >> numSteps;
 
  board = generateBoard({c, l});

  readBoard({c, l});
  cout << "result after " << numSteps << " steps" << endl << endl;

  for (int i = 0; i < numSteps; i++)
  {
    Step({c, l});

  }

  printBoard({c, l});

}