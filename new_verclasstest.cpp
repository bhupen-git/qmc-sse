#include<iostream>
#include<vector>

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
};

class Diagonal : public Vertex{
	public:
		Diagonal(int location_lattice, int location_opstring):Vertex(4, location_lattice, location_opstring, 1){}
};

class Spinflip: public Vertex{
	public:
		Spinflip(int location_lattice, int location_opstring):Vertex(2, location_lattice, location_opstring, 2){}
};

int main(){
	vector<Vertex *> opstring;
	opstring.push_back(new Diagonal(2,0));
	opstring.push_back(new Spinflip(3,4));
	opstring[1]->display_type();
	opstring[1]->count_legs();
	return 0;
}
