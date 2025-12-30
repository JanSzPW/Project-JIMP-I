#include "readMap.h"


map *readMap(FILE *in) {
    int i,j;
    double signal;

    map *mp = malloc( sizeof(map) );

    //read map dimensions
    int x,y;
    if (fscanf(in, "%d %d\n", &x, &y) != 2)
        return NULL;

    mp -> size = createVector(x,y);
    mp -> g_best = createVector(0,0);
    mp -> particles = NULL;

    //initiate matrix list of the right size
    mp -> signal = malloc( x * y * sizeof(double));
    //read signal strength from file
    for (i=0;i<x;i++)
        for (j=0;j<y;j++)
            if (fscanf(in, "%lf ", &signal) == 1)
                mp->signal[i*x+j] = signal;
            else {
                dropMap(mp);
                return NULL;
            }

    return mp;
}

void dropMap(map *mp) {

    free(mp -> g_best);
    free(mp -> size);
    free(mp -> signal);

    particle *p = mp->particles;
    while (p != NULL) {
        p = dropParticle(p);
    }

    free(mp);
}