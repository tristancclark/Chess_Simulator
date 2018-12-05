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


  cb.displayBoard();
  cb.submitMove("C2", "C3");
  cb.displayBoard();
  cb.submitMove("D7", "D6");
  cb.displayBoard();
  cb.submitMove("D1", "A4");
  cb.displayBoard();
  cb.submitMove("D7", "D6");
  cb.displayBoard();
  cb.submitMove("D1", "A4");
  cb.displayBoard();
  cb.submitMove("E8", "G8");
/*
//check tests
cb.displayBoard();
cb.submitMove("C2", "C3");
cb.displayBoard();
cb.submitMove("D7", "D6");
cb.displayBoard();
cb.submitMove("D1", "A4");
cb.displayBoard();
cb.submitMove("E8", "D7");
cb.displayBoard();
cb.submitMove("C7", "C6");
cb.displayBoard();
cb.submitMove("A4", "C6");
cb.displayBoard();
cb.submitMove("B8", "C6");
cb.displayBoard();
*/

//cout << cb.isInCheck(Black);




/*
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
  //cb.submitMove("F8", "E3");
  //cb.displayBoard();
  cb.submitMove("E2", "E3");
  cb.displayBoard();
  cb.submitMove("F2", "E3");
  cb.displayBoard();
  //blacsk go
  cout << "Blacks go" << endl;
  cb.submitMove("H7", "H6");
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
  cb.submitMove("C7", "C6");
  cb.displayBoard();


  cout << "bishops test" << endl;

  cb.submitMove("C1", "E3");
  cb.displayBoard();
  cb.submitMove("F1", "H3");
  cb.displayBoard();
  cb.submitMove("F8", "F6");
  cb.displayBoard();
  cb.submitMove("C8", "A6");
  cb.displayBoard();
  cb.submitMove("H3", "D7");
  cb.displayBoard();
  cb.submitMove("A6", "B5");
  cb.displayBoard();
  cb.submitMove("A6", "B7");
  cb.displayBoard();

  cout << "knights test" << endl;

  cb.submitMove("B1", "C3");
  cb.displayBoard();
  cb.submitMove("B8", "C6");
  cb.displayBoard();
  cb.submitMove("B8", "A6");
  cb.displayBoard();
  cb.submitMove("C3", "E4");
  cb.displayBoard();
  cb.submitMove("A6", "B4");
  cb.displayBoard();
  cb.submitMove("E4", "G3");
  cb.displayBoard();
  cb.submitMove("E4", "C3");
  cb.displayBoard();

  cout << "kings test" << endl;

  cb.submitMove("D8", "B8");
  cb.displayBoard();
  cb.submitMove("H2", "H3");
  cb.displayBoard();
  cb.submitMove("E8", "D8");
  cb.displayBoard();
  cb.submitMove("E1", "F1");
  cb.displayBoard();
  cb.submitMove("D8", "C7");
  cb.displayBoard();
  cb.submitMove("F1", "E2");
  cb.displayBoard();
  cb.submitMove("F1", "G2");
  cb.displayBoard();
  cb.submitMove("C7", "D7");
  cb.displayBoard();

  cout << "queens test" << endl;

  cb.submitMove("D1", "D3");
  cb.displayBoard();
  cb.submitMove("D1", "A4");
  cb.displayBoard();
  cb.submitMove("B8", "E6");
  cb.displayBoard();
  cb.submitMove("B8", "E5");
  cb.displayBoard();
  cb.submitMove("A4", "E4");
  cb.displayBoard();
  cb.submitMove("A4", "B5");
  cb.displayBoard();
  cb.submitMove("E5", "D5");
  cb.displayBoard();
  cb.submitMove("B5", "E8");
  cb.displayBoard();
  */

return 0;
}
