CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD
EXEC = sudoku
OBJECTS = board.o solution.o sudoku.o solutionTest.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
