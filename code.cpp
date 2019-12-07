#include "graph.h"
#include "PageRankEstimatorOMP.h"

void runSpeedupTests(ofstream* myfile, PageRankEstimatorOMP pre)
{
	double time1;
	for (int i = 1; i <= 8; i *= 2)
	{
		time1 = omp_get_wtime();
		pre.RunPageRankEstimator(i, 10, 0.05, 1);
		*myfile << i << ',' << omp_get_wtime() - time1 << endl;
		tuple<int, int>* values = pre.getTop5();
		(*myfile) << get<0>(values[0]) << "," << (get<1>(values[0])) << "," << (get<1>(values[0])) / static_cast<double>(pre.totalWalks);
		(*myfile) << "," << get<0>(values[1]) << "," << (get<1>(values[1])) << "," << (get<1>(values[1])) / static_cast<double>(pre.totalWalks);
		(*myfile) << "," << get<0>(values[2]) << "," << (get<1>(values[2])) << "," << (get<1>(values[2])) / static_cast<double>(pre.totalWalks);
		(*myfile) << "," << get<0>(values[3]) << "," << (get<1>(values[3])) << "," << (get<1>(values[3])) / static_cast<double>(pre.totalWalks);
		(*myfile) << "," << get<0>(values[4]) << "," << (get<1>(values[4])) << "," << (get<1>(values[4])) / static_cast<double>(pre.totalWalks) << endl;
	}
}

int main()
{

	ofstream myfile;
	myfile.open("stats.csv");
	
	Graph g = Graph(webNotredame);
	myfile << "webNotreDame" << endl;
	PageRankEstimatorOMP pre = PageRankEstimatorOMP(g);
	runSpeedupTests(&myfile, pre);

	g = Graph(webGoogle);
	pre = PageRankEstimatorOMP(g);
	myfile << "webGoogle" << endl;
	runSpeedupTests(&myfile, pre);



	return 0;
}


