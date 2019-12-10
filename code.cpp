#include "graph.h"
#include "PageRankEstimatorOMP.h"

void runSpeedupTests(ofstream* myfile, PageRankEstimatorOMP pre, Graph* g, int k, double d)
{
	double time1;
	for (int i = 1; i <= 8; i *= 2)
	{
		pre.ResetCounts(g);
		time1 = omp_get_wtime();
		pre.RunPageRankEstimator(i, k, d, 1, g);
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
	int x = std::atoi(argv[1]);
	int k = std::atoi(argv[2]);
	char e = argv[3][0];
	double d = std::stod(argv[4]);
	string str = "";
	ofstream myfile;
	switch (x)
	{
	case 0:
		myfile.open(str+"berk"+e+".csv", ofstream::app);
		myfile << "webBerkstan" << "," << k << "," << d << endl;
		break;
	case 1:
		myfile.open(str+"google"+e+".csv", ofstream::app);
		myfile << "webGoogle" << "," << k << "," << d << endl;
		break;
	case 2:
		myfile.open(str+"notre"+e+".csv", ofstream::app);
		myfile << "webNotreDame" << "," << k << "," << d << endl;
		break;
	case 3:
		myfile.open(str+"facebook"+e+".csv", ofstream::app);
		myfile << "webFacebookeCombined" << "," << k << "," << d << endl;
		break;
	}
	myfile << FileType(x) << endl;


	Graph g1 = Graph(FileType(x));

	PageRankEstimatorOMP pre1 = PageRankEstimatorOMP(&g1);
	cout << "running speedupTests" << endl;
	runSpeedupTests(&myfile, pre1, &g1, k, d);
	cout << "complete" << endl;
	return 0;
}


