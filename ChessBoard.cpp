#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include "ChessPiece.h"
#include "ChessBoard.h"
using namespace std;

//CHESSBOARD CLASS FUNCTIONS

ChessBoard::ChessBoard()
{
  setBoard();
}

ChessBoard::~ChessBoard()
{
  clearBoard();
}

void ChessBoard::resetBoard()
{
  clearBoard();
  setBoard();
}

void ChessBoard::clearBoard()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      delete cb[i][j];
      cb[i][j] = nullptr;
    }
  }
}

void ChessBoard::setBoard()
{
  cout << "A new chess game is started!" << endl;
  current_turn = White;
  Colour colours[2] = {Black, White};

  for (int i = 2; i < 6; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      cb[i][j] = nullptr; //set empty squares to nullptrs
    }
  }

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      cb[5*j+1][i] = new Pawn(colours[j]); //create pawns
    }
  }

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      cb[7*j][7*i] = new Castle(colours[j]); //create castles
      cb[7*j][5*i+1] = new Knight(colours[j]); //create knights
      cb[7*j][3*i+2] = new Bishop(colours[j]); //create bishops
    }
  }

  for (int i = 0; i < 2; i++)
  {
    cb[7*i][3] = new Queen(colours[i]); //create queens
    cb[7*i][4] = new King(colours[i]); //create kings
  }
}

void ChessBoard::submitMove(const char *s_square, const char *d_square)
{

  //check inputs first

  if (strlen(s_square) != 2)
  {
    cout << "That is an invalid source square. Please enter two characters." << endl;
    cout << "File (A-H) followed by Rank (1-8)." << endl;
    return;
  }

  if (strlen(d_square) != 2)
  {
    cout << "That is an invalid source square. Please enter two characters." << endl;
    cout << "File (A-H) followed by Rank (1-8)." << endl;
    return;
  }

  if (s_square[0] < 'A' || s_square[0] > 'H' || s_square[1] < '1' || s_square[1] > '8')
  {
    cout << "That is an out of range source square. Please enter two characters." << endl;
    cout << "File (A-H) followed by Rank (1-8)." << endl;
    return;
  }

  if (d_square[0] < 'A' || d_square[0] > 'H' || d_square[1] < '1' || d_square[1] > '8')
  {
    cout << "That is an out of range destination square. Please enter two characters." << endl;
    cout << "File (A-H) followed by Rank (1-8)." << endl;
    return;
  }

  //begin functionality
  int ascii_letter_shift = 'A';
  int ascii_number_shift = '0' + 8;
  Position s, d, k; //source, desination, king
  s.row = abs(static_cast<int>(s_square[1]) - ascii_number_shift);
  s.column = static_cast<int>(s_square[0]) - ascii_letter_shift;
  d.row = abs(static_cast<int>(d_square[1]) - ascii_number_shift);
  d.column = static_cast<int>(d_square[0]) - ascii_letter_shift;
  ChessPiece *&s_piece = cb[s.row][s.column];
  ChessPiece *&d_piece = cb[d.row][d.column];
  ChessPiece *imitation_board[8][8];

  if (s_square == d_square) //check if stay same square
  {
    cout << "The destination square is the same as the source square. Please make another move." << endl;
    return;
  }

  if (s_piece == nullptr) //does piece not exist in source
  {
    cout << "There is no piece at position " << s_square << "!" << endl;
    return;
  }

  if (s_piece->getColour() != current_turn) //is it that piece's turn
  {
    cout << "It is not " << s_piece->getColour() << "'s turn to move!" << endl;
    return;
  }

  if (d_piece != nullptr) //avoid segfault
  {
    if (d_piece->getColour() == current_turn) //teams own piece lies in d_square
    {
      cout << "A " << current_turn << " piece lies in " << d_square << "! Please make another move." << endl;
      return;
    }
  }

  if (!s_piece->isValidMove(s, d, cb)) //check if valid move
  {
    cout << current_turn << "'s " << s_piece << " cannot move " << "from " << s_square << " to " << d_square << "!" << endl;
    return;
  }

  //imitate making move to see if causes check
  imitateMove(cb, imitation_board, s, d);

  if (isInCheck(current_turn, imitation_board)) //if move leaves own king in check
  {
    cout << "That move puts you in check! Please make another move." << endl;
    return;
  }

  makeMove(s, d);
  nextTurn(); //change turn

  if (isInCheckmate(current_turn)) //if move creates checkmate
  {
    cout << current_turn << " is in checkmate" << endl;
    return;
  }

  if (isInCheck(current_turn, cb)) //if move creates check on other team
  {
    cout << current_turn << " is in check" << endl;

    k = findKing(current_turn, cb);
    static_cast<King *>(cb[k.row][k.column])->setCheck(true); //set king to incheck
    return;
  }

  if (isInStalemate(current_turn)) //if move creates stalemate
  {
    cout << current_turn << " is in stalemate" << endl;
    return;
  }

  //if function made it this far then no check so set king to not in check
  k = findKing(current_turn, cb);
  static_cast<King *>(cb[k.row][k.column])->setCheck(false);
}


