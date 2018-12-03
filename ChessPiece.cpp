#include <iostream>
#include <cctype>
#include "ChessPiece.h"
using namespace std;

//CHESSPIECE FUNCTIONS
ChessPiece::ChessPiece(Colour col, char n) : colour(col)
{
  if (col == White)
    name = tolower(n);
  else
    name = n;
}

ChessPiece::~ChessPiece() {}

void ChessPiece::setColour(Colour col)
{
  colour = col;
}

//PAWN FUNCTIONS

Pawn::Pawn(Colour colour) : ChessPiece(colour, 'P'){}
Castle::Castle(Colour colour) : ChessPiece(colour, 'C'){}
Bishop::Bishop(Colour colour) : ChessPiece(colour, 'B'){}
Knight::Knight(Colour colour) : ChessPiece(colour, 'N'){}
King::King(Colour colour) : ChessPiece(colour, 'K'){}
Queen::Queen(Colour colour) : ChessPiece(colour, 'Q'){}
