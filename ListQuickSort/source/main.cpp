#include <crtdbg.h>
#include "List.h"
#include <functional>
#include <iostream>

using namespace ex01_DataStructure::chapter02;

template<class T>
void print(const List<T>& list, bool reverse = false)
{
	for (auto it = list.GetBegin(); it != list.GetEnd(); ++it)
	{
		printf("%d\n", *it);
	}
	if (reverse)
	{
		for (auto it = --list.GetEnd(); it != list.GetBegin(); --it)
		{
			printf("%d\n", *it);
		}
		printf("%d\n", *list.GetBegin());
	}
}
#include <list>

template<class T> void print(const std::list<T>& list)
{
	for (auto& l : list)
	{
		std::cout << l << " ";
	}
	std::cout << std::endl;
}
std::list<int>* g_list;
int funcCnt = 0;
template<class T, class Iterator, class CMP> void qsort(Iterator& left, Iterator& right, const CMP& cmp)
{
	if (left == right) return;
	int funcNo = ++funcCnt;
	Iterator ai = left, aj = right;
	--aj;
	printf("\n");
	for (auto it = g_list->begin(); it != g_list->end(); ++it)
	{
		if (it == left)
			printf("|");
		printf("%d", *it);
		if (it == right)
			printf("|");
		printf(" ");
	}
	if (right == g_list->end())
		printf("|");

	printf("\n");
	if (0)
	{
		Iterator lit = ai, rit = aj;
		Iterator lp, ln, rp, rn;
		lp = ln = lit;
		rp = rn = rit;
		int ilp, iln, irp, irn;
		if (lit != g_list->begin())
			ilp = *(--lp);
		else
			ilp = -1;
		if (rit != g_list->begin())
			irp = *(--rp);
		else
			irp = -1;
		if (lit != --g_list->end())
			iln = *(++ln);
		else
			iln = -1;
		if (rit != --g_list->end())
			irn = *(++rn);
		else
			irn = -1;
		printf("left:%d, right:%d\n"
			   "%d,%d,%d | %d,%d,%d\n",
			   *lit, *rit,
			   ilp, *lit, iln, irp, *rit, irn);
		print(*g_list);

	}
	const T pivot = *left;
	printf("pivot:%d\n", pivot);
	for (;;) {
		while (cmp(*ai, pivot)) ++ai;
		while (cmp(pivot, *aj)) --aj;
		std::list<T>::iterator ak = aj;
		++ak;
		if (ai == aj) break;
		if (ai == ak) break;
		printf("%d<->%d\n", *ai, *aj);
		std::swap(*ai, *aj);
		print(*g_list);
		++ai; --aj;
	}
	++aj;
	printf("左半分%d\n", funcNo);
	qsort<T>(left, ai, cmp);
	printf("右半分%d\n", funcNo);
	qsort<T>(aj, right, cmp);
}

template<class T, class CMP> void qsort(std::list<T>& list, const CMP& cmp)
{
	g_list = &list;
	qsort<T>(list.begin(), list.end(), cmp);
}

struct Data
{
	int i;
	Data() :i(-1){}
	explicit Data(int i) :i(i){}
	operator int(){ return i; }
	operator int()const{ return i; }
	//Data(const Data&) = delete;
	Data& operator=(const Data&) = delete;
};
bool less(const int& right, const int& left)
{
	return right < left;
}
bool greater(const int& right, const int& left)
{
	return right > left;
}
#include "random.h"
#include <ctime>
#include <cstdlib>
void func()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	List<int> list;
	std::list<int> stdlist;
	//*
	for (int i = 0; i < 10; ++i)
	{
		//int r = rand() % 100;
		int r = ns_Random::Random::GetInstance()->GetRandom(0, 100);
		stdlist.push_back(r);
		list.PushBack(r);
	}
	//*/
	//*
	//int arr[] = {
	//	0, 4, 1, 3, 6, 
	//	1,
	//	5,
	//};
	//for (auto i : arr)
	//{
	//	stdlist.push_back(i);
	//	list.PushBack(Data(i));
	//}
	
	//*/
	//print(stdlist);
	//printf("\n---------------------\n\n");
	//qsort(stdlist, std::less<int>());
	//print(stdlist);

	print(list);
	printf("\n---------------------\n\n");




	list.QSort(greater);
	print(list);

	stdlist.sort(std::greater<int>());

	auto stdit = stdlist.begin();
	for (auto it = list.GetBegin(); it != list.GetEnd(); ++it, ++stdit)
	{
		if (*it != *stdit)
		{
			std::cerr << "error." << *it << " != " << *stdit << "\n";
		}
	}
	if (stdit == stdlist.end())
	{
		std::cout << "OK." << std::endl;
	}

	return;

}
#include <conio.h>

int main()
{
	// メモリリークチェック
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	func();
	std::cout << "\nend." << std::endl;
	_getch();
	return 0;
}