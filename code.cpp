#include "graph.h"
#include "PageRankEstimatorOMP.h"

void runSpeedupTests(ofstream* myfile, PageRankEstimatorOMP pre, Graph* g)
{
	double time1;
	for (int i = 1; i <= 8; i *= 2)
	{
		pre.ResetCounts(g);
		time1 = omp_get_wtime();
		pre.RunPageRankEstimator(i, 10, 0.05, 1,g);
		*myfile << i << ',' << omp_get_wtime() - time1 << endl;
		tuple<int, int>* values = pre.getTop5();
		(*myfile) << get<0>(values[0]) << "," << (get<1>(values[0])) << "," << (get<1>(values[0])) / static_cast<double>(pre.totalWalks);
		(*myfile) << "," << get<0>(values[1]) << "," << (get<1>(values[1])) << "," << (get<1>(values[1])) / static_cast<double>(pre.totalWalks);
		(*myfile) << "," << get<0>(values[2]) << "," << (get<1>(values[2])) << "," << (get<1>(values[2])) / static_cast<double>(pre.totalWalks);
		(*myfile) << "," << get<0>(values[3]) << "," << (get<1>(values[3])) << "," << (get<1>(values[3])) / static_cast<double>(pre.totalWalks);
		(*myfile) << "," << get<0>(values[4]) << "," << (get<1>(values[4])) << "," << (get<1>(values[4])) / static_cast<double>(pre.totalWalks) << endl;
	}
}

int main(int argc, char* argv[])
{

	std::string arg = argv[1];
	std::size_t pos;
	int x = std::stoi(arg, &pos);
	ofstream myfile;
	myfile.open("stats.csv", ofstream::app);

	Graph g1 = Graph(FileType(x));
	myfile << FileType(x) << endl;
	PageRankEstimatorOMP pre1 = PageRankEstimatorOMP(&g1);
	cout << "running speedupTests" << endl;
	runSpeedupTests(&myfile, pre1, &g1);
	cout << "complete" << endl;

	//
	//Graph g2 = Graph(facebookCombined);
	//PageRankEstimatorOMP pre2 = PageRankEstimatorOMP(g2);
	//myfile << "Facebook" << endl;
	//runSpeedupTests(&myfile, pre2);

	//Graph g3 = Graph(webBerkstan);
	//PageRankEstimatorOMP pre3 = PageRankEstimatorOMP(g3);
	//myfile << "berkStan" << endl;
	//runSpeedupTests(&myfile, pre3);

	//Graph g4 = Graph(webGoogle);
	//PageRankEstimatorOMP pre4 = PageRankEstimatorOMP(g4);
	//myfile << "webGoogle" << endl;
	//runSpeedupTests(&myfile, pre4);





	return 0;
}


