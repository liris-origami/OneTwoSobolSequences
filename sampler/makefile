
all: main

main: main.o onetwo_matrices.o
	g++ -o $@ $^ --std=c++11

%.o: %.cpp
	g++ -Wall -o $@ -c $< --std=c++11

clean:
	-rm main *.o
