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


int main()
{
	// Create a graph given in the above diagram.  Here vertex numbers are
	// 0, 1, 2, 3, 4, 5 with following mappings:
	// 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
	Graph g(6);
	g.addEdge(0, 1, 5);
	g.addEdge(0, 2, 3);
	g.addEdge(1, 3, 6);
	g.addEdge(1, 2, 2);
	g.addEdge(2, 4, 4);
	g.addEdge(2, 5, 2);
	g.addEdge(2, 3, 7);
	g.addEdge(3, 5, 1);
	g.addEdge(3, 4, -1);
	g.addEdge(4, 5, -2);

	int s = 1;
	cout << "Following are longest distances from source vertex " << s << " \n";
	g.topologicalSort();
	g.longestPath(s);
	cout << "nothing" << endl;
	return 0;
}
