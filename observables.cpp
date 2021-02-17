#include<iostream>
#include<vector>
#include<math.h>
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

void Observables :: init_energy(Simulation obj){
	E_binavg=0.0;
	Ebins.reserve(obj.nbins);
}

void Observables :: updt_Ebinavg(Simulation obj){E_binavg += obj.n_op;}

void Observables :: collect_Ebinavg(Simulation obj){
	E_binavg=E_binavg/((float) obj.mcs);
	E_binavg=E_binavg/(obj.beta*obj.N) - obj.Nb/((float) 4.0*obj.N);
	Ebins.push_back(E_binavg);
	E_binavg=0.0;
}


float Observables :: get_energy(Simulation obj){
	float sum=0.0;
	for(int bin=0; bin<obj.nbins; bin++){sum+=Ebins[bin];}
	E_avg=sum/obj.nbins;
	return sum/obj.nbins;
}

float Observables :: get_energy_error(Simulation obj){
	float error=0.0;
	for(int bin=0; bin<obj.nbins; bin++){error += powf((Ebins[bin] - E_avg),2.0);}
	error=error/(obj.nbins*(obj.nbins-1));
	return powf(error,0.5);
}
