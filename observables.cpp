#include<iostream>
#include "observables.h"

using namespace std;

void Observables :: get_spinstate(Simulation obj){
	for(int i=0; i<obj.N; i++){cout << obj.spin[i] << " ";}
	cout << "\n";
}

void Observables :: get_systemsize(Simulation obj){cout << obj.Lx << " x " << obj.Ly << "\n";}

void Observables :: get_truncation(Simulation obj){cout << obj.L << "\n";}

void Observables :: get_diagcount(Simulation obj){cout << obj.n_op << "\n";}

void Observables :: get_temperature(Simulation obj){cout << 1.0/obj.beta << "\n";}
