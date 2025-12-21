#ifndef STRUCT_H
#define STRUCT_H

typedef struct vector {
	int x;
	int y;
} vector;

typedef struct particle {
	vector *position;
	vector *velocity;
	vector *p_best;		//personal best
	double weight;		//inertia
	struct particle *nxt;	//instead of a seperate swarm struct
			     	//we will have a linked list of particles
			     	//attached to map structure
} particle;

typedef struct map {
	vector *size;
	double *signal;		//signal strength, flattened 2d array
	vector *g_best;
	particle *particles;
} map;

//get signal strength at position pos
double get_signal(vector pos);

//calculate new speed and position
void next_iteration(particle ptcl);


#endif
