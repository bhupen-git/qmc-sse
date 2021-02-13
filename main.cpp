#include<iostream>
#include<ctime>
#include<cstdlib>
#include<chrono>
#include "simulation.h"
#include "observables.h"

using namespace std;
using namespace std::chrono;

int main(){
	int mcs=10000; //set monte carlo sweeps//
	srand(time(0));
	Simulation sim1;
	Observables ob1;

	sim1.initparameters(16,16,16.0); //(Lx,Ly,beta)//
	sim1.make_lattice();
	sim1.initspinstate();

	auto start = high_resolution_clock :: now();

	for(int i=0; i<mcs; i++){
		sim1.diagonalupdate();
		sim1.make_vertexlist();
		sim1.make_loops();
		sim1.find_truncation();
	};

	auto stop = high_resolution_clock :: now();
	auto duration = duration_cast<seconds>(stop-start);
	cout << duration.count() << "\n";

	ob1.get_truncation(sim1);
	ob1.get_systemsize(sim1);

	return 0;
}

