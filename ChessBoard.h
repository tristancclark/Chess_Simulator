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
  void makeMove(const char *s_square, const char *d_square, int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8]);
  bool isInCheck(Colour colour, ChessPiece *cb[8][8]);
  bool isInStalemate(Colour colour, ChessPiece *cb[8][8]);
  bool isInCheckmate(Colour colour, ChessPiece *cb[8][8]);
  void findPiece(char name, Colour colour, int &row, int &column, ChessPiece* cb[8][8]);
  void imitateMove(ChessPiece *cb[8][8], ChessPiece *imitation_board[8][8], int s_row, int s_column, int d_row, int d_column);
};


#endif //CHESSBOARD_H
