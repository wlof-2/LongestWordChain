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



int main(int argc, char *argv[])
{
	// Create a graph given in the above diagram.  Here vertex numbers are
	// 0, 1, 2, 3, 4, 5 with following mappings:
	// 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
	int length = 0;
	char *word[100000];
	// length表示单词的长度
	string file_name;
	file_name = argv[argc - 1];
	length = getWord(word, file_name);
	Graph g(length);
	Node_Path *dist = new Node_Path[length];
	//释放内存
	// 表示有三个参数，两个是输入的
	
	int s = 1;
	cout << "Following are longest distances from source vertex " << s << " \n";
	g.topologicalSort();
	g.longestPath(s, word, dist, true);
	cout << "nothing" << endl;
	for (int i = 0; i < length; i++) {
		delete word[i];
	}

	return 0;
}
