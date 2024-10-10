all: mm blockmm blockmm_transpose mm_dump

#perfstats.o: perfstats.c
#	gcc -O3 -c perfstats.c

mm: mm.c perfstats.c
	gcc -DHAVE_LINUX_PERF_EVENT_H -O3 mm.c perfstats.c -o mm 

mm_dump: mm.c perfstats.c
	gcc -DHAVE_LINUX_PERF_EVENT_H -DDUMP -O3 mm.c perfstats.c -o mm_dump 

blockmm: blockmm.c perfstats.c
	gcc -O3 -DHAVE_LINUX_PERF_EVENT_H blockmm.c perfstats.c -o blockmm 

blockmm_transpose: blockmm_transpose.c perfstats.c
	gcc -O3 -DHAVE_LINUX_PERF_EVENT_H blockmm_transpose.c perfstats.c -o blockmm_transpose

blockmm_transpose_prefetch: blockmm_transpose.c perfstats.c 
	gcc -O3 -fprefetch-loop-arrays blockmm_transpose.c perfstats.c -o blockmm_transpose

clean:
		rm -f blockmm mm blockmm_transpose cachegrind.* mm_dump
