#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LongestWordChain/definition.h"
#include <string.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Longest_Test
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			Graph *test_map = new Graph(10);
			char *word[100000];
			char test1[1000] = "nshdkaw";
			char test2[1000] = "dhakjefba";
			char test3[1000] = "wfhksdc";
			char test4[1000] = "hksdj";
			char test5[1000] = "wueosnfsjefd";

			for (int i = 0; i < 50; i++)
			{
				word[i] = new char[20];
			}
			word[0] = test1;
			word[1] = test2;
			word[2] = test3;
			word[3] = test4;
			word[4] = test5;
			test_map->Every_Path(1, word, 0, 0, false);
			int big = R_Path.size();
			Assert::AreEqual(big, 3);
		}
	};
}