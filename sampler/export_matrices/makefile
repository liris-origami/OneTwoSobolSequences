all: export_matrices

export_matrices: export_matrices.o sobol_fast.o
	g++ -o $@ $^ 

%.o: %.cpp
	g++ -Wall -o $@ -c $< 

clean:
	-rm export_matrices *.o
	
