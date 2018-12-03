#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessPiece.h"

class ChessBoard
{

  ChessPiece* current_board[8][8];
  Colour current_turn;
public:
  ChessBoard();
  ~ChessBoard();
  void clearBoard();
  void setBoard();
  void resetBoard();
  void displayBoard();
  void submitMove(const char source_square[2], const char destination_square[2]);
  void makeMove(int s_row, int s_column, int d_row, int d_column);
};


#endif //CHESSBOARD_H
