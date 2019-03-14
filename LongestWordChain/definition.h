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
	void longestPath(int start, char* word[], bool begin_end, bool Weight);
	void Every_Path(int chose, char* word[], char end_letter, char start_letter, bool Weight);
	void Get_num(char* word[], int len, bool Weight);
};



Graph *map;
Node_Path *dist;
vector<int> R_Path;

void paraAnalysis(int argc, char * argv[], char opt[][5], int & flag_wc, char & head, char & tail, bool & para_loop, string &filePath);
int getWord(char *words[], string path);
int gen_chain_word(char* words[], int lens, char* result[], char head, char tail, bool enable_loop);
int gen_chain_char(char* words[], int lens, char* result[], char head, char tail, bool enable_loop);

constexpr auto ALPHA_LENGTH = 26;			//开头字母种类;

/*静态全局变量，参数表*/
static char opt[5][5] = {
	"-w", "-c", "-r", "-h", "-t"
};


enum
{
	_w,
	_c,
	_r,
	_h,
	_t
};

