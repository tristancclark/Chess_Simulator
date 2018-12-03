#include <iostream>
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

void ChessBoard::submitMove(const char* source_square, const char* destination_square)
{
  int ascii_letter_shift = 'A';
  int ascii_number_shift = '0' + 8;
  int s_row = abs(static_cast<int>(source_square[1]) - ascii_number_shift);
  int s_column = static_cast<int>(source_square[0]) - ascii_letter_shift;
  int d_row = abs(static_cast<int>(destination_square[1]) - ascii_number_shift);
  int d_column = static_cast<int>(destination_square[0]) - ascii_letter_shift;
  ChessPiece *&s_piece = current_board[s_row][s_column];
  ChessPiece *&d_piece = current_board[d_row][d_column];

  if (source_square == destination_square)
  {
    cerr << "The destination square is the same as the source square. Please make another move." << endl;
    return;
  }

  if (s_piece == nullptr) //does piece exist in source
  {
    cerr << "There is no piece to move in that square. Please make another move." << endl;
    return;
  }

  if (s_piece->getColour() != current_turn) //is it that teams turn
  {
    cerr << "It is not " << s_piece->getColour() << "'s turn. " << current_turn << " please make a move." << endl;
    return;
  }

  if (d_piece != nullptr) //avoid segfault
  {
    if (d_piece->getColour() == current_turn) //teams own piece lies in d_square
    {
      cerr << "A " << current_turn << " piece lies in the destination square. Please make another move." << endl;
      return;
    }
  }

  if (!s_piece->isValidMove(s_row, s_column, d_row, d_column, current_board))
  {
    cerr << "That is not a valid move. Please make another move." << endl;
    return;
  }

  //make move
  makeMove(s_piece, d_piece);
  //change turn
  nextTurn();
}

void ChessBoard::makeMove(ChessPiece *&s_piece, ChessPiece *&d_piece)
{
  delete d_piece;
  d_piece = s_piece;
  s_piece = nullptr;
}

void ChessBoard::displayBoard()
{
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
