#pragma once
#include "graph.h"
#include <cstdlib>
#include <stdio.h>
#include <omp.h>
#include <list>
#include <stack>

class PageRankEstimatorOMP
{
public:
	PageRankEstimatorOMP(Graph g);
	void RunPageRankEstimator(int threads, int k, int damping);
	int* counts;
	int countsSize;
	int totalWalks;
	tuple<int,int>* getTop5();
private:
	Graph graph;
	void print(int val);
	void print(double val);
	void print(string val);
	void print(size_t val);
	tuple<int, int>* getTop5(int* unordered, int size);
};

