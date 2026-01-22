#include "structures.h"
#include "readMap.h"
#include "pso.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {

    //defaults
    int particles = 30;
    int iterations = 100;
    int save_frequency = 0;

    //defaults
    char tmp[4]; //we assume config file is not broken (c1 0.5, not someLongString, that would overflow the variable)
    double tmp_d;
    double w = 0.5;
    double c1 = 0.5;
    double c2 = 0.5;
    double r1 = 0.5;
    double r2 = 0.5;

    if (argc < 2) {
        printf("Incorrect arguments\n");
        return EXIT_FAILURE;
    }

    //process arguments
    int i;
    for (i=2;i<argc;i++) {
        if (i >= argc-1)
            break;
        else if (argv[i][0] != '-')
            printf("Arguments: -p <particles> -i <iterations> -c <config file> -n <save frequency>\n");
        else {
            //particle count read from -p argument
            if (argv[i][1] == 'p') {
				if (atoi(argv[i+1]) <= 0) {
					printf("-p can't be less than or equal to zero\n");
					return EXIT_FAILURE;					
				}
                particles = atoi(argv[i+1]);
			}
            //iteration count read from -i argument
            else if (argv[i][1] == 'i') {
				if (atoi(argv[i+1]) <= 0) {
					printf("-i can't be less than or equal to zero\n");
					return EXIT_FAILURE;					
				}
                iterations = atoi(argv[i+1]);
			}
            //process config file
            else if (argv[i][1] == 'c') {
                FILE *conf = fopen(argv[i+1], "r");
                if (conf == NULL) {
                    printf("Error reading config file %s\n", argv[i+1]);
                    continue;
                }
                while (fscanf(conf, "%s %lf\n", tmp, &tmp_d) == 2) {
                    if (strcmp(tmp, "w") == 0)
                        w = tmp_d;
                    else if (strcmp(tmp, "c1") == 0)
                        c1 = tmp_d;
                    else if (strcmp(tmp, "c2") == 0)
                        c2 = tmp_d;
                }
                fclose(conf);
            }
            //save frequency read from -n argument
            else if (argv[i][1] == 'n')
                save_frequency = atoi(argv[i+1]);
            else {
                printf("Unknown argument \"%s\"\n", argv[i]);
                continue;
            }
            i++;
        }
    }
    printf("Particles: %d, iterations: %d, save frequency: %d\n", particles, iterations, save_frequency);
    printf("w=%lf c1=%lf c2=%lf r1=%lf r2=%lf\n", w, c1, c2, r1, r2);

    //read map from file
    FILE *in = fopen(argv[1],"r");
    if (in == NULL) {
        printf("Error reading map file %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    map *main_map = readMap(in);
    fclose(in);
    if (main_map == NULL)
        return EXIT_FAILURE;

    //initiate particles
    srand(time(NULL));
    for (i=0;i<particles;i++) {
        main_map -> particles = createParticle(main_map->particles, main_map->size);
    }


    //main logic
	char filename[32];
    FILE *save;
    for (i=0;i<iterations;i++) {
        //save current state every n iterations
        if (save_frequency>0 && i%save_frequency == 0) {
            snprintf(filename, sizeof(filename), "data/save_%d.svg", i/save_frequency);
            save = fopen(filename, "w");
            // fprintf(save, "Iteration %d:\n", i);
            save_state(main_map->particles, particles, save, main_map->size->x, main_map->size->y);
            fclose(save);
        }
        //advance particles
        next_iteration(main_map->particles,w,c1,c2,r1,r2, main_map);
    }
    //final save of the state at the end
    save = fopen("data/save_final.svg", "w");
    save_state(main_map->particles, particles, save, main_map->size->x, main_map->size->y);
    fclose(save);

    printf("Found strongest signal at location (%d, %d). Singal strength: %lf\n", (int)main_map->g_best->x, (int)main_map->g_best->y, main_map->g_best->val);

    //free memory
    dropMap(main_map);

}
