#include <iostream>
#include <cctype>
#include <cstdlib>
#include "ChessPiece.h"
#include "ChessBoard.h"
using namespace std;
//CHESSBOARD CLASS

//Constructor

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
      delete current_board[i][j];
      current_board[i][j] = nullptr;
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
      current_board[i][j] = nullptr; //set empty squares to nullptrs
    }
  }

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      current_board[5*j+1][i] = new Pawn(colours[j]); //assign pawns
    }
  }

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      current_board[7*j][7*i] = new Castle(colours[j]); //assign castles
      current_board[7*j][5*i+1] = new Knight(colours[j]); //assign knights
      current_board[7*j][3*i+2] = new Bishop(colours[j]); //assign bishops
    }
  }

  for (int i = 0; i < 2; i++)
  {
    current_board[7*i][3] = new Queen(colours[i]); //assign queen
    current_board[7*i][4] = new King(colours[i]); //assign king
  }
}

void ChessBoard::submitMove(const char* s_square, const char* d_square)
{
  int ascii_letter_shift = 'A';
  int ascii_number_shift = '0' + 8;
  int s_row = abs(static_cast<int>(s_square[1]) - ascii_number_shift);
  int s_column = static_cast<int>(s_square[0]) - ascii_letter_shift;
  int d_row = abs(static_cast<int>(d_square[1]) - ascii_number_shift);
  int d_column = static_cast<int>(d_square[0]) - ascii_letter_shift;
  ChessPiece *&s_piece = current_board[s_row][s_column];
  ChessPiece *&d_piece = current_board[d_row][d_column];
  ChessPiece* temporary_board[8][8];
  int k_row, k_column;
  char k_name = 'K';

  if (s_square == d_square)
  {
    cout << "The destination square is the same as the source square. Please make another move." << endl;
    return;
  }

  if (s_piece == nullptr) //does piece exist in source
  {
    cout << "There is no piece at position " << s_square << "!" << endl;
    return;
  }

  if (s_piece->getColour() != current_turn) //is it that teams turn
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

  if (!s_piece->isValidMove(s_row, s_column, d_row, d_column, current_board))
  {
    cout << current_turn << "'s " << s_piece->getName() << " cannot move " << "from " << s_square << " to " << d_square << "!" << endl;
    //displayBoard();
    return;
  }

  //imitate making move to check for check
  imitateMove(current_board, temporary_board, s_row, s_column, d_row, d_column);

  if (isInCheck(current_turn, temporary_board)) //check if move leaves own king in check
  {
    cout << "That move puts you in check! Please make another move." << endl;
    return;
  }

  makeMove(s_square, d_square, s_row, s_column, d_row, d_column, current_board); //make move
  //displayBoard();
  nextTurn(); //change turn

  if (isInCheck(current_turn, current_board)) //check if move creates check
  {
    if (isInCheckmate(current_turn, current_board)) //and stalemate
    {
      cout << current_turn << " is in checkmate." << endl;
      return;
    }
    cout << current_turn << " is in check." << endl;
    findPiece(k_name, current_turn, k_row, k_column, current_board);
    static_cast<King *>(current_board[k_row][k_column])->setCheck(true);
    //displayBoard();
    return;
  }

  if (isInStalemate(current_turn, current_board))
  {
    cout << current_turn << " is in stalemate." << endl;
    return;
  }
  findPiece(k_name, current_turn, k_row, k_column, current_board);
  static_cast<King *>(current_board[k_row][k_column])->setCheck(false);
}

void ChessBoard::imitateMove(ChessPiece *cb[8][8], ChessPiece *imitation_board[8][8], int s_row, int s_column, int d_row, int d_column)
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      imitation_board[i][j] = cb[i][j];
    }
  }
  imitation_board[d_row][d_column] = imitation_board[s_row][s_column];
  imitation_board[s_row][s_column] = nullptr;
}


