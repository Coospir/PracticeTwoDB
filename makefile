all: football_db

football_db: main.o date.o file_work.o
		g++ main.o date.o file_work.o -o football_db

main.o: main.cpp
		g++ -c main.cpp

date.o: date.cpp
		g++ -c date.cpp

file_work.o: file_work.cpp
		g++ -c file_work.cpp


