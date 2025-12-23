all:
	cc -Wall --pedantic src/*.c -o bin/swarm

run: all
	bin/swarm data/map.txt -i 50 -p 50 -n 10 -c data/config.txt

test: all
	bin/swarm data/map.txt
