//
// Author: Ibraheem El Sheikha
//

#include "reversi.h"
#include <stdio.h>
#include <string.h>

void printBoard(char board[][26], int n) {
  //print column letters
  printf("  ");
  for (int col = 0; col < n; col++) {
    printf("%c", 'a'+col);
  }
  
  //print row letters
  for (int row = 0; row < n; row++) {
    printf("\n");
    printf("%c ", 'a'+row);
    for (int col = 0; col < n; col++) {
      printf("%c", board[row][col]);
    }
  }

  printf("\n");
  return;
}

bool positionInBounds(int n, int row, int col) {
  return (col >= 0 && col < n && row >= 0 && row < n);
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
  
  if (board[row][col] != 'U' || !positionInBounds(n, row, col)) {
    return false;
  }

  int newRow = row + deltaRow;
  int newCol = col + deltaCol;

  //if new position out of bounds, return false
  if ((!positionInBounds(n, newRow, newCol)) || 
      (board[newRow][newCol] == colour) || 
      (board[newRow][newCol] == 'U'))
    return false;

  //while the new position is in bounds and there is a piece in the direction we are travelling, keep checking in that direction
  while ((positionInBounds(n, newRow, newCol)) &&
          (board[newRow][newCol] != colour) &&
          (board[newRow][newCol] != 'U')) {
    newRow += deltaRow;
    newCol += deltaCol;
  }

  if (!positionInBounds(n, newRow, newCol)) {
    return false;
  }
  
  if (board[newRow][newCol] == colour) {
    return true;
  }
  
  return false;
}

char numToLetter(int num) {
  return 'a' + num;
}

void flipTiles(char board[][26], int n, int row, int col, char colour) {
  
  for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      
      if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) {
        int newRow = row + deltaRow;
        int newCol = col + deltaCol;
        
        while (board[newRow][newCol] != colour) {
          board[newRow][newCol] = colour;
          newRow += deltaRow;
          newCol += deltaCol;
        }
      }  
    }
  }
  
  return;
}

void printLegalMoves(char board[][26], int n, int row, int col, char colour) {
  for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) {
        printf("%c%c\n", numToLetter(row), numToLetter(col));
        return;
      }
    }
  }
}

bool isLegalMove(char board[][26], int n, int row, int col, char colour) {
  for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol))
        return true;
    }
  }
  return false;
}

int main(void) {
  //board initialization and print
  int n;
  printf("Enter the board dimension: ");
  scanf("%d", &n);
  char board[26][26];
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      board[row][col] = 'U';
    }
  }
  board[n/2][n/2] = 'W';
  board[n/2 - 1][n/2 - 1] = 'W';
  board[n/2 - 1][n/2] = 'B';
  board[n/2][n/2 - 1] = 'B';
  printBoard(board, n);

  //board configuration input
  char input[3+1];
  printf("Enter board configuration:\n");
  scanf("%s", input);

  //editing then printing board after board configuration
  while(strcmp(input, "!!!") != 0) {
    int row = input[1] - 'a';
    int col = input[2] - 'a';
    board[row][col] = input[0];
    scanf("%s", input);
  }
  printBoard(board, n);

  //print available moves
  printf("Available moves for W:\n");
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'U') {
        printLegalMoves(board, n, row, col, 'W');
      }
    }
  }

  printf("Available moves for B:\n");
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'U') {
        printLegalMoves(board, n, row, col, 'B');
      }
    }
  }

  char move[3+1];
  printf("Enter a move:\n");
  scanf("%s", move);
  int rowMove = move[1] - 'a';
  int colMove = move[2] - 'a';
  char colour = move[0];

  if (isLegalMove(board, n, rowMove, colMove, colour)) {
    printf("Valid move.\n");
    flipTiles(board, n, rowMove, colMove, colour);
    board[rowMove][colMove] = colour;
  } else {
    printf("Invalid move.\n");
  }

  printBoard(board, n);

  return 0;
}
