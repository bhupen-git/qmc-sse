#ifndef OBSERVABLES_H
#define OBSERVABLES_H
#include<vector>
#include "simulation.h"

class Observables{
	float E_binavg, E_avg;
	vector<float> Ebins;
	public:
		void get_spinstate(Simulation);
		void get_systemsize(Simulation);
		void get_truncation(Simulation);
		void get_diagcount(Simulation);
		void get_temperature(Simulation);
		void init_energy(Simulation);
		void updt_Ebinavg(Simulation);
		void collect_Ebinavg(Simulation);
		float get_energy(Simulation);
		float get_energy_error(Simulation);
};

#endif
