all:  arithmetics swap flip_array linked_list linked_list.s


#arraySort

EXTRA_CFLAGS = -DHAVE_LINUX_PERF_EVENT_H
CFLAGS = -O3

arithmetics: arithmetics.c 
	$(CC) -O4 $(EXTRA_CFLAGS) arithmetics.c -o arithmetics
	$(CC) -O4 $(EXTRA_CFLAGS) -S arithmetics.c 

arithmetics_3: arithmetics_3.c perfstats.c
	$(CC) -O0 $(EXTRA_CFLAGS) perfstats.c arithmetics_3.c -o arithmetics_3
	$(CC) -O0 $(EXTRA_CFLAGS) perfstats.c -S arithmetics_3.c 

swap: swap.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) swap.c -o swap

flip_array: flip_array.c perfstats.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) perfstats.c flip_array.c -o flip_array
	$(CC) -S $(CFLAGS) $(EXTRA_CFLAGS)  flip_array.c -o flip_array.s

linked_list: linked_list.c perfstats.c 
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) perfstats.c  linked_list.c -o linked_list

linked_list.s: linked_list.c perfstats.c 
	$(CC) -S $(CFLAGS) $(EXTRA_CFLAGS) linked_list.c -o linked_list.s
	
clean:
		rm -f arithmetics linked_list flip_array swap linked_list.s
