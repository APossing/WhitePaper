#!/bin/sh
mpicxx -std=c++11 -o out -fopenmp code.cpp graph.cpp PageRankEstimatorOMP.cpp -lm
for j in 64 128 512 1024 2048 4096 8192 16384
do
	for i in 0 1 2 3
	do
		./out ${i} ${j} 0.2
	done
done
for j in 0 0.05 0.1 0.15 0.2 
do
	for i in 0 1 2 3
	do
		./out ${i} 100 ${j}
	done
rm out
