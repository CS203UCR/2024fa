#!/bin/bash
LD_PRELOAD=libhugetlbfs.so HUGETLB_MORECORE=yes ../memory/matrix_mul/blockmm 2048 256