void ChessBoard::makeMove(const char *s_square, const char *d_square, int s_row, int s_column, int d_row, int d_column, ChessPiece *cb[8][8])
{
  ChessPiece *&s_piece = cb[s_row][s_column];
  ChessPiece *&d_piece = cb[d_row][d_column];

  cout << current_turn << "'s " << s_piece->getName() << " moves from ";
  cout << s_square << " to " << d_square;

  if (d_piece != nullptr)
  {
    cout << " taking " << d_piece->getColour() << "'s " << d_piece->getName() << endl;
  }
  else
  {
    cout << endl;
  }
  if (s_piece->getName() == 'k' || s_piece->getName() == 'K')
  {
    if (!(s_piece->hasBeenMoved()))
    {
      if ((d_column - s_column) == -2)
      {
        //swap the castle
        cb[s_row][s_column - 1] = cb[s_row][s_column - 4];
        cb[s_row][s_column - 4] = nullptr;
        cb[s_row][s_column - 1]->setBeenMoved();
        cout << "Left side castling has occurred. " << current_turn << "'s ";
        cout << cb[s_row][s_column - 1]->getName() << " jumps the King." << endl;
      }
      if ((d_column - s_column) == 2)
      {
        //swap the castle
        cb[s_row][s_column + 1] = cb[s_row][s_column + 3];
        cb[s_row][s_column + 3] = nullptr;
        cb[s_row][s_column + 1]->setBeenMoved();
        cout << "Right side castling has occurred. " << current_turn << "'s ";
        cout << cb[s_row][s_column + 1]->getName() << " jumps the King." << endl;
      }
    }
  }
  delete d_piece;
  d_piece = s_piece;
  d_piece->setBeenMoved();
  s_piece = nullptr;
}

void ChessBoard::findPiece(char name, Colour colour, int &row, int &column, ChessPiece* cb[8][8])
{
  if (colour == White)
  {
    name = tolower(name);
  }
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (cb[i][j] != nullptr)
      {
        if (cb[i][j]->getName() == name)
        {
          row = i;
          column = j;
          return;
        }
      }
    }
  }
}


bool ChessBoard::isInCheckmate(Colour colour, ChessPiece *cb[8][8]) //check if colour team is in check
{
  ChessPiece *temporary_board[8][8];

  for (int i = 0; i < 8; i++) //for all piece on own team
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
              if (cb[x][y] != nullptr) //avoid seg fault
              {
                if (cb[x][y]->getColour() == colour) //if destination is own team
                {
                  continue;
                }
              }
              if (cb[i][j]->isValidMove(i, j, x, y, cb)) //if valid move
              {
                imitateMove(cb, temporary_board, i, j, x, y); //imitate making move

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
  return true;
}

bool ChessBoard::isInStalemate(Colour colour, ChessPiece *cb[8][8]) //check if colour team is in check
{
  ChessPiece *temporary_board[8][8];

  for (int i = 0; i < 8; i++) //for all piece on own team
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
              if (cb[x][y] != nullptr) //avoid seg fault
              {
                if (cb[x][y]->getColour() == colour) //if destination is own team
                {
                  continue;
                }
              }
              if (cb[i][j]->isValidMove(i, j, x, y, cb)) //if valid move
              {
                imitateMove(cb, temporary_board, i, j, x, y); //imitate making move

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
  return true;
}

bool ChessBoard::isInCheck(Colour colour, ChessPiece *cb[8][8]) //check if colour team is in check
{
  int row, column;
  char name = 'K';
  findPiece(name, colour, row, column, cb);

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (cb[i][j] != nullptr) //if square contains piece
      {
        if (cb[i][j]->getColour() != colour) //if piece is on opposite team
        {
          if (cb[i][j]->isValidMove(i, j, row, column, cb)) //if taking king valid
          {
            return true;
          }
        }
      }
    }
  }
  return false;
}


void ChessBoard::displayBoard()
{
  cout << endl;
  cout << "    ";
  //A to H
  for (int r=0; r<8; r++)
    cout << (char) ('A' + r) << "   ";
  cout << endl;
  //row by row
  for (int r=0; r<8; r++) {
    cout << "  ---------------------------------" << endl;
    cout << (char) ('8' - r) << " ";
    for (int i=0; i<8; i++) {
      cout << "|" << " ";
      if (current_board[r][i] == nullptr)
        cout << ' ' << ' ';
      else
        cout << current_board[r][i]->getName() << " ";
    }
    cout << "|" << endl;
  }
  cout << "  ---------------------------------" << endl;
  cout << endl << endl;
}
