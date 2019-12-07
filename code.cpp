#include "graph.h"
#include "PageRankEstimatorOMP.h"

void runSpeedupTests(ofstream* myfile, Graph* g)
{
	double time1;
	for (int i = 1; i <= 8; i *= 2)
	{
		PageRankEstimatorOMP pre = PageRankEstimatorOMP(g);
		//pre.ResetCounts();
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

	Graph* g3 = new Graph(FileType(webBerkstan));
	myfile << "berk" << endl;
	cout << "running speedupTests" << endl;
	runSpeedupTests(&myfile, g3);
	cout << "complete" << endl;
	delete g3;
	
	Graph* g2 = new Graph(FileType(webGoogle));
	myfile << "gogle" << endl;
	cout << "running speedupTests" << endl;
	runSpeedupTests(&myfile, g2);
	cout << "complete" << endl;
	delete g2;
	Graph* g1 = new Graph(FileType(facebookCombined));
	myfile << "facebookCombined" << endl;
	cout << "running speedupTests" << endl;
	runSpeedupTests(&myfile, g1);
	cout << "complete" << endl;
	delete g1;

	Graph* g4 = new Graph(FileType(webNotredame));
	myfile << "notre" << endl;
	cout << "running speedupTests" << endl;
	runSpeedupTests(&myfile, g4);
	cout << "complete" << endl;
	delete g4;

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


