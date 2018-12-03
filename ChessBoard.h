#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessPiece.h"

class ChessBoard
{

  ChessPiece* current_board[8][8];
  Colour current_turn;
  void nextTurn() {current_turn == White? current_turn = Black : current_turn = White;}
public:
  ChessBoard();
  ~ChessBoard();
  void clearBoard();
  void setBoard();
  void resetBoard();
  void displayBoard();
  void submitMove(const char *source_square, const char *destination_square);
  void makeMove(ChessPiece *&s_piece, ChessPiece *&d_piece);
};


#endif //CHESSBOARD_H
