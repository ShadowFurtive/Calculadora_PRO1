OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

test_calculadora.exe: test_calculadora.o calculadora.o expressio.o token.o
	g++ -o test_calculadora.exe test_calculadora.o calculadora.o expressio.o token.o

test_calculadora.o: test_calculadora.cpp calculadora.hpp calculadora.rep expressio.hpp expressio.rep arbreBin.hpp token.hpp token.rep
	g++ -c test_calculadora.cpp $(OPCIONS)

calculadora.o: calculadora.cpp calculadora.hpp calculadora.rep expressio.hpp expressio.rep arbreBin.hpp token.hpp token.rep
	g++ -c calculadora.cpp $(OPCIONS)

test_expressio.exe: test_expressio.o expressio.o token.o
	g++ -o test_expressio.exe test_expressio.o expressio.o token.o

test_expressio.o: test_expressio.cpp expressio.hpp expressio.rep arbreBin.hpp token.hpp token.rep
	g++ -c test_expressio.cpp $(OPCIONS)

expressio.o: expressio.cpp expressio.hpp expressio.rep arbreBin.hpp token.hpp token.rep
	g++ -c expressio.cpp $(OPCIONS)

test_token.exe: test_token.o token.o
	g++ -o test_token.exe test_token.o token.o

test_token.o: test_token.cpp token.hpp token.rep
	g++ -c test_token.cpp $(OPCIONS)

token.o: token.cpp token.hpp token.rep
	g++ -c token.cpp $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch

test_token:
	./test_token.exe < test_token.inp | diff - test_token.cor

test_expressio:
	./test_expressio.exe < test_expressio.inp | diff - test_expressio.cor

test_calculadora:
	./test_calculadora.exe < test_calculadora.inp | diff - test_calculadora.cor
