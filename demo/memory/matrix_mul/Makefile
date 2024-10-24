all: mm blockmm blockmm_interchange blockmm_transpose mm_dump rect_blockmm_trans blockmm_transpose_reg blockmm_reg

#perfstats.o: perfstats.c
#	gcc -O3 -c perfstats.c

mm: mm.c perfstats.c
	gcc -DHAVE_LINUX_PERF_EVENT_H -O3 mm.c perfstats.c -o mm 

mm_dump: mm.c perfstats.c
	gcc -DHAVE_LINUX_PERF_EVENT_H -DDUMP -O3 mm.c perfstats.c -o mm_dump 

blockmm: blockmm.c perfstats.c
	gcc -O4 -DHAVE_LINUX_PERF_EVENT_H blockmm.c perfstats.c -o blockmm 

blockmm_reg: blockmm_reg.c perfstats.c
	gcc -O4 -DHAVE_LINUX_PERF_EVENT_H blockmm_reg.c perfstats.c -o blockmm_reg 

blockmm_transpose: blockmm_transpose.c perfstats.c
	gcc -O4 -DHAVE_LINUX_PERF_EVENT_H blockmm_transpose.c perfstats.c -o blockmm_transpose

blockmm_transpose_reg: blockmm_transpose_reg.c perfstats.c
	gcc -O4 -DHAVE_LINUX_PERF_EVENT_H blockmm_transpose_reg.c perfstats.c -o blockmm_transpose_reg

blockmm_interchange: blockmm_interchange.c perfstats.c
	gcc -O4 -DHAVE_LINUX_PERF_EVENT_H blockmm_interchange.c perfstats.c -o blockmm_interchange

rect_blockmm_trans: rect_blockmm_trans.c perfstats.c
	gcc -O4 -DHAVE_LINUX_PERF_EVENT_H rect_blockmm_trans.c perfstats.c -o rect_blockmm_trans

blockmm_transpose_prefetch: blockmm_transpose.c perfstats.c 
	gcc -O4 -fprefetch-loop-arrays blockmm_transpose.c perfstats.c -o blockmm_transpose

clean:
		rm -f blockmm mm blockmm_transpose cachegrind.* mm_dump rect_blockmm_trans blockmm_transpose_reg blockmm_reg
