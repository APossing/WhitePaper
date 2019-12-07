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
	PageRankEstimatorOMP(Graph *g);
	void RunPageRankEstimator(int threads, int k, double damping, double backDampening);
	int* counts;
	int countsSize;
	int totalWalks;
	tuple<int,int>* getTop5();
private:
	Graph *graph;
	void print(int val);
	void print(double val);
	void print(string val);
	void print(size_t val);
	int getTailsNextLocation(int targetId, stack<int> prevLocations, drand48_data* randBuffer, double backDampening);
	int getHeadsNextLocation(int targetId, stack<int> prevLocations, drand48_data* randBuffer); 
	tuple<int, int>* getTop5(int* unordered, int size);
};

