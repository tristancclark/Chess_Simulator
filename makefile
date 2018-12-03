OBJ = ChessPiece.o	ChessBoard.o	main.o
EXE = main
CXX = g++
CXXFLAGS = -Wall	-g	-MMD

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

-include $(OBJ:.o=.d)

clean:
	rm -f *.o main *.d *.h.gch
