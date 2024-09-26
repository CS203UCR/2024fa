all: madd_A madd_B arraySort bitonic quicksort quicksort_cpu

perfstats.o: perfstats.c
	gcc -O3 -c perfstats.c


madd_A: madd_A.c
	gcc -O3 madd_A.c -o madd_A

madd_B: madd_B.c
	gcc -O3 madd_B.c -o madd_B

mm: mm.c 
	gcc -O3 mm.c perfstats.o -o mm 


arraySort: arraySort.cpp calculate_sum.c
	gcc calculate_sum.c -c 
	g++ -O0 arraySort.cpp calculate_sum.o -o arraySort

arraySortO3: arraySort.cpp calculate_sum.c
	gcc calculate_sum.c -c 
	g++ -O3 arraySort.cpp calculate_sum.o -o arraySort
    
bitonic: bitonic.cu
	/usr/local/cuda/bin/nvcc -O3 bitonic.cu -o bitonic
        
quicksort: quicksort.cu 
	/usr/local/cuda/bin/nvcc -O3 quicksort.cu -o quicksort

quicksort_cpu: quicksort_cpu.cpp 
	/usr/local/cuda/bin/nvcc -O3 quicksort_cpu.cpp -o quicksort_cpu

clean:
		rm -f madd_A madd_B arraySort bitonic quicksort quicksort_cpu
