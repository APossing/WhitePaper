#pragma once
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
using namespace std;
enum FileType { webGoogle, webBerkstan, webNotredame, facebookCombined };

class Graph
{
	// Access specifier 
public:
	Graph(string fileName, FileType fileType);
	explicit Graph(FileType fileType);
	Graph(const Graph &g);
	Graph();
	int max;
	vector<int> nodes;
	unordered_set<int> nodesMap;
	list<tuple<int, int>> links;
	bool IsEdgeInGraph(int from, int to);
	bool nodeInGraph(int from);
	unordered_map<int, tuple<vector<int>, unordered_set<int> >> graph;
	int size;
	void toggleGraphLocation(int row, int column);
	int getMaxOutgoingEdgesFromNode();
private:
	void initGraph(int size);
	void loadWebGoogle(string fileName);
	void loadwebNotreDame(string fileName);
	void processLinks(int threads);
};