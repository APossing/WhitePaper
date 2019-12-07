#include "PageRankEstimatorOMP.h"
#include <ctime>
bool isHardDebug = false;
PageRankEstimatorOMP::PageRankEstimatorOMP(Graph* graph)
{
	countsSize = graph->max;
	totalWalks = 0;
	counts = new int[graph->max]{ 0 };
}

void PageRankEstimatorOMP::ResetCounts(Graph* graph)
{
	counts = new int[graph->max]{ 0 };
	countsSize = graph->max;
}

PageRankEstimatorOMP::~PageRankEstimatorOMP()
{
	//free(counts);
}

void PageRankEstimatorOMP::RunPageRankEstimator(int threads, int k, double damping, double backDampening, Graph* graph)
{
	omp_set_dynamic(0);     // disable dynamic teams
	omp_set_num_threads(threads); // Use p threads for all consecutive parallel regions

	cout << graph->nodes.size() << endl;

	drand48_data* randBuffer = new struct drand48_data[threads]();
	srand48((unsigned int)time(NULL));

	int myTotalWalks = 0;
	
#pragma omp parallel for schedule(static) reduction(+: myTotalWalks) 
	for (int i = 0; i < graph->max; i++)
	{
		double value;
		myTotalWalks++;
		if (i % 10000 == 0 || i > 685000)
			cout << i << endl;
		int nodeTarget = i;
		//unordered_map<int, int> values = unordered_map<int, int>();
		stack<int> prevLocations = stack<int>();
		for (int j = 0; j < k; j++)
		{
			srand48_r(time(NULL) + i, randBuffer + omp_get_thread_num());
			if (graph->nodesMap.find(nodeTarget) != graph->nodesMap.end())
			{
				#pragma omp atomic
				counts[nodeTarget]++;

				//if (values.find(nodeTarget) == values.end())
				//	values[nodeTarget] = 1;
				//else
				//	values[nodeTarget]++;
				drand48_r(randBuffer + omp_get_thread_num(), &value); // todo fix buffer location
				if (value > damping)
				{
					nodeTarget = getTailsNextLocation(nodeTarget, prevLocations, randBuffer + omp_get_thread_num(), backDampening, graph);
				}
				else
				{
					nodeTarget = getHeadsNextLocation(nodeTarget, prevLocations, randBuffer + omp_get_thread_num(), graph);
				}
			}
		}
		//for (auto it = values.begin(); it != values.end(); ++it)
		//{
		//	if ((*it).first < graph->max)
		//	{
		//		#pragma omp atomic
		//		counts[(*it).first] += (*it).second;
		//	}
		//}
	}
	totalWalks = myTotalWalks;
}

int PageRankEstimatorOMP::getHeadsNextLocation(int nodeTarget, stack<int> prevLocations, drand48_data* randBuffer, Graph* graph)
{
	double value;
	drand48_r(randBuffer, &value);
	int count = graph->nodes.size();
	prevLocations.push(nodeTarget);
	nodeTarget = graph->nodes[(((int)(count * value) + 1) % (count))];
	return nodeTarget;
}

int PageRankEstimatorOMP::getTailsNextLocation(int nodeTarget, stack<int> prevLocations, drand48_data* randBuffer, double backDampening, Graph* graph)
{
	double value;
	drand48_r(randBuffer, &value);
	int size = get<0>(graph->graph[nodeTarget]).size();
	int count = size;
	if (backDampening < 1.0)
		count += count*backDampening;
	else
		count += backDampening;
	if (count == 0)
		count = 1;
	int selected = (((int)(count * value)) % (count));
	
	if (selected >= size)
	{
		if (prevLocations.size() == 0)
		{
			return getHeadsNextLocation(nodeTarget, prevLocations, randBuffer, graph);
		}
		else
		{
			nodeTarget = prevLocations.top();
			prevLocations.pop();
		}
	}
	else
	{
		prevLocations.push(nodeTarget);
		nodeTarget = get<0>(graph->graph[nodeTarget])[selected]; //getHeadsNextLocation(nodeTarget, prevLocations, randBuffer);//get<0>(graph->graph[nodeTarget])[selected];
	}
	return nodeTarget;
}

tuple<int, int>* PageRankEstimatorOMP::getTop5()
{
	return getTop5(counts, countsSize);
}

void PageRankEstimatorOMP::print(int val)
{
	if (isHardDebug)
		cout << val << endl;
}

void PageRankEstimatorOMP::print(double val)
{
	if (isHardDebug)
		cout << val << endl;
}

void PageRankEstimatorOMP::print(string val)
{
	if (isHardDebug)
		cout << val << endl;
}

void PageRankEstimatorOMP::print(size_t val)
{
	if (isHardDebug)
		cout << val << endl;
}

tuple<int, int>* PageRankEstimatorOMP::getTop5(int* unordered, int size)
{
	tuple<int, int>* top5 = new tuple<int, int>[5]{ tuple<int,int>(-1,-1),tuple<int,int>(-1,-1),tuple<int,int>(-1,-1),tuple<int,int>(-1,-1),tuple<int,int>(-1,-1) };
	for (int i = 0; i < size; i++)
	{
		//for (int j = 0; j < 5; j++)
		//{
		//	if (unordered[i] >= get<1>(top5[i]))
		//	{
		//		int val = j;
		//		while (j < 4)
		//		{
		//			unordered[j + 1] = unordered[j];
		//			j++;
		//		}
		//		top5[val] = tuple<int, int>(i, unordered[i]);
		//		j++;
		//	}
		//}
		if (unordered[i] >= get<1>(top5[0]))
		{
			top5[4] = top5[3];
			top5[3] = top5[2];
			top5[2] = top5[1];
			top5[1] = top5[0];
			top5[0] = tuple<int, int>(i, unordered[i]);
		}
		else if (unordered[i] >= get<1>(top5[1]))
		{
			top5[4] = top5[3];
			top5[3] = top5[2];
			top5[2] = top5[1];
			top5[1] = tuple<int, int>(i, unordered[i]);
		}
		else if (unordered[i] >= get<1>(top5[2]))
		{
			top5[4] = top5[3];
			top5[3] = top5[2];
			top5[2] = tuple<int, int>(i, unordered[i]);
		}
		else if (unordered[i] >= get<1>(top5[3]))
		{
			top5[4] = top5[3];
			top5[3] = tuple<int, int>(i, unordered[i]);
		}
		else if (unordered[i] >= get<1>(top5[4]))
		{
			top5[4] = tuple<int, int>(i, unordered[i]);
		}
	}
	return top5;
}


