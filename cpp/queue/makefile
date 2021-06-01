main: main.o queue.o
	g++ -std=c++20 main.o queue.o

main.o: main.cpp queue.cpp
	g++ -c -std=c++20 main.cpp queue.cpp

clean:
	del *.o meth

run:
	a.exe