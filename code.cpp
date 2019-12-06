#include "graph.h"
#include "PageRankEstimatorOMP.h"
int main()
{
	Graph g = Graph(webNotredame);
	PageRankEstimatorOMP pre = PageRankEstimatorOMP(g);
	double time1 = omp_get_wtime();
	pre.RunPageRankEstimator(8, 10, 0.2, 1);
	cout << omp_get_wtime() - time1 <<endl;
	//tuple<int,int>* values = pre.getTop5();
	//cout << get<0>(values[0]) << ":" << (get<1>(values[0])) << ":" << (get<1>(values[0])) / static_cast<double>(pre.totalWalks) << endl;
	//cout << get<0>(values[1]) << ":" << (get<1>(values[1])) << ":" << (get<1>(values[1])) / static_cast<double>(pre.totalWalks) << endl;
	//cout << get<0>(values[2]) << ":" << (get<1>(values[2])) << ":" << (get<1>(values[2])) / static_cast<double>(pre.totalWalks) << endl;
	//cout << get<0>(values[3]) << ":" << (get<1>(values[3])) << ":" << (get<1>(values[3])) / static_cast<double>(pre.totalWalks) << endl;
	//cout << get<0>(values[4]) << ":" << (get<1>(values[4])) << ":" << (get<1>(values[4])) / static_cast<double>(pre.totalWalks) << endl;
	
	return 0;
}