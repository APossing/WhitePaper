#!/bin/sh
mpicxx -std=c++11 -o out -fopenmp code.cpp graph.cpp PageRankEstimatorOMP.cpp -lm
./out
rm out
