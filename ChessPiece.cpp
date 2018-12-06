#include <iostream>
#include <cctype>
#include "ChessPiece.h"
using namespace std;

//OPERATOR OVERLOADS

ostream &operator<<(ostream &o, Colour c)
{
  if (c == White)
    o << "White";
  if (c == Black)
    o << "Black";
  return o;
}

ostream &operator<<(ostream &o, Position p)
{
  char position[2];
  int ascii_letter_shift = 'A';
  int ascii_number_shift = '0' + 8;
  position[1] = abs(static_cast<char>(p.row - ascii_number_shift));
  position[0] = static_cast<char>(p.column + ascii_letter_shift);
  cout << position;
  return o;
}

//CHESSPIECE FUNCTIONS
ChessPiece::ChessPiece(Colour col) : colour(col), been_moved(false)
{}

ChessPiece::~ChessPiece() {}

ostream& operator<<(ostream& o, ChessPiece*& cp)
{
  cout << cp->getColour() << "'s " << cp->getName();
  return o;
}

//PAWN FUNCTIONS
Pawn::Pawn(Colour colour) : ChessPiece(colour){}

bool Pawn::isValidMove(Position s, Position d, ChessPiece *cb[8][8])
{
  int direction, move_forward, move_side;
  ChessPiece *d_piece = cb[d.row][d.column];
  getColour() == Black ? direction = 1 : direction = -1;
  move_forward = (d.row - s.row)*direction; //squares forward pawn is trying to move
  move_side = abs(d.column - s.column);

  if (d_piece == nullptr) //if nothing in destination square
  {
    if (s.column != d.column) //if pawn tries to move out of column
    {

      return false;
    }

    if (move_forward == 1) //move forwards 1 always valid
    {
      return true;
    }

    if (!hasBeenMoved() && move_forward == 2) //not been moved and move forwards 2
    {
      if (cb[s.row + direction][s.column] == nullptr) //square ahead is empty
      {
        return true;
      }
    }
    return false;
  }

  //if opposite colour in desination square and diagonal 1 square
  if (move_forward == 1 && move_side == 1)
  {
    return true;
  }
  return false;
}

string Pawn::getName()
{
  return "Pawn";
}

//CASTLE FUNCTIONS
Castle::Castle(Colour colour) : ChessPiece(colour){}

bool Castle::isValidMove(Position s, Position d, ChessPiece *cb[8][8])
{
  int start_row, start_column;
  int move_hor = abs(d.column - s.column);
  int move_vert = abs(d.row - s.row);

  //set starting row/column to the smaller row/column:
  d.column > s.column ? start_column = s.column : start_column = d.column;
  d.row > s.row ? start_row = s.row : start_row = d.row;

  if (s.row == d.row) //if move along a row
  {
    for (int i = 1; i < move_hor; i++) //check if any piece is in the way
    {
      if (cb[s.row][start_column+i] != nullptr)
      {
        return false;
      }
    }
    return true;
  }

  if (s.column == d.column) //if move along a column
  {
    for (int i = 1; i < move_vert; i++) //check if any piece in the way
    {
      if (cb[start_row + i][s.column] != nullptr)
      {
        return false;
      }
    }
    return true;
  }
  return false;
}

string Castle::getName()
{
  return "Castle";
}

//BISHOP FUNCTIONS
Bishop::Bishop(Colour colour) : ChessPiece(colour){}

bool Bishop::isValidMove(Position s, Position d, ChessPiece *cb[8][8])
{
  int start_row, start_column;
  int move_hor = d.column - s.column;
  int move_vert = d.row - s.row;
  int gradient;

  //set starting row/column to smaller row/column
  d.column > s.column ? start_column = s.column : start_column = d.column;
  d.row > s.row ? start_row = s.row : start_row = d.row;

  if (abs(move_vert) != abs(move_hor)) //if not a diagonal move
  {
    return false;
  }

  //find gradient of move
  (move_hor < 0)==(move_vert < 0) ? gradient = 1 : gradient = -1;

  if (gradient == 1) //if move has +ve gradient
  {
    for (int i = 1; i < abs(move_hor); i++) //check if any piece in the way
    {
      if (cb[start_row + i][start_column + i] != nullptr)
      {
        return false;
      }
    }
    return true;
  }

  //if gradient is -ve:

  //set start row too larger row and start column to smaller column
  d.column > s.column ? start_column = s.column : start_column = d.column;
  d.row < s.row ? start_row = s.row : start_row = d.row;

  for (int i = 1; i < abs(move_hor); i++) //check if any piece in the way
  {
    if (cb[start_row - i][start_column + i] != nullptr)
    {
      return false;
    }
  }
  return true;
}

