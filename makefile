main: Main.o
	g++ -o main Main.o

Main.o: Main.cpp
	g++ -c Main.cpp

clean: 
	rm main Main.o