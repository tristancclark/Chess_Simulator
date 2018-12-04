#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <iostream>
using namespace std;


enum Colour {Black, White};

inline ostream &operator<<(ostream &o, Colour c)
{
  if (c == White)
    o << "White";
  if (c == Black)
    o << "Black";
  return o;
}


//BASE CLASS CHESS PIECE
class ChessPiece
{
  Colour colour;
  char name;
public:
  ChessPiece(Colour colour, char name);
  virtual ~ChessPiece() = 0;
  virtual bool isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8]) = 0;

  void setColour(Colour col){colour = col;}
  Colour getColour(){return colour;}
  char getName(){return name;}
};

class Pawn : public ChessPiece
{
public:
  bool been_moved;
  bool isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8]) override;
  Pawn(Colour colour);
  ~Pawn(){}
};

class Castle : public ChessPiece
{
public:
  Castle(Colour colour);
  ~Castle(){}
  bool isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8]) override;
};

class Bishop : public ChessPiece
{
public:
  Bishop(Colour colour);
  ~Bishop(){}
  bool isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8]) override;
};

class Knight : public ChessPiece
{
public:
  Knight(Colour colour);
  ~Knight(){}
  bool isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8]) override;
};

class King : public ChessPiece
{
public:
  King(Colour colour);
  ~King(){}
  bool isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8]) override;
};

class Queen : public ChessPiece
{
public:
  Queen(Colour colour);
  ~Queen(){}
  bool isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8]) override;
};

#endif //CHESSPIECE_H
