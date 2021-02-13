#ifndef OPERATOR_H
#define OPERATOR_H

class Operator{
	friend class Simulation;
	int type, location;
	int ver[4];

	public:
	Operator();
	void resetvertex();
};

#endif
