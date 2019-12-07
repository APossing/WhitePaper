mpixx -g -o out -fopenmp code.cpp graph.cpp PageRankEstimatorOMP.cpp -lm
./out
rm out
