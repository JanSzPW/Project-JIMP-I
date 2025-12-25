#ifndef STRUCT_H
#define STRUCT_H

typedef struct vector {
	int x;
	int y;
	double val; //only used for p_best and g_best vectors
} vector;

typedef struct particle {
	vector *position;
	vector *velocity;
	vector *p_best;		//personal best
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


vector *createVector(int x, int y);
void dropVector(vector *v);

particle *createParticle(particle *tl, vector *map_size);
particle *dropParticle(particle *p);


#endif
