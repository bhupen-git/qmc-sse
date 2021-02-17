#include<iostream>
#include<ctime>
#include<cstdlib>
#include<chrono>
#include "simulation.h"
#include "observables.h"

using namespace std;
using namespace std::chrono;

int main(){
	int mcequi=10000; //set monte carlo sweeps//
	int mcs=10000;
	int nbins=20;
	srand(time(0));
	Simulation sim1;
	Observables ob1;

	sim1.initparameters(16,1,256.0,nbins,mcs); //(Lx,Ly,beta,nbins,mcsperbin)//
	sim1.make_1Dlattice();
	sim1.initspinstate();
	ob1.init_energy(sim1);

	auto start = high_resolution_clock :: now();

	for(int i=0; i<mcequi; i++){
		sim1.diagonalupdate();
		sim1.make_vertexlist();
		sim1.make_loops();
		sim1.find_truncation();
	};

	for(int bin=0; bin<nbins; bin++){
		for(int i=0; i<mcs; i++){
			sim1.diagonalupdate();
			sim1.make_vertexlist();
			sim1.make_loops();
			ob1.updt_Ebinavg(sim1);
		}
		ob1.collect_Ebinavg(sim1);
	}

	auto stop = high_resolution_clock :: now();
	auto duration = duration_cast<seconds>(stop-start);
	cout << duration.count() << "\n";
	ob1.get_truncation(sim1);
	ob1.get_systemsize(sim1);
	cout << ob1.get_energy(sim1) << "\n";
	cout << ob1.get_energy_error(sim1) << "\n";

	return 0;
}

