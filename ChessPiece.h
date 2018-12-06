#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <iostream>
using namespace std;

//define struct Position
struct Position
{
  int row;
  int column;
};
ostream &operator<<(ostream &o, Position p);

//define enum Colour
enum Colour {Black, White};
ostream &operator<<(ostream &o, Colour c);


//BASE CLASS CHESS PIECE
class ChessPiece
{
  Colour colour; //colour of piece: Black or White
  bool been_moved; //initialise to false, once moved = true

public:
  //initialises colour and been_moved set to false
  ChessPiece(Colour colour);

  //pure virtual destructor
  virtual ~ChessPiece() = 0;

  //Pure virtual function. Checks if piece at s is allowed to move to d and
  // if any other piece is in the way. Does not take into account what lies
  //in destination square. Returns true if valid and false otherwise.
  virtual bool isValidMove(Position s, Position d, ChessPiece *cb[8][8]) = 0;

  //Pure virtual function. Returns sting containing piece name. E.g "King"
  virtual string getName() = 0;

  //Getter function returning piece colour
  Colour getColour(){return colour;}

  //Setter function setting been_moved to true.
  void setBeenMoved(){been_moved = true;}

  //Getter function returning whether piece has previously been moved.
  bool hasBeenMoved(){return been_moved;}

  //Friend function overloading insertion operator. If ChessPiece pointer
  //placed as such: outputstream << ChessPiece*, then piece name is outputted
  //to that stream.
  friend ostream& operator<<(ostream& o, ChessPiece *&cp);
};

//DERVIVED CLASS PAWN
class Pawn : public ChessPiece
{
public:
  Pawn(Colour colour);
  ~Pawn(){}
  bool isValidMove(Position s, Position d, ChessPiece *cb[8][8]) override;
  string getName() override;
};

//DERVIVED CLASS CASTLE
class Castle : public ChessPiece
{
public:
  Castle(Colour colour);
  ~Castle(){}
  bool isValidMove(Position s, Position d, ChessPiece *cb[8][8]) override;
  string getName() override;
};

//DERVIVED CLASS BISHOP
class Bishop : public ChessPiece
{
public:
  Bishop(Colour colour);
  ~Bishop(){}
  bool isValidMove(Position s, Position d, ChessPiece *cb[8][8]) override;
  string getName() override;
};

//DERVIVED CLASS KNIGHT
class Knight : public ChessPiece
{
public:
  Knight(Colour colour);
  ~Knight(){}
  bool isValidMove(Position s, Position d, ChessPiece *cb[8][8]) override;
  string getName() override;
};

//DERVIVED CLASS KING
class King : public ChessPiece
{
  bool check; //records whether King is in check
public:
  King(Colour colour);
  ~King(){}
  bool isValidMove(Position s, Position d, ChessPiece *cb[8][8]) override;
  string getName() override;

  //Setter function sets Check to bool ch
  void setCheck(bool ch){check = ch;}

  //Getter function returns whether King is in check.
  bool isInCheck(){return check;}
};

//DERVIVED CLASS QUEEN
class Queen : public ChessPiece
{
public:
  Queen(Colour colour);
  ~Queen(){}
  bool isValidMove(Position s, Position d, ChessPiece *cb[8][8]) override;
  string getName() override;
};

#endif //CHESSPIECE_H
