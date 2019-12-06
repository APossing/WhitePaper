#include "PageRankEstimatorOMP.h"
#include <ctime>
bool isHardDebug = false;
PageRankEstimatorOMP::PageRankEstimatorOMP(Graph g)
{
	this->graph = g;
	countsSize = g.max;
	totalWalks = 0;
}

void PageRankEstimatorOMP::RunPageRankEstimator(int threads, int k, int damping, int backDampening)
{
	omp_set_dynamic(0);     // disable dynamic teams
	omp_set_num_threads(threads); // Use p threads for all consecutive parallel regions
	counts = new int[graph.max]{ 0 };
	cout << graph.nodes.size() << endl;

	drand48_data* randBuffer = new struct drand48_data[threads]();
	srand48((unsigned int)time(NULL));
#pragma omp parallel for schedule(static) reduction(+: totalWalks) 
	for (int i = 0; i < graph.nodes.size(); i++)
	{
		double value;
		totalWalks++;
		if (i % 100 == 0)
			cout << i << endl;
		int nodeTarget = i;
		unordered_map<int, int> values = unordered_map<int, int>();
		stack<int> prevLocations = stack<int>();
		for (int j = 0; j < k; j++)
		{
			print(nodeTarget);
			srand48_r(time(NULL) + i, randBuffer + omp_get_thread_num());
			//print(1.1);
			//print(2.1);
			if (graph.nodesMap.find(nodeTarget) != graph.nodesMap.end())
			{
				if (values.find(nodeTarget) == values.end())
					values[nodeTarget] = 1;
				else
					values[nodeTarget]++;
				print(3.1);
				drand48_r(randBuffer + omp_get_thread_num(), &value); // todo fix buffer location
				print(4.1);
				if (value > damping)
				{
					nodeTarget = getTailsNextLocation(nodeTarget, prevLocations, randBuffer + omp_get_thread_num());
					print(5.11);
					print(nodeTarget);
				}
				else
				{
					nodeTarget = getHeadsNextLocation(nodeTarget, prevLocations, randBuffer + omp_get_thread_num());
					print(6.11);
					print(nodeTarget);
				}
			}
		}
		print(13);
		//cout << 5.0 << endl;
		if (values.size() > 0)
		{
			for (auto it = values.begin(); it != values.end(); ++it)
			{
				//cout <<(*it).first << endl;
				if ((*it).first < graph.max)
				{
#pragma omp atomic
					counts[(*it).first] += (*it).second;
				}
			}
		}
		//cout << 6.0 << endl;
	}
}

int PageRankEstimatorOMP::getHeadsNextLocation(int nodeTarget, stack<int> prevLocations, drand48_data* randBuffer)
{
	double value;
	print(9);
	drand48_r(randBuffer, &value);
	print(10);
	//heads
	int count = graph.nodes.size();
	print(11);
	prevLocations.push(nodeTarget);
	nodeTarget = graph.nodes[(((int)(count * value) + 1) % (count))];
	print(12);
	return nodeTarget;
}

int PageRankEstimatorOMP::getTailsNextLocation(int nodeTarget, stack<int> prevLocations, drand48_data* randBuffer)
{
	double value;
	drand48_r(randBuffer, &value);
	//tails
	int count = get<0>(graph.graph[nodeTarget]).size() +1;
	int selected = (((int)(count * value)) % (count));
	print(7.0);
	if (selected >= get<0>(graph.graph[nodeTarget]).size()-1)
	{
		if (prevLocations.size() == 0)
		{
			// heads statement
			return getHeadsNextLocation(nodeTarget, prevLocations, randBuffer);
		}
		else
		{
			nodeTarget = prevLocations.top();
			prevLocations.pop();
		}
	}
	else
	{
		print(8);
		print(selected);
		prevLocations.push(nodeTarget);
		print(8.1);
		nodeTarget = get<0>(graph.graph[nodeTarget])[selected]; //getHeadsNextLocation(nodeTarget, prevLocations, randBuffer);//get<0>(graph.graph[nodeTarget])[selected];
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


