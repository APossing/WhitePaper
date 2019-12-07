#include "graph.h"
#include "PageRankEstimatorOMP.h"

void printTop5(ofstream* file, PageRankEstimatorOMP pre)
{
	tuple<int, int>* values = pre.getTop5();
	(*file) << get<0>(values[0]) << "," << (get<1>(values[0])) << "," << (get<1>(values[0])) / static_cast<double>(pre.totalWalks);
	(*file) << get<0>(values[1]) << "," << (get<1>(values[1])) << "," << (get<1>(values[1])) / static_cast<double>(pre.totalWalks);
	(*file) << get<0>(values[2]) << "," << (get<1>(values[2])) << "," << (get<1>(values[2])) / static_cast<double>(pre.totalWalks);
	(*file) << get<0>(values[3]) << "," << (get<1>(values[3])) << "," << (get<1>(values[3])) / static_cast<double>(pre.totalWalks);
	(*file) << get<0>(values[4]) << "," << (get<1>(values[4])) << "," << (get<1>(values[4])) / static_cast<double>(pre.totalWalks) << endl;
}

int main()
{
	double time1;
	ofstream myfile;
	myfile.open("stats.txt");
	Graph g = Graph(webNotredame);
	myfile << "webNotreDame" << endl;
	PageRankEstimatorOMP pre = PageRankEstimatorOMP(g);
	for (int i = 1; i <= 8; i *= 2)
	{
		time1 = omp_get_wtime();
		pre.RunPageRankEstimator(i, 1000, 0.05, 1);
		myfile << i << ',' << omp_get_wtime() - time1 << endl;
		printTop5(&myfile, pre);
	}

	g = Graph(webGoogle);
	pre = PageRankEstimatorOMP(g);
	myfile << "webGoogle" << endl;
	for (int i = 1; i <= 8; i *= 2)
	{
		time1 = omp_get_wtime();
		pre.RunPageRankEstimator(i, 10000, 0.05, 1);
		myfile << omp_get_wtime() - time1 << endl;
		printTop5(&myfile, pre);
	}



	return 0;
}


