OBJ = ChessPiece.o	ChessBoard.o	test4.o
EXE = main
CXX = g++
CXXFLAGS = -Wall	-g	-MMD	-std=c++11

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

-include $(OBJ:.o=.d)

clean:
	rm -f *.o main *.d *.h.gch
