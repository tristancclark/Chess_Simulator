OBJ = ChessPiece.o	ChessBoard.o	ChessMain.o
EXE = chess
CXX = g++
CXXFLAGS = -Wall	-g	-MMD	-std=c++11

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

-include $(OBJ:.o=.d)

clean:
	rm -f *.o chess *.d *.h.gch
