#ifndef hello
#define hello
#include "graph.h"

void Graph::initGraph(int size)
{
	this->size = size;
	this->max = 0;
	this->nodesMap = unordered_set<int>();
	this->links = list<tuple<int, int>>(links);
	graph = unordered_map<int, tuple<vector<int>, unordered_set<int>>>();
}

void Graph::toggleGraphLocation(int row, int column)
{
	if (graph.find(row) == graph.end())
		graph[row] = tuple < vector<int>, unordered_set<int>>();
	if (get<1>(graph[row]).find(column) != get<1>(graph[row]).end())
		return;
	get<1>(graph[row]).insert(column);
	get<0>(graph[row]).push_back(column);

	if (graph.find(column) == graph.end())
		graph[column] = tuple < vector<int>, unordered_set<int>>();
}

int Graph::getMaxOutgoingEdgesFromNode()
{
	unsigned int max = 0;
	int maxId = -1;
	for (int x: nodes)
	{
		if (get<0>(graph[x]).size() > max)
		{
			max = get<0>(graph[x]).size();
			maxId = x;
		}
	}
	return maxId;
}

bool Graph::IsEdgeInGraph(int from, int to)
{
	return graph.find(from) != graph.end() && get<1>(graph[from]).find(to) != get<1>(graph[from]).end();
}

bool Graph::nodeInGraph(int from)
{
	return graph.find(from) != graph.end();
}

void Graph::loadWebGoogle(string fileName)
{
	ifstream inFile;
	inFile.open(fileName, std::ios::out);
	string line;
	getline(inFile, line);
	getline(inFile, line);
	getline(inFile, line);
	int size = 0;
	char* cstr = new char[line.length() + 1];
	strcpy(cstr, line.c_str());
	char* pch = strtok(cstr, " ");
	int i = 0;
	while (pch != NULL)
	{
		if (i++ == 2)
		{
			size = stoi(pch);
		}
		pch = strtok(NULL, " ,.-");
	}


	initGraph(size);
	getline(inFile, line);
	int words[2];
	int k = 0;
	while (getline(inFile, line))
	{
		if (k++ % 10000 == 0)
			cout << k << endl;
		int j = 0;
		string word;
		for (auto x : line)
		{
			if (x == '\t')
			{
				words[j] = stoi(word);
				word = "";
			}
			else
			{
				word += x;
			}
		}
		words[1] = stoi(word);

		if (nodesMap.find(words[1]) == nodesMap.end())
		{
			nodesMap.insert(words[1]);
			this->nodes.push_back(words[1]);
			if (words[1] > this->max)
				this->max = words[1];
		}
		if (nodesMap.find(words[0]) == nodesMap.end())
		{
			nodesMap.insert(words[0]);
			this->nodes.push_back(words[0]);
			if (words[0] > this->max)
				this->max = words[0];
		}

		toggleGraphLocation(words[0], words[1]);
	}

	inFile.close();
}

void Graph::loadwebNotreDame(string fileName)
{
	ifstream inFile;
	inFile.open(fileName, std::ios::out);
	string line;
	getline(inFile, line);
	getline(inFile, line);
	getline(inFile, line);
	int size = 0;
	char* cstr = new char[line.length() + 1];
	strcpy(cstr, line.c_str());
	char* pch = strtok(cstr, " ");
	int i = 0;
	while (pch != NULL)
	{
		if (i++ == 2)
		{
			size = stoi(pch);
		}
		pch = strtok(NULL, " ,.-");
	}


	initGraph(size);
	getline(inFile, line);
	int words[2];
	int k = 0;
	while (getline(inFile, line))
	{
		if (k++ % 10000 == 0)
			cout << k << endl;
		int j = 0;
		string word;
		for (auto x : line)
		{
			if (x == '\t')
			{
				words[j] = stoi(word);
				word = "";
			}
			else
			{
				word += x;
			}
		}
		words[1] = stoi(word);

		if (nodesMap.find(words[1]) == nodesMap.end())
		{
			nodesMap.insert(words[1]);
			this->nodes.push_back(words[1]);
			if (words[1] > this->max)
				this->max = words[1];
		}
		if (nodesMap.find(words[0]) == nodesMap.end())
		{
			nodesMap.insert(words[0]);
			this->nodes.push_back(words[0]);
			if (words[0] > this->max)
				this->max = words[0];
		}

		toggleGraphLocation(words[0], words[1]);
	}

	inFile.close();
}

void Graph::processLinks(int threads)
{
	for(auto x: links)
	{
		
	}
}

Graph::Graph(string fileName, FileType fileType)
{
	fileName = "Data/" + fileName;

	switch (fileType)
	{
	case webGoogle:
		loadWebGoogle(fileName);
		break;
	case webBerkstan:
		break;
	case webNotredame:
		loadwebNotreDame(fileName);
		break;
	case facebookCombined:
		break;
	default:
		break;
	}
}

Graph::Graph(FileType fileType)
{
	switch (fileType)
	{
	case webGoogle:
		loadWebGoogle("Data/web-Google_sorted.txt");
		break;
	case webBerkstan:
		break;
	case webNotredame:
		loadwebNotreDame("Data/web-NotreDame_sorted.txt");
		break;
	case facebookCombined:
		break;
	default:
		break;
	}
}

Graph::Graph(const Graph& g)
{
	this->graph = g.graph;
	this->nodes = g.nodes;
	this->nodesMap = g.nodesMap;
	this->size = g.size;
	this->max = g.max;
}

Graph::Graph()
{
	initGraph(0);
}

#endif