void ChessBoard::makeMove(Position s, Position d)
{
  ChessPiece *&s_piece = cb[s.row][s.column];
  ChessPiece *&d_piece = cb[d.row][d.column];

  cout << s_piece << " moves from " << s << " to " << d;

  if (d_piece != nullptr)
  {
    cout << " taking " << d_piece << endl;
  }
  else
  {
    cout << endl;
  }

  if (s_piece->getName() == "King") //check for castling
  {
    if (!(s_piece->hasBeenMoved())) //if kings already been moved
    {
      if ((d.column - s.column) == -2) //left castling
      {
        //swap the castle to left
        cb[s.row][s.column - 1] = cb[s.row][s.column - 4];
        cb[s.row][s.column - 4] = nullptr;
        cb[s.row][s.column - 1]->setBeenMoved();
        cout << "Left side castling has occurred. ";
        cout << cb[s.row][s.column - 1] << " jumps the King." << endl;
      }
      if ((d.column - s.column) == 2) //right castling
      {
        //swap the castle to right
        cb[s.row][s.column + 1] = cb[s.row][s.column + 3];
        cb[s.row][s.column + 3] = nullptr;
        cb[s.row][s.column + 1]->setBeenMoved();
        cout << "Right side castling has occurred. ";
        cout << cb[s.row][s.column + 1] << " jumps the King." << endl;
      }
    }
  }

  //make move:
  delete d_piece; //free taken piece on heap
  d_piece = s_piece; //move piece
  d_piece->setBeenMoved(); //set to been moved
  s_piece = nullptr; //clear source square
}


bool ChessBoard::isInCheck(Colour colour, ChessPiece *cb[8][8]) //check if colour team is in check
{
  Position s, d, k; //source, destination, king
  k = findKing(colour, cb);

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (cb[i][j] != nullptr) //if square contains piece
      {
        if (cb[i][j]->getColour() != colour) //if piece is on opposite team
        {
          s.row = i;
          s.column = j;
          d.row = k.row;
          d.column = k.column;
          if (cb[i][j]->isValidMove(s, d, cb)) //if taking king valid
          {
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool ChessBoard::isInStalemate(Colour colour)
{
  ChessPiece *temporary_board[8][8];
  Position s, d;

  for (int i = 0; i < 8; i++) //for all pieces on own team
  {
    for (int j = 0; j < 8; j++)
    {
      if (cb[i][j] != nullptr) //if square contains piece
      {
        if (cb[i][j]->getColour() == colour) //if piece is on own team
        {
          for (int x = 0; x < 8; x++) //for all of that pieces' valid moves
          {
            for (int y = 0; y < 8; y++)
            {
              if (cb[x][y] != nullptr) //if square contains piece
              {
                if (cb[x][y]->getColour() == colour) //if destination is own team
                {
                  continue; //skip to next iteration
                }
              }

              s.row = i;
              s.column = j;
              d.row = x;
              d.column = y;

              if (cb[i][j]->isValidMove(s, d, cb)) //if valid move
              {
                imitateMove(cb, temporary_board, s, d); //imitate making move

                if (!isInCheck(colour, temporary_board)) //check if this releases check
                {
                  return false;
                }
              }
            }
          }
        }
      }
    }
  }
  return true; //if get to this point then in checkmate
}

bool ChessBoard::isInCheckmate(Colour colour)
{
  if (isInCheck(colour, cb) && isInStalemate(colour))
  {
    return true;
  }
  return false;
}


Position ChessBoard::findKing(Colour colour, ChessPiece *cb[8][8])
{
  Position k = {};

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (cb[i][j] != nullptr)
      {
        if (cb[i][j]->getName() == "King") //if piece is a king
        {
          if(cb[i][j]->getColour() == colour) //if piece is right colour
          {
            k.row = i;
            k.column = j;
            return k;
          }
        }
      }
    }
  }
  return k;
}

void ChessBoard::imitateMove(ChessPiece *cb[8][8], ChessPiece *ib[8][8], Position s, Position d)
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      ib[i][j] = cb[i][j]; //copy board
    }
  }
  ib[d.row][d.column] = ib[s.row][s.column]; //do move
  ib[s.row][s.column] = nullptr;
}
