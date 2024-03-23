#include "ArgumentManager.h"
#include "Stack.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

void DrawBoard(string **, const int, const int, const int, ofstream &);
bool safePosition(const int, const int, const int, const int);
int KnightTour(string **, int, int, int, int, int &, int, int const, int const);

// void createQueue(queue &KnightMove) {
//   KnightMove.enqueue(-1, 2, 0);
//   KnightMove.enqueue(-2, 1, 1);
//   KnightMove.enqueue(-2, -1, 2);
//   KnightMove.enqueue(-1, -2, 3);
//   KnightMove.enqueue(1, -2, 4);
//   KnightMove.enqueue(2, -1, 5);
//   KnightMove.enqueue(2, 1, 6);
//   KnightMove.enqueue(1, 2, 7);
// }

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string input = am.get("input");
  string output = am.get("output");
  ifstream fin(input);
  ofstream fout(output);
  if (!fin.is_open()) {
    fout << "File is not open" << endl;
    return 1;
  }

  int numRow, numCol;
  int numRHoles, numCHoles;
  int numHoles;
  int row, col;
  int numMoves;

  fin >> numRow >> numCol;
  // if (numRow != numCol) {
  //   fout << "A closed tour does not exist!";
  //   return 0;
  // }

  fin >> row >> col;
  int initialRow = row;
  int initialCol = col;
  
  string **board = new string *[numRow];
  for (int i = 0; i < numRow; i++) {
    board[i] = new string[numCol];
    for (int j = 0; j < numCol; j++) {
      board[i][j] = " ";
    }
  }

  // queue KnightMove;
  // createQueue(KnightMove);
  // cout << example.row << " " << example.col << " " << example.priority;

  numMoves = numRow * numCol;
  fin >> numHoles;
  int count = 0;
  while (count != numHoles) {
    fin >> numRHoles >> numCHoles;
    board[numRHoles][numCHoles] = "XX";
    count++;
  }
  numMoves -= numHoles;
  int count2 = 2;
  if (KnightTour(board, row, col, numRow, numCol, count2, numHoles, initialRow,
                 initialCol) == 1) {
    fout << "A closed tour exists!" << endl;
    DrawBoard(board, numRow, numCol, numMoves, fout);
  } else {
    fout << "A closed tour does not exist!";
  };
  for (int i = 0; i < numRow; i++) {
    delete[] board[i];
  }
  delete[] board;

  return 0;
}

void DrawBoard(string **board, const int numRow, const int numCol, int numMoves, ofstream &fout) {
  fout << "+";
  for (int i = 0; i < numCol; i++) {
    fout << "--+";
  }
  fout << endl;
  for (int row = 0; row < numRow; row++) {
    fout << "|";
    for (int col = 0; col < numCol; col++) {
      // if (board[row][col]) {
      //   cout << "XX|";
      // } else {
      //   cout << " |";
      // }
      fout << board[row][col] << "|";
    }
    fout << endl;
    fout << "+";
    for (int i = 0; i < numCol; i++) {
      fout << "--+";
    }
    fout << endl;
  }
}

bool safePosition(const int row, const int col, const int numRow,
                  const int numCol) {
  return (row >= 0 && col >= 0 && row < numRow && col < numCol);
}

int KnightTour(string **board, int row, int col, int numRow, int numCol,
               int &numMoves, int numHoles, int initialRow, int initialCol) {
  if (numMoves == numRow * numCol - numHoles + 2 && row == initialRow &&
      col == initialCol) {
    return 1;
  }
  for (int i = 0; i < 8; i++) {
    int rowMoves[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
    int colMoves[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int newRow = row + rowMoves[i];
    int newCol = col + colMoves[i];
    if (safePosition(newRow, newCol, numRow, numCol) &&
        board[newRow][newCol] == " ") {
      if (numMoves < numRow * numCol - numHoles + 1) {
        if (numMoves < 10) {
          board[newRow][newCol] = " " + to_string(numMoves);
        } else {
          board[newRow][newCol] = to_string(numMoves);
        }
      } else {
        board[initialRow][initialCol] = " 1";
      }
      numMoves++;
      if (KnightTour(board, newRow, newCol, numRow, numCol, numMoves, numHoles,
                     initialRow, initialCol) == 1) {
        return 1;
      }
      board[newRow][newCol] = " ";
      numMoves--;
    }
  }
  return 0;
}
