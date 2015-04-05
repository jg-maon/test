#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include "List.h"
#include <iostream>
using namespace std;

template<class T> void print(const ns_Exercise3::List<T>& l)
{
	for (auto n = l.first(); n != l.end(); n = n->next())
	{
		cout << *n->val() << endl;
	}
}
#include<list>
void proc()
{
	ns_Exercise3::List<int> l;

	//l.push_back(1);
	//l.push_back(5);
	//l.push_back(3);
	//l.push_back(2);
	//l.push_back(4);

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	//auto it = l.begin();
	//l.InsertBack(it, 30);	// [1],30,2,3,4,5
	//it++;					// 1,[30],2,3,4,5
	//l.erase(it);			// 1,[2],3,4,5
	//*it = 20;				// 1,[20],3,4,5
	//++it;					// 1,20,[3],4,5
	//l.erase(it);			// 1,20,[4],5


	print(l);

	cout << "--------------" << endl;

	l.QSort();
	print(l);
}
int main()
{

	// メモリリークチェック
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	proc();
	
	return 0;
}