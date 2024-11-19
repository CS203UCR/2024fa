all: bstSearch

perfstats.o: perfstats.c perfstats.h
	gcc -g -DHAVE_LINUX_PERF_EVENT_H $(EXTRA_OPTS) -I$(PWD) $(LIBS) -o perfstats.o -c perfstats.c


bst.o: bst.c
	gcc -g -DHAVE_LINUX_PERF_EVENT_H $(EXTRA_OPTS) -I$(PWD) $(LIBS) -o bst.o -c bst.c

bstSearch: bstSearch.cpp bst.o perfstats.o
	g++ -O3 -DHAVE_LINUX_PERF_EVENT_H $(EXTRA_OPTS) bstSearch.cpp perfstats.o bst.o -o bstSearch


clean:
		rm -f bstSearch *.o
