#include "PageRankEstimatorOMP.h"
#include <ctime>
bool isHardDebug = true;
PageRankEstimatorOMP::PageRankEstimatorOMP(Graph g)
{
	this->graph = g;
	counts = new int[g.max]{0};
	countsSize = g.max;
	totalWalks = 0;
}

void PageRankEstimatorOMP::RunPageRankEstimator(int threads, int k, int damping)
{
	omp_set_dynamic(0);     // disable dynamic teams
	omp_set_num_threads(threads); // Use p threads for all consecutive parallel regions
	
	
	drand48_data* randBuffer = new struct drand48_data[threads]();
	srand48((unsigned int)time(NULL));
	double value;
	double value2;
	#pragma omp parallel for schedule(static) reduction(+: totalWalks)
	for (int i = 0; i < graph.nodes.size(); i++)
	{
		totalWalks++;
		if (i % 100 == 0)
			cout << i << endl;
		int nodeTarget = i;
		unordered_map<int, int> values = unordered_map<int, int>();
		stack<int> prevLocations = stack<int>();
		for (int j = 0; j < k; j++)
		{
			srand48_r(time(NULL) + i, randBuffer + omp_get_thread_num());
			print(1);
			if (values.find(nodeTarget) == values.end())
				values[nodeTarget] = 1;
			else
				values[nodeTarget]++;
			print(2);
			if (graph.nodesMap.find(nodeTarget) != graph.nodesMap.end())
			{
				print(3);
				drand48_r(randBuffer + omp_get_thread_num(), &value); // todo fix buffer location
				print(4);
				if (value > damping)
				{
					print(5);
					drand48_r(randBuffer + omp_get_thread_num(), &value2);
					print(6);
					//tails
					int count = get<1>(graph.graph[nodeTarget]).size() + 1;
					int selected = (((int)(count * value2)) % (count));
					print(7.0);
					if (selected >= get<0>(graph.graph[nodeTarget]).size())
					{
						if (prevLocations.size() == 0)
						{
							// heads statement
							print(9);
							drand48_r(randBuffer + omp_get_thread_num(), &value2);
							print(10);
							//heads
							int count = graph.nodes.size();
							print(11);
							prevLocations.push(nodeTarget);
							nodeTarget = graph.nodes[(((int)(count * value2) + 1) % (count))];
							print(12);
							//heads statement
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
						print(get<0>(graph.graph[nodeTarget]).size());
						print(8.2);
						nodeTarget = get<0>(graph.graph[nodeTarget])[selected];
					}
				}
				else
				{
					cout << 9 << endl;
					drand48_r(randBuffer, &value2);
					print(10);
					//heads
					int count = graph.nodes.size();
					print(11);
					prevLocations.push(nodeTarget);
					nodeTarget = graph.nodes[(((int)(count * value2) + 1) % (count))];
					print(12);
				}
			}
		}
		print(13);
		for (auto it = values.begin(); it != values.end(); ++it)
		{
			print((*it).first);
			#pragma omp atomic
			counts[(*it).first] += (*it).second;
		}
	}
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
	tuple<int, int>* top5 = new tuple<int,int>[5] {tuple<int,int>(-1,-1),tuple<int,int>(-1,-1),tuple<int,int>(-1,-1),tuple<int,int>(-1,-1),tuple<int,int>(-1,-1) };
	for(int i = 0; i < size; i++)
	{
		if (unordered[i] >= get<1>(top5[0]))
		{
			top5[4] = top5[3];
			top5[3] = top5[2];
			top5[2] = top5[1];
			top5[1] = top5[0];
			top5[0] = tuple<int,int>(i,unordered[i]);
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


