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

  //  cb.submitMove("A1", "A3");

return 0;
}
