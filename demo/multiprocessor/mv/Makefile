all: matvec matvec_threaded

EXTRA_CFLAGS = -DHAVE_LINUX_PERF_EVENT_H -g -O3 -pthread -w

matvec: matvec.c perfstats.c
	$(CC) $(EXTRA_CFLAGS)  matvec.c perfstats.c -o matvec

matvec_threaded: matvec_threaded.c perfstats.c
	$(CC) $(EXTRA_CFLAGS)  matvec_threaded.c perfstats.c -o matvec_threaded

clean:
		rm -f matvec matvec_threaded
		