all: linked_list linked_list.s


#arraySort

EXTRA_CFLAGS = -DHAVE_LINUX_PERF_EVENT_H
CFLAGS = -O1 -w -mno-avx -Wno-implicit-function-declaration -Wno-format-zero-length

linked_list: linked_list.c linked_list_main.c perfstats.c 
	$(CC) -c $(CFLAGS) $(EXTRA_CFLAGS) perfstats.c 
	$(CC) -c $(CFLAGS) $(EXTRA_CFLAGS) linked_list.c 
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) linked_list.o perfstats.o  linked_list_main.c -o linked_list

linked_list.s: linked_list.c 
	$(CC) -S $(CFLAGS) $(EXTRA_CFLAGS) linked_list.c 
	
clean:
		rm -f linked_list linked_list.s
