EXECS =  testloop testloop_O3 coherence blockmm blockmm_pthread value_of_i vadd_sse fence mfence vadd_sse_two_threads vadd_sse_two_threads_chunk vadd_mt vadd_mt_chunk testloop_volatile testloop_O3_volatile coherence_lock

EXTRA_CFLAGS = -O3 -Wno-format-zero-length -Wno-implicit-function-declaration -w

all: $(EXECS)

testloop_O3: testloop.c
	gcc  -O3 -g testloop.c -pthread -lpthread -o testloop_O3
#	otool -tV testloop_O3 > testloop_O3.dump 


testloop: testloop.c
	gcc -O0 -g testloop.c -pthread -lpthread -o testloop 

testloop_O3_volatile: testloop.c
	gcc  -O3 -DVOLATILE testloop.c -pthread -lpthread -o testloop_O3_volatile


testloop_volatile: testloop.c
	gcc -O0 -g testloop.c -pthread -lpthread -o testloop_volatile 
#	otool -tV testloop > testloop.dump 

coherence: coherence.c
	gcc -O3 coherence.c -pthread -lpthread -o coherence 

coherence_lock: coherence_lock.c
	gcc -O3 coherence_lock.c -pthread -lpthread -o coherence_lock 

value_of_i: value_of_i.c
	gcc value_of_i.c -pthread -lpthread -o value_of_i

blockmm_pthread: blockmm_pthread.c
	gcc  -O3 blockmm_pthread.c -pthread -lpthread -o blockmm_pthread

blockmm: blockmm.c
	gcc  -O3 blockmm.c -pthread -lpthread -o blockmm 

vadd_sse: vadd.c 
	$(CC) $(EXTRA_CFLAGS) -DSSE vadd.c -o vadd_sse

vadd_sse_pthread: vadd_pthread.c 
	$(CC) $(EXTRA_CFLAGS) -pthread -DSSE vadd_pthread.c -o vadd_sse_pthread 

vadd_sse_two_threads: vadd_two_threads.c 
	$(CC) $(EXTRA_CFLAGS) -pthread -DSSE vadd_two_threads.c -o vadd_sse_two_threads

vadd_sse_two_threads_chunk: vadd_two_threads.c 
	$(CC) $(EXTRA_CFLAGS) -lpthread -DSSE -DCHUNK vadd_two_threads.c -o vadd_sse_two_threads_chunk

vadd_mt: vadd_mt.c perfstats.c
	$(CC) $(EXTRA_CFLAGS) -mno-avx -DHAVE_LINUX_PERF_EVENT_H -pthread -DSSE vadd_mt.c perfstats.c -o vadd_mt

vadd_mt_chunk: vadd_mt.c 
	$(CC) $(EXTRA_CFLAGS) -mno-avx -DHAVE_LINUX_PERF_EVENT_H -pthread -DSSE -DCHUNK vadd_mt.c perfstats.c -o vadd_mt_chunk 

pthread_overhead: pthread_overhead.c
	$(CC) $(EXTRA_CFLAGS) -lpthread -DSSE pthread_overhead.c -o pthread_overhead

fence: fence.c 
	$(CC) $(EXTRA_CFLAGS) fence.c -o fence -lpthread

mfence: fence.c 
	$(CC) -DMFENCE $(EXTRA_CFLAGS) fence.c -o mfence -lpthread


clean:
		rm -f $(EXECS)
		rm -rf *.dSYM
