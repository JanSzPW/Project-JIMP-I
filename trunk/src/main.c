#include "structures.h"
#include "readMap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
            if (argv[i][1] == 'p')
                particles = atoi(argv[i+1]);
            //iteration count read from -i argument
            else if (argv[i][1] == 'i')
                iterations = atoi(argv[i+1]);
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
                    else if (strcmp(tmp, "r1") == 0)
                        r1 = tmp_d;
                    else if (strcmp(tmp, "r2") == 0)
                        r2 = tmp_d;
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

    dropMap(main_map);

}