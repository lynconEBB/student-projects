all:
	flex -o scanner.cpp scanner.l
	bison -d --defines=parser.h -o parser.cpp parser.y
	g++ -g main.cpp scanner.cpp parser.cpp driver.cpp tree.cpp symTable.cpp -o main
clean:
	rm -rf scanner.cpp
	rm -rf parser.cpp parser.h 
	rm -rf main