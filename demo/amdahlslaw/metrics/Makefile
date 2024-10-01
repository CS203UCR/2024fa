BUILD_DIR=./build
EXECUTABLE=cudamm cpumm cudamm_int cpumm_int cudamm_double cpumm_double cpumm_float
#EXTRA_CFLAGS= -DOUTPUT
EXTRA_CFLAGS=  -arch=sm_80

.SUFFIXES:

all: $(EXECUTABLE)

cudamm: matrix_cuda.cu
	/usr/local/cuda/bin/nvcc $(EXTRA_CFLAGS) matrix_cuda.cu -o cudamm

cpumm: cpumm.c
	g++ -O3  cpumm.c -o cpumm

cudamm_int: matrix_cuda.cu
	/usr/local/cuda/bin/nvcc $(EXTRA_CFLAGS) -DD_TYPE=int matrix_cuda.cu -o cudamm_int

cpumm_int: cpumm.c
	g++ -O3 -DD_TYPE=int cpumm.c -o cpumm_int

cudamm_double: matrix_cuda.cu
	/usr/local/cuda/bin/nvcc $(EXTRA_CFLAGS) -DD_TYPE=double matrix_cuda.cu -o cudamm_double

cpumm_double: cpumm.c
	g++ -O3 -DD_TYPE=double cpumm.c -o cpumm_double

cpumm_float: cpumm.c
	g++ -O3 -DD_TYPE=float cpumm.c -o cpumm_float
	
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
	