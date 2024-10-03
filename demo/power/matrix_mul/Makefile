all: blockmm_pthread blockmm mm blockmm_transpose

#perfstats.o: perfstats.c
#	gcc -O3 -c perfstats.c

mm: mm.c perfstats.c
	gcc -DHAVE_LINUX_PERF_EVENT_H -O3 mm.c perfstats.c -o mm 

mm_dump: mm.c perfstats.c
	gcc -DHAVE_LINUX_PERF_EVENT_H -DDUMP -O3 mm.c perfstats.c -o mm_dump 

blockmm_pthread: blockmm_pthread.c perfstats.c
	gcc -O3 -DHAVE_LINUX_PERF_EVENT_H blockmm.c perfstats.c -o blockmm_pthread 

blockmm_transpose: blockmm_transpose.c perfstats.c
	gcc -O3 -DHAVE_LINUX_PERF_EVENT_H blockmm_transpose.c perfstats.c -o blockmm_transpose

blockmm_interchange: blockmm_interchange.c perfstats.c
	gcc -O3 -DHAVE_LINUX_PERF_EVENT_H blockmm_interchange.c perfstats.c -o blockmm_interchange

blockmm_transpose_prefetch: blockmm_transpose.c perfstats.c 
	gcc -O3 -fprefetch-loop-arrays blockmm_transpose.c perfstats.c -o blockmm_transpose

clean:
		rm -f blockmm mm blockmm_pthread blockmm_transpose cachegrind.* mm_dump
