compile:
	g++ assignment02.cpp -o assignment02.o -Wall -pthread -std=c++11 `pkg-config --cflags --libs opencv`
execute:
	./assignment02.o
	
