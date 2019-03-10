// LongestWordChain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
// A C++ program to print topological sorting of a DAG
#include "iostream"
#include "list"
#include "stack"
#include <limits.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include "definition.h"
#define NINF INT_MIN
using namespace std;

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

	// prints a Topological Sort of the complete graph
	void longestPath(int s);
	void topologicalSort();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<AdjListNode>[V];
}

void Graph::addEdge(int u, int v, int weight)
{
	AdjListNode new_node(v, weight);    // 新建一个实例 new_node
	adj[u].push_back(new_node); // Add w to v’s list.
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[])
{
	// Mark the current node as visited.
	int last_v = 0;
	visited[v] = true;
	// Recur for all the vertices adjacent to this vertex
	list<AdjListNode>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		if (!visited[i->getV()])
		{
			topologicalSortUtil(i->getV(), visited);
		}
		else
		{
			if (find(Stack.begin(), Stack.end(), i->getV) != Stack.end())
			{
				// 说明，该点已经访问过，但是不在Stack中，所以出现环
				return;
			}
		}
	}
	// Push current vertex to stack which stores result
	this->Stack.push_back(v);
}


void Graph::topologicalSort()
{
	// stack<int> Stack;

	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to store Topological
	// Sort starting from all vertices one by one
	for (int i = 0; i < V; i++)
	{
		if (visited[i] == false)
			topologicalSortUtil(i, visited);
	}
}


// 根据传入的顶点，求出到到其它点的最长路径. longestPath使用了
// topologicalSortUtil() 方法获得顶点的拓扑序。
void Graph::longestPath(int s)
{
	int *dist = (int *)malloc(sizeof(int)*V);
	//初始化到所有顶点的距离为负无穷
	//到源点的距离为0
	for (int i = 0; i < V; i++)
		dist[i] = NINF;
	dist[s] = 0;

	// 处理拓扑序列中的点
	while (Stack.empty() == false)
	{
		//取出拓扑序列中的第一个点
		int u = Stack.back();
		Stack.pop_back();

		// 更新到所有邻接点的距离
		list<AdjListNode>::iterator i;
		if (dist[u] != NINF)
		{
			for (i = adj[u].begin(); i != adj[u].end(); ++i)
				if (dist[i->getV()] < dist[u] + i->getWeight())
					dist[i->getV()] = dist[u] + i->getWeight();
		}
	}

	// 打印最长路径
	for (int i = 0; i < V; i++)
		(dist[i] == NINF) ? cout << "INF " : cout << dist[i] << " ";
}

void Get_num(char* word[], int len, Graph *map_node)
{
	int length = 0;
	char word_end;
	for (int i = 0; i < len; i++)
	{
		length = strlen(word[i]);
		word_end = word[i][length - 1];
		for (int j = i; j < len; j++)
		{
			if (word_end == word[j][0])
			{
				map_node->addEdge(i, j, strlen(word[j]));
			}
		}
	}
	return;
}

int main(int argc, char *argv[])
{
	// Create a graph given in the above diagram.  Here vertex numbers are
	// 0, 1, 2, 3, 4, 5 with following mappings:
	// 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
	int len;
	char file_name[90] = { 0 };
	char chose_way = 0;
	Graph g(len);
	// 表示有三个参数，两个是输入的
	if (argc == 3)
	{
		chose_way = argv[1][1];
		// 表示是按照单词数最多还是字母数最多
		strcpy(file_name, argv[2]);
	}
	else if(argc == 4)
	{

	}
	else if(argc == 5)
	{
		// 表示在命令行中使用 -h 参数加字母的形式，指定单词链的首字母，
		// 例如 > Wordlist.exe -h e -w absolute_path_of_word_list
		chose_way = argv[3][1];
		strcpy(file_name, argv[4]);
	}
	else if (argc == 7)
	{

	}

	int s = 1;
	cout << "Following are longest distances from source vertex " << s << " \n";
	g.topologicalSort();
	g.longestPath(s);
	cout << "nothing" << endl;
	return 0;
}
