CC = g++

main: main.o observables.o operator.o simulation.o
	$(CC) -o main main.o observables.o operator.o simulation.o

main.o: main.cpp observables.h simulation.h
	$(CC) -c main.cpp

observables.o: observables.h
operator.o: operator.h
simulation.o: simulation.h observables.h operator.h

clean:
	rm -r *.o main
