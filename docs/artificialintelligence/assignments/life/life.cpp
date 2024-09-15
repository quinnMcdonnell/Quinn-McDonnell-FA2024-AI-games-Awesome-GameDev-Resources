#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<bool>> board; // a double buffered variable that stores alive and dead cells as bools

struct point //a 2D point on said board
{
  point(int x, int y) {
    this->x = x;
    this->y = y;
  }
  int x; //line
  int y; //column
};

//Creates the board based on the size of the point p (2,2) is 2 x 2 grid
vector<vector<bool>> generateBoard(point p) {
  vector<vector<bool>> board;
  for (int l = 0; l < p.y; l++) 
  {
    vector<bool> line;
    line.reserve(p.x); //lines are made
    for (int c = 0; c < p.x; c++)
    {
      line.push_back(false); //columns are made
    }
    board.push_back(line);
  }

  return board;
}

void readBoard(point p)
{
  for (int l = 0; l < p.y; l++) {
    
    string line;
    cin >> line; //reads in a line from the inputted grid
    
    for (int c = 0; c < p.x; c++) {
      board[l][c] = (line[c] == '#'); //if a column has a alive(#) cell then it made true;
    }
  }
}

//basic nested foar loop that prints based on where or not a board[l][c] returns true or false
void printBoard(point p)
{
  for (int l = 0; l < p.y; l++) {
    for (int c = 0; c < p.x; c++) {
      if (board[l][c]) {
        cout << "#"; //if true = alive
      } else {
        cout << "."; //if false = dead
      }
    }
    cout << endl;
  }
}

//checks point above the checked p
point getTop(point p, point l) {
  p.y--;

  if (p.y < 0) {
    p.y = l.y - 1;
  }

  return p;
}

// checks point below the checked p
point getBottom(point p, point l) { 
    p.y++;
    p.y %= l.y;
    return p;
}

// checks point to the right of the checked p
point getRight(point p, point l) {
  p.x++;
  p.x %= l.x;
  return p;
}

// checks point to the left of the checked p
point getLeft(point p, point l) {
  p.x--;

  if (p.x < 0) {
    p.x = l.x - 1;
  }

  return p;
}

//counts up the total neighbors excluding oneself
int getNeighbors(point p, point lim) //lim is the size of board itself and go to opposite side if it surpasses the size (ex 2 -> 0) in a 3x3 grid
{ 
    int count = 0;

    //checks regular directions using functions above
    auto t = getTop(p, lim);
    auto b = getBottom(p, lim);
    auto r = getRight(p, lim);
    auto l = getLeft(p, lim);

    //checks for other directions using top or bottom as the new check
    auto tr = getRight(t, lim);
    auto tl = getLeft(t, lim);
    auto br = getRight(b, lim);
    auto bl = getLeft(b, lim);
    
    //if a statement returns true, the count goes up, so if . then no if # then yes
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

    return count; //returns count
}

//the steps being done
void Step(point l)
{ 
    auto nBoard = board;

    for(int line = 0; line < l.y; line++) 
    {
      for (int col = 0; col < l.x; col++) 
      {
        auto neighbor = getNeighbors({col, line}, l);
        auto alive = board[line][col];

        if (alive && (neighbor == 2 || neighbor == 3)) //checks if the cell is alive and has between 2 - 3 neighbors
        {
            nBoard[line][col] = true;
        } else if (!alive && neighbor == 3)  //if it isn't allive but has three neighbors, it becomes alive
        {
            nBoard[line][col] = true;
        } else 
        {
          nBoard[line][col] = false; //if statements above are not met, then the cell dies
        }

      } 
    }

    board = nBoard; //returns the new board
}

int main() {  
  int c, l, numSteps;
  cin >> c >> l >> numSteps; //takes in the top 3 variables from test
 
  board = generateBoard({c, l}); //takes the grid in based on the 3 said values above c and l determining grid size

  readBoard({c, l});
  cout << endl << "result after " << numSteps << " steps" << endl << endl; //extra statement to show the final result

  for (int i = 0; i < numSteps; i++) //does blank number of steps based on the numSteps value
  {
    Step({c, l}); //does step

  }

  printBoard({c, l}); //the final result

}