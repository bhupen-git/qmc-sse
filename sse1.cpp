#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>

using namespace std;

class Operator{
	public:
	int type, location;
	int ver[4];
	Operator(){type=-1;for(int i=0; i<4; i++){ver[i]=-1;}}
	void resetvertex(){for(int i=0; i<4; i++){ver[i]=-1;}}
};

const int Lx=16;
const int Ly=16;
const int N=Lx*Ly;
const int Nb=2*N;
float beta=16;
int vfirst[N];
int vlast[N];
int n_op=0;
int L=N/2;
int spin[N];
int bond[2][Nb];
const float probfactor=0.5*beta*Nb;
const float a=1.0/3.0;
vector<Operator> opstring;

void lattice(){
	int index;
	for(int y=0; y<Ly; y++){
		for(int x=0; x<Lx; x++){
			index = x + y*Lx;
			bond[0][index]=index;
			bond[1][index]=(x+1)%Lx + y*Lx;
			bond[0][index+N]=index;
			bond[1][index+N]=x + ((y+1)%Ly)*Lx;
		}
	}
}

void initspinstate(){for(int i=0; i<N; i++){spin[i] = 2*((int)rand()%2)-1;}}

void diagonalupdate(){
	int b;
	for(int p=0; p<L; p++){
		if(opstring[p].type == -1){
			b=rand()%Nb;
			if(spin[bond[0][b]]==spin[bond[1][b]]){continue;}
			if(((float) rand()/RAND_MAX)*(L-n_op) <= probfactor){opstring[p].type=0; opstring[p].location=b; n_op++;}
		}
		else if(opstring[p].type == 0){
			if(((float) rand()/RAND_MAX)*probfactor <= L-n_op+1){opstring[p].type = -1; n_op--; opstring[p].resetvertex();}
		}
		else{b=opstring[p].location; spin[bond[0][b]]=-spin[bond[0][b]]; spin[bond[1][b]]=-spin[bond[1][b]];}
	}
}

void make_vertexlist(){
	int v0, b, i1, i2, v1, v2, f, l;
	for(int i=0; i<N; i++){vfirst[i]=-1; vlast[i]=-1;}
	for(int p=0; p < L; p++){
		if(opstring[p].type == -1){continue;}
		v0=4*p;
		b=opstring[p].location;
		i1=bond[0][b]; i2=bond[1][b]; v1=vlast[i1]; v2=vlast[i2];
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

void set_loop(int,int);

void make_loops(){
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

void set_loop(int a, int b){
	int v1=a, v2;
	do{
		if(b == -2){opstring[v1/4].type = (opstring[v1/4].type ^ 1);}
		opstring[v1/4].ver[v1%4]=b;
		v2=(v1^1);
		v1=opstring[v2/4].ver[v2%4];
		opstring[v2/4].ver[v2%4]=b;
	}while(v1 != a);
}

void find_truncation(){
	int Lnew;
	Lnew=(1+a)*n_op;
	if(Lnew < L){return;}
	opstring.resize(Lnew,Operator());
	L=Lnew;
}

int main(){
	int mcsweep=5000;

	srand(time(0));
	opstring.reserve(L);
	for(int p=0; p<L; p++){opstring.push_back(Operator());}
	initspinstate();
	lattice();

	for(int i=0; i<mcsweep; i++){
		diagonalupdate();
		make_vertexlist();
		make_loops();
		find_truncation();
	}
	cout << L;

	return 0;
}