string Bishop::getName()
{
  return "Bishop";
}

//KNIGHT FUNCTIONS
Knight::Knight(Colour colour) : ChessPiece(colour){}

bool Knight::isValidMove(Position s, Position d, ChessPiece *cb[8][8])
{
  int move_hor = abs(d.column - s.column);
  int move_vert = abs(d.row - s.row);

  //check for L shape move
  if ((move_vert == 1 && move_hor == 2) || (move_vert == 2 && move_hor == 1))
  {
    return true;
  }
  return false;
}

string Knight::getName()
{
  return "Knight";
}

//KING FUNCTIIONS
King::King(Colour colour) : ChessPiece(colour), check(false){}

bool King::isValidMove(Position s, Position d, ChessPiece *cb[8][8])
{
  int move_hor = d.column - s.column;
  int move_vert = d.row - s.row;

  //check one square diagonally
  if (abs(move_hor) == 1 && abs(move_vert) == abs(move_hor))
  {
    return true;
  }

  //check for one square along row or column
  if ((abs(move_hor) == 1 && abs(move_vert) == 0) || (abs(move_hor) == 0 && abs(move_vert) == 1))
  {
    return true;
  }

  if (!isInCheck())
  {
    if (!hasBeenMoved()) //check for castling
    {
      if (move_hor == 2 && move_vert == 0)
      {
        if (cb[s.row][s.column+1] == nullptr && cb[s.row][s.column+2] == nullptr) //check two squares empty
        {
          if (cb[s.row][s.column + 3] != nullptr) //check if castle still there
          {
            if (!(cb[s.row][s.column + 3]->hasBeenMoved())) //check if castle been moved
            {
              return true;
            }
          }
        }
      }
      if (move_hor == -2 && move_vert == 0)
      {
        if (cb[s.row][s.column-1] == nullptr && cb[s.row][s.column-2] == nullptr
          && cb[s.row][s.column-3] == nullptr) //check three left squares empty
          {
            if (cb[s.row][s.column - 4] != nullptr)
            {
              if (!(cb[s.row][s.column - 4]->hasBeenMoved())) //check if castle been moved
              {
                return true;
              }
            }
          }
        }
      }
    }
      return false;
  }

string King::getName()
{
  return "King";
}

//QUEEN FUNCTIONS
Queen::Queen(Colour colour) : ChessPiece(colour){}

bool Queen::isValidMove(Position s, Position d, ChessPiece *cb[8][8])
{
  int start_row, start_column;
  int move_hor = d.column - s.column;
  int move_vert = d.row - s.row;
  int gradient;

  //set start row/column to smaller row/column number
  d.column > s.column ? start_column = s.column : start_column = d.column;
  d.row > s.row ? start_row = s.row : start_row = d.row;

  if (abs(move_vert) == abs(move_hor)) //if a diagonal move
  {
    //find gradient
    (move_hor < 0)==(move_vert < 0) ? gradient = 1 : gradient = -1;

    if (gradient == 1) //if move has +ve gradient
    {
      for (int i = 1; i < abs(move_hor); i++) //check if any piece in the way
      {
        if (cb[start_row + i][start_column + i] != nullptr)
        {
          return false;
        }
      }
      return true;
    }
    //if gradient is -ve:

    //set start column to smaller column number and start row to larger row number
    d.column > s.column ? start_column = s.column : start_column = d.column;
    d.row < s.row ? start_row = s.row : start_row = d.row;

    for (int i = 1; i < abs(move_hor); i++) //check if anytpiece in the way
    {
      if (cb[start_row - i][start_column + i] != nullptr)
      {
        return false;
      }
    }
    return true;
  }

  //if a straight move:

  if (s.row == d.row) //if move along a row
  {
    for (int i = 1; i < abs(move_hor); i++) //check if any piece in the way
    {
      if (cb[s.row][start_column+i] != nullptr)
      {
        return false;
      }
    }
    return true;
  }

  if (s.column == d.column) //if move along a column
  {
    for (int i = 1; i < abs(move_vert); i++) //check if any piece in the way
    {
      if (cb[start_row + i][s.column] != nullptr)
      {
        return false;
      }
    }
    return true;
  }
  return false;
}

string Queen::getName()
{
  return "Queen";
}
