#include "definition.h"
#include "pch.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

static char opt[5][5] = {
	"-w", "-c", "-r", "-h", "-t"
};

int getWord(char *words[], string path)
{
	ifstream fin;				//open wordlist file;
	fin.open(path);
	if (!fin.is_open())
	{
		cout << "can't open the file" << endl;
	}

	char word[1000];
	char ch;
	int lens = 0;
	int k = 0;
	while (fin.get(ch))
	{
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		{
			if (ch >= 'A' && ch <= 'Z') {
				ch = ch - 'A' + 'a';
			}
			word[k] = ch;
			k++;
		}
		else if (k != 0)
		{
			words[lens] = new char[k + 1];
			for (int i = 0; i < k; i++) {
				words[lens][i] = word[i];
			}
			words[lens][k] = '\0';
			lens++;
			k = 0;
		}
	}
	fin.close();
	return lens;
}

void getInput(int argc, char *argv[]) 
{
	if (isOpt(opt[0], argc, argv))				//parameter "-w"
	{
		if (isOpt(opt[1], argc, argv))
		{
			cout << "parameter error: -w and -c can't occur simultaneously" << endl;
			return;
		}
		if (isOpt(opt[2], argc, argv))			//parameter "-r"
		{
			if (isOpt(opt[3], argc, argv))	    //parameter "-h"
			{
				string head;
				head = argv[isOpt(opt[3], argc, argv) + 1];
				if (isOpt(opt[4], argc, argv))	//parameter "-t"
				{
					string tail;
					tail = argv[isOpt(opt[4], argc, argv) + 1];
					//parameter "-w" "-r" "-h" "-t"
				}
				else
				{
					//parameter "-w" "-r" "-h"
				}
			}
			else if (opt[4], argc, argv)       //parameter "-t"
			{
				string tail;
				tail = argv[isOpt(opt[4], argc, argv) + 1];
				//parameter "-w" "-r" "-t"
			}
			else
			{
				//parameter "-w" "-r"
			}
		}
		else									//
		{
			//parameter "-w" 
		}
	}
	else if (isOpt(opt[1], argc, argv))			//parameter "-c"
	{
		if (isOpt(opt[2], argc, argv))			//parameter "-r"
		{
			if (isOpt(opt[3], argc, argv))	    //parameter "-h"
			{
				string head;
				head = argv[isOpt(opt[3], argc, argv) + 1];
				if (isOpt(opt[4], argc, argv))	//parameter "-t"
				{
					string tail;
					tail = argv[isOpt(opt[4], argc, argv) + 1];
					//parameter "-c" "-r" "-h" "-t"
				}
				else
				{
					//parameter "-c" "-r" "-h"
				}
			}
			else if (opt[4], argc, argv)       //parameter "-t"
			{
				string tail;
				tail = argv[isOpt(opt[4], argc, argv) + 1];
				//parameter "-c" "-r" "-t"
			}
			else
			{
				//parameter "-c" "-r"
			}
		}
	}
	else {
		cout << "absence parameter -w or -c" << endl;
	}
}

/*判断某个参数是否存在,，若存在，返回这个操作数在argv中的位置，否则，返回0*/
int isOpt(char option[], int argc, char *argv[]) 
{
	int k = 0;
	int j = 0;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(option, argv[i]) == 0)
		{
			k++;
			j = i;
		}
	}
	if (k <= 1)
	{
		return j;
	}
	else
	{
		cout << "parameter error!" << endl;
		return 0;
	}
}