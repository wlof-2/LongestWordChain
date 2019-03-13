#pragma once
#include <vector>
#include <list>
#include <string>
int para[10];
int E_degree[100000];
using namespace std;

class Node_Path
{
public:
	int end_length;
	vector<int> Path;

private:

};

class AdjListNode
{
	int v;
	int weight;

public:
	AdjListNode(int _v, int _w) { v = _v;  weight = _w; }
	int getV() { return v; }
	int getWeight() { return weight; }
};

// Class to represent a graph
class Graph
{
private:
	int V; // No. of vertices'
	vector<int> Stack;
	// Pointer to an array containing adjacency listsList
	list<AdjListNode> *adj;

	// A function used by topologicalSort
	void topologicalSortUtil(int v, bool visited[]);
public:
	Graph(int V); // Constructor

	// function to add an edge to graph
	void addEdge(int u, int v, int weight);
	int getv() { return V; }
	// prints a Topological Sort of the complete graph
	void topologicalSort();
	void longestPath(int s, char* word[], Node_Path *dist, bool begin_end);
	void Every_Path(int chose, char* word[], Node_Path *dist, char end_letter, char start_letter);
	void Get_num(char* word[], int len, bool Weight);
};

int  getWord(char *words[], string path);
void getInput(int argc, char *argv[], Graph *map, char* word[], int length, Node_Path *dist);
int isOpt(char option[], int argc, char *argv[]);
Node_Path *dist;
vector<int> R_Path;