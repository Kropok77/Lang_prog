program: compile link start
compile: main.cpp
	g++ lab1.cpp -c
link: main.o
	g++ lab1.o -o lab1
start:
	./lab1