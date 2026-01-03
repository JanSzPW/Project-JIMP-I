all:
	cc -Wall --pedantic src/*.c -o bin/swarm

run: all
	bin/swarm data/map.txt -i 50 -p 50 -n 10 -c data/config.txt

test: all
	bin/swarm data/map.txt
	bin/swarm data/map.txt -t -i 50 -p 50 -n 10 -c data/config.txt
	bin/swarm data/map.txt -i 50 -t test -p 50 -n 10 -c data/config.txt
	bin/swarm data/map.txt - -t test -p 50 -n 10 -c data/config.txt

vg: all
	valgrind bin/swarm data/map.txt -i 10 -p 5 -n 3 -c data/config.txt
