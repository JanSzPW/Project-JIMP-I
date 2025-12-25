#include "readMap.h"


map *readMap(FILE *in) {
    map *mp = malloc( sizeof(map) );

    //read those from file
    mp -> size = createVector(1,1);
    mp -> g_best = createVector(1,1);
    mp -> signal = malloc( mp->size->x * mp->size->y);
    mp -> particles = NULL;

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