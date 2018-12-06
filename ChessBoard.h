#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessPiece.h"

class ChessBoard
{
private:
  ChessPiece* cb[8][8]; //current board represents real positions of pieces
  Colour current_turn; //records who's turn: White/Black

  //Switches current_turn to other colour
  void nextTurn() {current_turn == White? current_turn = Black : current_turn = White;}

  //Frees all heap memory and sets all contents of cb
  //to nullptrs
  void clearBoard();

  //Sets up board by creating pieces on the heap with their corresponding
  // pointers being located in their 'positions' in cb
  void setBoard();

  //Moves piece located at s to d on cb
  void makeMove(Position s, Position d);

  //Returns true if team 'colour' are in check in the board passed as an
  // argument. Returns false otherwise.
  bool isInCheck(Colour colour, ChessPiece *cb[8][8]);

  //Returns true if team 'colour' are in stalemate in cb.
  //Returns false otherwise.
  bool isInStalemate(Colour colour);

  //Returns true if team 'colour' are in checkmate in cb.
  //Returns false otherwise.
  bool isInCheckmate(Colour colour);

  //Returns the Position of the King piece on team 'colour'.
  Position findKing(Colour colour, ChessPiece *cb[8][8]);

  //Copies contents of cb to ib then moves piece in position s to d (on ib).
  void imitateMove(ChessPiece *cb[8][8], ChessPiece *ib[8][8], Position s, Position d);

public:

  //Calls setBoard().
  ChessBoard();

  //calls clearBoard().
  ~ChessBoard();

  //Checks for errors in submition of moves. Checks for validity of move.
  //Send messages to standard output on any errors.
  //Checks for stalemate and checkmate after each move and if they occer
  // then send messages to standard output.
  void submitMove(const char *s_square, const char *d_square);

  //calls clearBoard() followed by setBoard().
  void resetBoard();
};


#endif //CHESSBOARD_H
