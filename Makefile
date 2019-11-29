OBJECTS = treeprint.o lexer.o symbol.o interpreter.o init.o error.o main.o parser.tab.o codeoptimizer.o codegenerator.o
SOURCES = treeprint.cpp lexer.cpp symbol.cpp init.cpp error.cpp main.cpp codegenerator.cpp codeoptimizer.cpp example.y
EXE = jasminCompiler
CFLAGS += -Wall -g

$(EXE):	$(OBJECTS)
	g++ $(CFLAGS) -o $(EXE) $(OBJECTS)

main.o: 	main.cpp global.hpp
	g++ $(CFLAGS) -c main.cpp

lexer.o: 	lexer.cpp global.hpp
	g++ $(CFLAGS) -c lexer.cpp

symbol.o: 	symbol.cpp global.hpp
	g++ $(CFLAGS) -c symbol.cpp

init.o: 	init.cpp global.hpp
	g++ $(CFLAGS) -c init.cpp

error.o: 	error.cpp global.hpp
	g++ $(CFLAGS) -c error.cpp

treeprint.o:	treeprint.cpp global.hpp 
	g++ $(CFLAGS) -c treeprint.cpp

parser.tab.o:	parser.tab.cpp parser.tab.hpp global.hpp
	g++ $(CFLAGS) -c parser.tab.cpp

codegenerator.o:	codegenerator.cpp global.hpp symbol.cpp
	g++ $(CFLAGS) -c codegenerator.cpp

codeoptimizer.o:	codeoptimizer.cpp global.hpp
	g++ $(CFLAGS) -c codeoptimizer.cpp

interpreter.o:	interpreter.cpp global.hpp symbol.cpp
	g++ $(CFLAGS) -c interpreter.cpp 

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d parser.ypp

global.hpp: parser.tab.hpp

clean: 
	rm -f $(EXE) $(OBJECTS) 29.tar.gz 29.zip *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
