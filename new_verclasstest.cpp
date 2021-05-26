#include<iostream>
#include<vector>
#include<stack>

using namespace std;

struct leg{
	leg *ptr_to_leg=NULL;
	bool set_visit=false;
	int leg_index, loc_in_opstring;
};

class Vertex{
	public:
		vector<leg> leg_array;
		int vertex_type, loc_in_lattice;

		Vertex(int no_of_legs, int location_lattice, int location_opstring, int v_type){
			for(int i=0; i<no_of_legs; i++){
				leg_array.push_back(leg());
				leg_array[i].leg_index=i;
				leg_array[i].loc_in_opstring=location_opstring;
			}
			vertex_type=v_type;
			loc_in_lattice=location_lattice;
		}

		void display_type(){cout<<vertex_type<<'\n';}
		void count_legs(){cout<<leg_array.size()<<'\n';}
		void get_leg_props(int legindex){cout<<(leg_array[legindex].ptr_to_leg)->leg_index<<'\n'<<(leg_array[legindex].ptr_to_leg)->loc_in_opstring<<'\n';}
};

class Diagonal : public Vertex{
	public:
		Diagonal(int location_lattice, int location_opstring):Vertex(4, location_lattice, location_opstring, 1){}
};

class Spinflip: public Vertex{
	public:
		Spinflip(int location_lattice, int location_opstring):Vertex(2, location_lattice, location_opstring, 2){}
};

class Identity: public Vertex{
	public:
		Identity(int location_lattice, int location_opstring):Vertex(4, location_lattice, location_opstring, 0){}
};

class Plaquette: public Vertex{
	public:
		Plaquette(int location_lattice, int location_opstring):Vertex(2, location_lattice, location_opstring, 14){}
};


int main(){
	int i1,i2,i3;
	vector<Vertex *> opstring;
	stack<leg *> cluster;
	leg *leg_top;
	leg leg_t;
	leg *vfirst[3], *vlast[3];

	opstring.push_back(new Diagonal(0,0));
	opstring.push_back(new Identity(2,1));
	opstring.push_back(new Diagonal(1,2));
	opstring.push_back(new Spinflip(0,3));
	opstring.push_back(new Spinflip(1,4));
	opstring.push_back(new Spinflip(2,5));
	for(int i=0; i<3; i++){vfirst[i]=NULL; vlast[i]=NULL;}
	for(int p=0; p<6; p++){
		if(opstring[p]->vertex_type == 0){continue;}
		else if(opstring[p]->vertex_type == 1){
			i1=opstring[p]->loc_in_lattice; i2=opstring[p]->loc_in_lattice + 1;
			if(vlast[i1] != NULL){
				(opstring[p]->leg_array[0]).ptr_to_leg = vlast[i1];
				vlast[i1]->ptr_to_leg = &(opstring[p]->leg_array[0]);
			}
			else{
				vfirst[i1] = &(opstring[p]->leg_array[0]);
			}
			if(vlast[i2] != NULL){
				(opstring[p]->leg_array[1]).ptr_to_leg = vlast[i2];
				vlast[i2]->ptr_to_leg = &(opstring[p]->leg_array[1]);
			}
			else{
				vfirst[i2] = &(opstring[p]->leg_array[1]);
			}
			vlast[i1] = &(opstring[p]->leg_array[2]);
			vlast[i2] = &(opstring[p]->leg_array[3]);
		}
		else if(opstring[p]->vertex_type == 2){
			i3=opstring[p]->loc_in_lattice;
			if(vlast[i3] != NULL){
				(opstring[p]->leg_array[0]).ptr_to_leg = vlast[i3];
				vlast[i3]->ptr_to_leg = &(opstring[p]->leg_array[0]);
			}
			else{
				vfirst[i3] = &(opstring[p]->leg_array[0]);
			}
			vlast[i3] = &(opstring[p]->leg_array[1]);
		}

		for(int i=0; i<3; i++){
			if(vfirst[i] != NULL){
				vfirst[i]->ptr_to_leg = vlast[i];
				vlast[i]->ptr_to_leg = vfirst[i];
			}
		}
	}
	//(opstring[0]->leg_array[0]).set_visit = true;
	//(opstring[0]->leg_array[2]).set_visit = true;
	//(opstring[3]->leg_array[1]).set_visit = true;
	//(opstring[4]->leg_array[1]).set_visit = true;

	cluster.push(&(opstring[3]->leg_array[0]));
	//while(! cluster.empty()){
	for(int i=0; i<22; i++){
		leg_top = cluster.top();
		if(leg_top->set_visit){leg_top = NULL; cluster.pop();}
		else if(opstring[leg_top->loc_in_opstring]->vertex_type == 2){
			cluster.push(leg_top->ptr_to_leg);
			leg_top->set_visit = true;
		}
		else{
			for(int i=0; i<4; i++){
				(opstring[leg_top->loc_in_opstring]->leg_array[i]).set_visit = true;
				cluster.push(((opstring[leg_top->loc_in_opstring])->leg_array[i]).ptr_to_leg);
			}
		}
	}
	
	while(! cluster.empty()){cout<<(cluster.top())->loc_in_opstring; cluster.pop();}
	

	return 0;
}
