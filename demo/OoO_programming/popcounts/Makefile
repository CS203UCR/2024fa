all: popcount popcount_B popcount_C popcount_D popcount_SSE42 popcount_E

EXTRA_OPTS = -DHAVE_LINUX_PERF_EVENT_H -w

perfstats.o: perfstats.c perfstats.h
	gcc -g  -O3 $(EXTRA_OPTS) -I$(PWD) $(LIBS) -o perfstats.o -c perfstats.c

popcount: perfstats.o popcount.cpp
	g++ -O3 $(EXTRA_OPTS) popcount.cpp perfstats.o -o popcount_A
	g++ -S -O3 $(EXTRA_OPTS) popcount.cpp -o A.s

popcount_B: perfstats.o popcount.cpp
	g++ -O3 $(EXTRA_OPTS) -DB popcount.cpp perfstats.o -o popcount_B
	g++ -S -O3 $(EXTRA_OPTS) -DB popcount.cpp -o B.s

popcount_C: perfstats.o popcount.cpp
	g++ -O3 $(EXTRA_OPTS) -DC popcount.cpp perfstats.o -o popcount_C
	g++ -S -O3 $(EXTRA_OPTS) -DC popcount.cpp -o C.s

popcount_D: perfstats.o popcount.cpp
	g++ -O3 $(EXTRA_OPTS) -DD popcount.cpp perfstats.o -o popcount_D
	g++ -S -O3 $(EXTRA_OPTS) -DD popcount.cpp -o D.s

popcount_E: perfstats.o popcount.cpp
	g++ -O3 $(EXTRA_OPTS) -DE popcount.cpp perfstats.o -o popcount_E
	g++ -S -O3 $(EXTRA_OPTS) -DE popcount.cpp -o E.s

popcount_SSE42: perfstats.o popcount.cpp
	g++ -O3 $(EXTRA_OPTS) -m64 -msse4.2 -DSSE42 popcount.cpp perfstats.o -o popcount_SSE42
	
dump:
	otool -tV popcount
	otool -tV popcount_inline 
	
clean:
		rm -f popcount_A popcount_B popcount_C popcount_D popcount_SSE42 popcount_E
		