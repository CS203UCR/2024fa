all: unaligned struct struct_O3

EXTRA_CFLAGS = -DHAVE_LINUX_PERF_EVENT_H -g

struct_O3:
	gcc -O3 struct.c -o struct_O3
	
struct:
	gcc -O0 struct.c -o struct


unaligned: unaligned.c
	gcc $(EXTRA_CFLAGS) unaligned.c -o unaligned

clean:
		rm -f unaligned struct struct_O3
