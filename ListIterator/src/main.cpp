#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include <iostream>
using namespace std;
#include <functional>
#include <algorithm>
#include <list>

template<class T> void print(const std::list<T>& list)
{
	for (auto& l : list)
	{
		std::cout << l << std::endl;
	}
}

template<class T, class Iterator, class CMP> void qsort(Iterator& left, Iterator& right, const CMP& cmp)
{
	if (left == right) return;
	Iterator ai = left,	aj = right;
	--aj;
	const T pivot = *left;
	for (;;) {
		while (cmp(*ai, pivot)) ++ai;
		while (cmp(pivot, *aj)) --aj;
		std::list<T>::iterator ak = aj;
		++ak;
		if (ai == aj) break;
		if (ai == ak) break;
		std::swap(*ai, *aj);
		++ai; --aj;
	}
	++aj;
	qsort<T>(left, ai, cmp);
	qsort<T>(aj, right, cmp);
}

template<class T, class CMP> void qsort(std::list<T>& list, const CMP& cmp)
{
	qsort<T>(list.begin(), list.end(), cmp);
}


void proc()
{
	std::list<int> list;

	list.push_back(1);
	list.push_back(3);
	list.push_back(2);
	list.push_back(5);
	list.push_back(4);

	print(list);

	qsort(list, std::greater<int>());

	print(list);

}
int main()
{

	// メモリリークチェック
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	proc();
	
	return 0;
}