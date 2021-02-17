#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include "simulation.h"

using namespace std;

void Simulation :: initparameters(int lx, int ly, float invt, int nofbins, int mcsperbin){
	Lx=lx;
	Ly=ly;
	N=Lx*Ly;
	beta=invt;
	n_op=0;
	L=N/2;
	nbins=nofbins;
	mcs=mcsperbin;
	opstring.reserve(L);
	for(int p=0; p<L; p++){opstring.push_back(Operator());}
	spin = new int[N];
	vfirst = new int[N];
	vlast = new int[N];
	
	if(ly == 1){Nb=N;}
	else{Nb=2*N;}

	bondlist = new bond[Nb];
	probfactor=0.5*beta*Nb;

	for(int i=0; i<N; i++){vfirst[i]=-1; vlast[i]=-1;}
}

void Simulation :: make_lattice(){
	int index;
	for(int y=0; y<Ly; y++){
		for(int x=0; x<Lx; x++){
			index = x + y*Lx;
			bondlist[index].i=index;
			bondlist[index].j=(x+1)%Lx + y*Lx;
			bondlist[index+N].i=index;
			bondlist[index+N].j=x + ((y+1)%Ly)*Lx;
		}
	}
}

void Simulation :: make_1Dlattice(){
	int index;
	for(int x=0; x<Lx; x++){
		index=x;
		bondlist[index].i=index;
		bondlist[index].j=(x+1)%Lx;
	}
}

void Simulation :: initspinstate(){for(int i=0; i<N; i++){spin[i]=(2*((int)rand()%2)-1);}}

void Simulation :: diagonalupdate(){
	int b;
	for(int p=0; p<L; p++){
		if(opstring[p].type == -1){
			b=rand()%Nb;
			if(spin[bondlist[b].i]==spin[bondlist[b].j]){continue;}
			if(((float) rand()/RAND_MAX)*(L-n_op) <= probfactor){opstring[p].type=0; opstring[p].location=b; n_op++;}
		}
		else if(opstring[p].type == 0){
			if(((float) rand()/RAND_MAX)*probfactor <= L-n_op+1){opstring[p].type = -1; n_op--; opstring[p].resetvertex();}
		}
		else{b=opstring[p].location; spin[bondlist[b].i]=-spin[bondlist[b].i]; spin[bondlist[b].j]=-spin[bondlist[b].j];}
	}
}

void Simulation :: make_vertexlist(){
	int v0, b, i1, i2, v1, v2, f, l;
	for(int i=0; i<N; i++){vfirst[i]=-1; vlast[i]=-1;}
	for(int p=0; p < L; p++){
		if(opstring[p].type == -1){continue;}
		v0=4*p;
		b=opstring[p].location;
		i1=bondlist[b].i; i2=bondlist[b].j; v1=vlast[i1]; v2=vlast[i2];
		if(v1 != -1){opstring[v1/4].ver[v1%4] = v0; opstring[p].ver[v0%4] = v1;}else{vfirst[i1]=v0;}
		if(v2 != -1){opstring[v2/4].ver[v2%4] = v0+1; opstring[p].ver[(v0+1)%4] = v2;}else{vfirst[i2]=v0+1;}
		vlast[i1]=v0+2; vlast[i2]=v0+3;
	}

	for(int i=0; i<N; i++){
		f=vfirst[i];
		if(f != -1){
			l=vlast[i];
			opstring[f/4].ver[f%4] = l; opstring[l/4].ver[l%4] = f;
		}
	}
}

void Simulation :: set_loop(int a, int b){
	int v1=a, v2;
	do{
		if(b == -2){opstring[v1/4].type = (opstring[v1/4].type ^ 1);}
		opstring[v1/4].ver[v1%4]=b;
		v2=(v1^1);
		v1=opstring[v2/4].ver[v2%4];
		opstring[v2/4].ver[v2%4]=b;
	}while(v1 != a);
}


void Simulation :: make_loops(){
	int v;
	for(int v0=0; v0 < 4*L; v0+=2){
		if(opstring[v0/4].ver[v0%4] < 0){continue;}
		v = v0;
		if((float) rand()/RAND_MAX < 0.5){set_loop(v,-1);}
		else{set_loop(v,-2);}
	}
	for(int i=0; i<N; i++){
		v=vfirst[i];
		if(v == -1){
			if((float) rand()/RAND_MAX < 0.5){spin[i] = -spin[i];}
		}
		else if(opstring[v/4].ver[v%4] == -2){spin[i] = -spin[i];}
	}
}

void Simulation :: find_truncation(){
	int Lnew;
	Lnew=(1+a)*n_op;
	if(Lnew < L){return;}
	opstring.resize(Lnew,Operator());
	L=Lnew;
}


