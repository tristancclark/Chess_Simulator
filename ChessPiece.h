#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <iostream>
using namespace std;

enum Colour {Black, White};
//BASE CLASS CHESS PIECE

class ChessPiece
{
  Colour colour;
  char name;
public:
  ChessPiece(Colour colour, char name);
  virtual ~ChessPiece() = 0;
  virtual bool isValidMove() = 0;

  void setColour(Colour colour);
  char getName(){return name;}
};

class Pawn : public ChessPiece
{
public:
  bool been_moved;
  bool isValidMove() {return true;}
  Pawn(Colour colour);
  ~Pawn(){}
};

class Castle : public ChessPiece
{
public:
  Castle(Colour colour);
  ~Castle(){}
  bool isValidMove() {return true;}
};

class Knight : public ChessPiece
{
public:
  Knight(Colour colour);
  ~Knight(){}
  bool isValidMove() {return true;}
};

class Bishop : public ChessPiece
{
public:
  Bishop(Colour colour);
  ~Bishop(){}
  bool isValidMove() {return true;}
};

class King : public ChessPiece
{
public:
  King(Colour colour);
  ~King(){}
  bool isValidMove() {return true;}
};

class Queen : public ChessPiece
{
public:
  Queen(Colour colour);
  ~Queen(){}
  bool isValidMove() {return true;}
};

#endif //CHESSPIECE_H
