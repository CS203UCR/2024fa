all: array_swap 

perfstats.o: perfstats.c perfstats.h
	gcc -g -DHAVE_LINUX_PERF_EVENT_H -O3 $(EXTRA_OPTS) -I$(PWD) $(LIBS) -o perfstats.o -c perfstats.c

array_swap: swap.c perfstats.o
	g++ -DHAVE_LINUX_PERF_EVENT_H -O3 $(EXTRA_OPTS) perfstats.o -I$(PWD) -o array_swap -c swap.c

loop_unroll: loop_unroll.c calculate_sum.o perfstats.o
	g++ -O3 -DHAVE_LINUX_PERF_EVENT_H $(EXTRA_OPTS) loop_unroll.c perfstats.o calculate_sum.o -o loop_unroll

clean:
		rm -f array_swap *.o
