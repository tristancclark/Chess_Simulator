#include <iostream>
#include <cctype>
#include "ChessPiece.h"
using namespace std;

//CHESSPIECE FUNCTIONS
ChessPiece::ChessPiece(Colour col, char n) : colour(col), been_moved(false)
{}

ChessPiece::~ChessPiece() {}

//PAWN FUNCTIONS
Pawn::Pawn(Colour colour) : ChessPiece(colour, 'P'){}

bool Pawn::isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8])
{
  int direction, move_forward, move_side;
  ChessPiece *d_piece = cb[d_row][d_column];
  getColour() == Black ? direction = 1 : direction = -1;
  move_forward = (d_row - s_row)*direction; //squares forward pawn is trying to move
  move_side = abs(d_column - s_column);

  if (d_piece == nullptr) //if nothing in destination square
  {
    if (s_column != d_column) //if pawn tries to move out of column
    {

      return false;
    }

    if (move_forward == 1) //move forwards 1 always valid
    {
      return true;
    }

    if (!hasBeenMoved() && move_forward == 2) //not been moved and move forwards 2
    {
      if (cb[s_row + direction][s_column] == nullptr) //square ahead is empty
      {
        return true;
      }
    }
    return false;
  }

  //if opposite colour in desination square
  if (move_forward == 1 && move_side == 1)
  {
    return true;
  }
  return false;
}

char Pawn::getName()
{
  if (getColour() == White)
  {
    return 'p';
  }
  return 'P';
}

//CASTLE FUNCTIONS
Castle::Castle(Colour colour) : ChessPiece(colour, 'C'){}

bool Castle::isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8])
{
  int start_row, start_column;
  int move_hor = abs(d_column - s_column);
  int move_vert = abs(d_row - s_row);

  d_column > s_column ? start_column = s_column : start_column = d_column;
  d_row > s_row ? start_row = s_row : start_row = d_row;

  if (s_row == d_row) //move along a row
  {
    for (int i = 1; i < move_hor; i++) //check if any piece is in the way
    {
      if (cb[s_row][start_column+i] != nullptr)
      {
        return false;
      }
    }
    return true;
  }

  if (s_column == d_column) //move along a column
  {
    for (int i = 1; i < move_vert; i++) //check if any piece in the way
    {
      if (cb[start_row + i][s_column] != nullptr)
      {
        return false;
      }
    }
    return true;
  }
  return false;
}

char Castle::getName()
{
  if (getColour() == White)
  {
    return 'c';
  }
  return 'C';
}

//BISHOP FUNCTIONS
Bishop::Bishop(Colour colour) : ChessPiece(colour, 'B'){}

bool Bishop::isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8])
{
  int start_row, start_column;
  int move_hor = d_column - s_column;
  int move_vert = d_row - s_row;
  int gradient;

  d_column > s_column ? start_column = s_column : start_column = d_column;
  d_row > s_row ? start_row = s_row : start_row = d_row;

  if (abs(move_vert) != abs(move_hor)) //if not a diagonal move
  {
    return false;
  }

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
  d_column > s_column ? start_column = s_column : start_column = d_column;
  d_row < s_row ? start_row = s_row : start_row = d_row;
  for (int i = 1; i < abs(move_hor); i++)
  {
    if (cb[start_row - i][start_column + i] != nullptr)
    {
      return false;
    }
  }
  return true;
}

char Bishop::getName()
{
  if (getColour() == White)
  {
    return 'b';
  }
  return 'B';
}

//KNIGHT FUNCTIONS
Knight::Knight(Colour colour) : ChessPiece(colour, 'N'){}

bool Knight::isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8])
{
  int move_hor = abs(d_column - s_column);
  int move_vert = abs(d_row - s_row);

  //check for L shape move
  if ((move_vert == 1 && move_hor == 2) || (move_vert == 2 && move_hor == 1))
  {
    return true;
  }
  return false;
}

char Knight::getName()
{
  if (getColour() == White)
  {
    return 'n';
  }
  return 'N';
}

//KING FUNCTIIONS
King::King(Colour colour) : ChessPiece(colour, 'K'){}

bool King::isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8])
{
  int move_hor = d_column - s_column;
  int move_vert = d_row - s_row;

  if (abs(move_hor) == 1 && abs(move_vert) == abs(move_hor)) //check one square diagonally
  {
    return true;
  }

  //check for one square along row or column
  if ((abs(move_hor) == 1 && abs(move_vert) == 0) || (abs(move_hor) == 0 && abs(move_vert) == 1))
  {
    return true;
  }

  if (!hasBeenMoved()) //check for castling
  {
    if (move_hor == 2 && move_vert == 0)
    {
      if (cb[s_row][s_column+1] == nullptr && cb[s_row][s_column+2] == nullptr) //check two squares empty
      {
        if (cb[s_row][s_column + 3] != nullptr) //check if castle still there
        {
          if (!(cb[s_row][s_column + 3]->hasBeenMoved())) //check if castle been moved
          {
            return true;
          }
        }
      }
    }
    if (move_hor == -2 && move_vert == 0)
    {
      if (cb[s_row][s_column-1] == nullptr && cb[s_row][s_column-2] == nullptr
      && cb[s_row][s_column-3] == nullptr) //check three left squares empty
      {
        if (cb[s_row][s_column - 4] != nullptr)
        {
          if (!(cb[s_row][s_column - 4]->hasBeenMoved())) //check if castle been moved
          {
            return true;
          }
        }
      }
    }
  }
  return false;
}

char King::getName()
{
  if (getColour() == White)
  {
    return 'k';
  }
  return 'K';
}

//QUEEN FUNCTIONS
Queen::Queen(Colour colour) : ChessPiece(colour, 'Q'){}

bool Queen::isValidMove(int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8])
{
  int start_row, start_column;
  int move_hor = d_column - s_column;
  int move_vert = d_row - s_row;
  int gradient;
  d_column > s_column ? start_column = s_column : start_column = d_column;
  d_row > s_row ? start_row = s_row : start_row = d_row;

  if (abs(move_vert) == abs(move_hor)) //if a diagonal move
  {
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
    d_column > s_column ? start_column = s_column : start_column = d_column;
    d_row < s_row ? start_row = s_row : start_row = d_row;
    for (int i = 1; i < abs(move_hor); i++)
    {
      if (cb[start_row - i][start_column + i] != nullptr)
      {
        return false;
      }
    }
    return true;
  }

  if (s_row == d_row) //move along a row
  {
    for (int i = 1; i < abs(move_hor); i++) //check if any piece in the way
    {
      if (cb[s_row][start_column+i] != nullptr)
      {
        return false;
      }
    }
    return true;
  }

  if (s_column == d_column) //move along a column
  {
    for (int i = 1; i < abs(move_vert); i++) //check if any piece in the way
    {
      if (cb[start_row + i][s_column] != nullptr)
      {
        return false;
      }
    }
    return true;
  }
  return false;
}

char Queen::getName()
{
  if (getColour() == White)
  {
    return 'q';
  }
  return 'Q';
}
