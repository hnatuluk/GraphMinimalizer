all :
	cat usage
build : main.o FileWriter.o ConsoleWriter.o File.o FiniteStateLoader.o GraphMinimalizer.o InputLoader.o InputStateTable.o StateLoader.o
	g++ -pedantic -pedantic-errors -Wall -Werror main.o FileWriter.o ConsoleWriter.o File.o FiniteStateLoader.o GraphMinimalizer.o InputLoader.o InputStateTable.o StateLoader.o -o program
clean : 
	rm main.o FileWriter.o ConsoleWriter.o File.o FiniteStateLoader.o GraphMinimalizer.o InputLoader.o InputStateTable.o StateLoader.o
test1 : program inputs/inputOne
	cat inputs/inputOne
	./program inputs/inputOne
test11 : program inputs/inputOne
	cat inputs/inputOne
	./program inputs/inputOne outputs/outputOne
	cat outputs/outputOne
test2 : program inputs/inputDouble
	cat inputs/inputDouble
	./program inputs/inputDouble
test21 : program inputs/inputDouble
	cat inputs/inputDouble
	./program inputs/inputDouble outputs/outputDouble
	cat outputs/outputDouble
test3: program inputs/inputNone
	cat inputs/inputNone
	./program inputs/inputNone
test31 : program inputs/inputNone
	cat inputs/inputNone
	./program inputs/inputNone outputs/outputNone
	cat outputs/outputNone
test4: program
	./program inputs/neex
test5: program inputs/test5
	./program inputs/test5
test6: program inputs/test6
	./program inputs/test6
test7: program inputs/test7
	./program inputs/test7
test8: program inputs/test8
	./program inputs/test8
main.o : main.cpp File.h GraphMinimalizer.h ConsoleWriter.h FileWriter.h
	g++ -pedantic -pedantic-errors -Wall -Werror -c main.cpp	
FileWriter.o : FileWriter.cpp FileWriter.h File.h ConsoleWriter.h
	g++ -pedantic -pedantic-errors -Wall -Werror -c FileWriter.cpp
ConsoleWriter.o : ConsoleWriter.cpp ConsoleWriter.h OutputWriter.h
	g++ -pedantic -pedantic-errors -Wall -Werror -c ConsoleWriter.cpp
File.o : File.cpp File.h Exception.h
	g++ -pedantic -pedantic-errors -Wall -Werror -c File.cpp
FiniteStateLoader.o : FiniteStateLoader.h FiniteStateLoader.cpp File.h GraphLoader.h GraphChecker.h GraphSolver.h
	g++ -pedantic -pedantic-errors -Wall -Werror -c FiniteStateLoader.cpp
GraphMinimalizer.o : GraphMinimalizer.cpp GraphMinimalizer.h File.h GraphLoader.h Exception.h GraphChecker.h GraphSolver.h OutputWriter.h StateLoader.h InputLoader.h FiniteStateLoader.h InputStateTable.h
	g++ -pedantic -pedantic-errors -Wall -Werror -c GraphMinimalizer.cpp
InputLoader.o : InputLoader.cpp InputLoader.h File.h GraphLoader.h GraphChecker.h GraphSolver.h
	g++ -pedantic -pedantic-errors -Wall -Werror -c InputLoader.cpp
InputStateTable.o : InputStateTable.cpp InputStateTable.h GraphLoader.h GraphChecker.h GraphSolver.h StateLoader.h
	g++ -pedantic -pedantic-errors -Wall -Werror -c InputStateTable.cpp
StateLoader.o : StateLoader.cpp StateLoader.h GraphLoader.h File.h GraphChecker.h GraphSolver.h
	g++ -pedantic -pedantic-errors -Wall -Werror -c StateLoader.cpp
