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
void Graph::longestPath(int start, char* word[], Node_Path *dist, bool begin_end)
{
	//Node_Path *dist = new Node_Path[V];
	//初始化到所有顶点的距离为负无穷
	//到源点的距离为0
	for (int i = 0; i < V; i++)
	{
		if (E_degree[i] == 0)
		{
			dist[i].end_length = strlen(word[i]);
		}
		else
		{
			dist[i].end_length = NINF;
		}
	}
	dist[start].end_length = strlen(word[start]);

	// 处理拓扑序列中的点
	while (Stack.empty() == false)
	{
		//取出拓扑序列中的第一个点
		int u = Stack.back();
		Stack.pop_back();

		// 更新到所有邻接点的距离
		list<AdjListNode>::iterator i;
		if (dist[u].end_length != NINF)
		{
			for (i = adj[u].begin(); i != adj[u].end(); ++i)
			{
				if (begin_end)
				{
					//从某个点作为开头开始找
					if (dist[i->getV()].end_length < dist[u].end_length + i->getWeight() && \
						(dist[i->getV()].Path.front == start || u == start))
					{
						dist[i->getV()].end_length = dist[u].end_length + i->getWeight();
						dist[i->getV()].Path = dist[u].Path;
						dist[i->getV()].Path.push_back(u);
					}
				}
				else if (dist[i->getV()].end_length < dist[u].end_length + i->getWeight())
				{
					dist[i->getV()].end_length = dist[u].end_length + i->getWeight();
					dist[i->getV()].Path = dist[u].Path;
					dist[i->getV()].Path.push_back(u);
				}
			}
				
		}
	}
	return;
}

void Graph::Every_Path(int chose, char* word[], Node_Path *dist, char end_letter, char start_letter)
{
	vector<int> R_Path;
	int max = -1, end_point = 0, start = 0;
	vector<int> start_array;
	for (int i = 0; i < V; i++)
	{
		if (word[i][0] == start_letter)
		{
			start_array.push_back(i);
		}
	}
	if (chose == 1)
	{
		//表示直接找最长单词链，带权的
		longestPath(0, word, dist, false);
		for (int i = 0; i < V; i++)
		{
			if (dist[i].end_length > max)
			{
				max = dist[i].end_length;
				end_point = i;
				R_Path = dist[i].Path;
			}	
		}
	}
	else if (chose == 2)
	{
		 //确定开头的
		vector<int>::iterator j;
		for (j = start_array.begin(); j != start_array.end(); ++j)
		{
			longestPath(*j, word, dist, true);
			for (int i = start; i < V; i++)
			{
				if (dist[i].end_length > max)
				{
					max = dist[i].end_length;
					end_point = i;
					R_Path = dist[i].Path;
				}
			}
		}
	}
	else if(chose == 3) 
	{
		//确定结尾的
		longestPath(0, word, dist, false);
		for (int i = 0; i < V; i++)
		{
			if (dist[i].end_length > max && word[i][strlen(word[i]) - 1] == end_letter)
			{
				max = dist[i].end_length;
				end_point = i;
			}
		}

	}
	else if (chose == 4)
	{
		//确定开头和结尾的
		vector<int>::iterator j;
		for (j = start_array.begin(); j != start_array.end(); ++j)
		{
			longestPath(*j, word, dist, true);
			for (int i = start; i < V; i++)
			{
				if (dist[i].end_length > max && word[i][strlen(word[i]) - 1] == end_letter)
				{
					max = dist[i].end_length;
					end_point = i;
					R_Path = dist[i].Path;
				}
			}
		}
	}
}

void Get_num(char* word[], int len, Graph *map_node, bool Weight)
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
				E_degree[j] += 1;
				if(Weight)
					map_node->addEdge(i, j, strlen(word[j]));
				else
					map_node->addEdge(i, j, 1);
			}
		}
	}
	return;
}

