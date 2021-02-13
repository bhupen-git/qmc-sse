#ifndef OBSERVABLES_H
#define OBSERVABLES_H
#include "simulation.h"

class Observables{
	public:
		void get_spinstate(Simulation);
		void get_systemsize(Simulation);
		void get_truncation(Simulation);
		void get_diagcount(Simulation);
		void get_temperature(Simulation);
};

#endif
