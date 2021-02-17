#ifndef SIMULATION_H
#define SIMULATION_H
#include<vector>
#include "operator.h"

using namespace std; 

class Simulation{
	friend class Observables;

	struct bond{int i; int j;};

	int Lx, Ly, n_op, L, N, Nb, nbins, mcs;
	float beta, probfactor;
	const float a=1.0/3.0;
	int *spin,*vfirst,*vlast;
	bond *bondlist;
	vector<Operator> opstring;

	public:
	void initparameters(int, int, float, int, int);
	void make_lattice();
	void make_1Dlattice();
	void initspinstate();
	void diagonalupdate();
	void make_vertexlist();
	void set_loop(int,int);
	void make_loops();
	void find_truncation();
};

#endif
