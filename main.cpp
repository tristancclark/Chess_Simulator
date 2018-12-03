#include "ChessBoard.h"
#include "ChessPiece.h"
#include <iostream>

using namespace std;

int main() {

  cout << "===========================" << endl;
  cout << "Testing the Chess Engine" << endl;
  cout << "===========================" << endl;
  cout << endl;

  ChessBoard cb;
  cout << endl;

//pawn tests
  cb.displayBoard();
  cb.submitMove("A2", "A3");
  cb.displayBoard();
  cb.submitMove("B7", "B5");
  cb.displayBoard();
  cb.submitMove("G2", "H3");
  cb.displayBoard();
  cb.submitMove("G2", "G3");
  cb.displayBoard();
  cb.submitMove("F8", "E3");
  cb.displayBoard();
  cb.submitMove("E2", "E3");
  cb.displayBoard();
  cb.submitMove("F2", "E3");
  cb.displayBoard();
  //blacsk go
  cout << "Blacks go" << endl;
  cb.submitMove("D8", "B4");
  cb.displayBoard();
  cb.submitMove("A3", "B4");
  cb.displayBoard();
  cb.submitMove("E8", "D3");
  cb.displayBoard();
  cb.submitMove("E1", "G6");
  cb.displayBoard();
  cb.submitMove("H7", "G6");
  cb.displayBoard();
  cb.submitMove("C2", "C4");
  cb.displayBoard();

  //blacks go
  cout << "castles test" << endl;
  //castle tests
  cb.submitMove("A8", "A5");
  cb.displayBoard();
  cb.submitMove("H8", "H1");
  cb.displayBoard();
  cb.submitMove("H8", "H2");
  cb.displayBoard();
  cb.submitMove("A1", "A5");
  cb.displayBoard();
  cb.submitMove("H2", "E2");
  cb.displayBoard();
  cb.submitMove("A5", "E5");
  cb.displayBoard();
  cb.submitMove("A5", "F8");
  cb.displayBoard();


return 0;
}
