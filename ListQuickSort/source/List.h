#ifndef __INCLUDED_LIST_H__
#define __INCLUDED_LIST_H__
#include <cstdio>



namespace ex01_DataStructure
{
	namespace chapter02
	{
		template<class T>
		class List;
	}
}

namespace ex01_DataStructure
{
	namespace chapter02
	{
		template<class T>
		class List
		{
		public:
			struct LIST_NODE
			{
				T			data;		//!< データ
				LIST_NODE*	pPrev;		//!< 前要素
				LIST_NODE*	pNext;		//!< 次要素
				LIST_NODE()
					: data()
					, pPrev(nullptr)
					, pNext(nullptr)
				{}
				LIST_NODE(const T& data, LIST_NODE* pPrev, LIST_NODE* pNext)
					: data(data)
					, pPrev(pPrev)
					, pNext(pNext)
				{}
					
			};
			class Iterator;
			class ConstIterator;
		public:
			List()
				: m_pFirst(nullptr)
				, m_pLast(nullptr)
				, m_dummy(T(),m_pLast,nullptr)
				, m_size(0)
			{}
			List(const List<T>& right)
				: m_pFirst(nullptr)
				, m_pLast(nullptr)
				, m_dummy(T(),m_pLast, nullptr)
				, m_size(0)
			{
				Clear();
				for (auto it = right.GetBegin(); it != right.GetEnd(); ++it)
				{
					PushBack(*it);
				}
			}
			virtual ~List()
			{
				Clear();
			}

			List<T>& operator = (const List<T>& right)
			{
				Clear();
				for (auto it = right.GetBegin(); it != right.GetEnd(); ++it)
				{
					PushBack(*it);
				}
				return *this;
			}

			size_t GetSize()const
			{
				return m_size;
			}

			void Clear()
			{
				if (m_pFirst && m_pLast)
				{
					for (LIST_NODE* n = m_pFirst; n != &m_dummy; n = _Erase(n));
				}
			}

			void PushBack(const T& data)
			{
				_InsertFront(&m_dummy, data);
			}

			void Erase(const Iterator& pos)
			{
				_Erase(pos.m_pNode);
			}
			
			void Insert(const Iterator& pos)
			{
				if (pos.m_pNode != &m_dummy)
				{
					_InsertFront(pos.m_pNode);
				}
			}

			Iterator GetBegin()
			{
				return Iterator(m_pFirst, this);
			}
			ConstIterator GetBegin()const
			{
				return ConstIterator(m_pFirst, this);
			}

			Iterator GetEnd()
			{
				return Iterator(&m_dummy, this);
			}
			ConstIterator GetEnd() const
			{
				return ConstIterator(&m_dummy, this);
			}


			template<class CMP>
			void QSort(CMP cmp);

		private:
			// 指定要素の前に挿入
			LIST_NODE* _InsertFront(LIST_NODE* pNode, const T& data)
			{
				LIST_NODE *ins;
				if (m_size)
				{
					// 末尾追加
					ins = new LIST_NODE(data, pNode->pPrev, pNode);
					if (!ins)
					{
						return pNode;
					}
					pNode->pPrev->pNext = ins;
					pNode->pPrev = ins;
				}
				else
				{
					// 最初の要素
					ins = new LIST_NODE(data, nullptr, &m_dummy);
					if (!ins)
					{
						return pNode;
					}
					
					m_pFirst = ins;

				}

				// 先頭要素
				if (pNode == m_pFirst)
				{
					m_pFirst = ins;
				}
				// 末尾要素
				if (pNode == &m_dummy)
				{
					m_dummy.pPrev = m_pLast = ins;
				}

				++m_size;

				return ins;

			}

			// 指定ノードの削除
			//! @return 指定ノードの次ノード
			LIST_NODE* _Erase(LIST_NODE* pNode)
			{
				if (pNode == &m_dummy)
				{
					return pNode;
				}

				// 前要素との連結
				if (pNode != m_pFirst)
				{
					pNode->pPrev->pNext = pNode->pNext;
				}
				else
				{
					m_pFirst = pNode->pNext;
				}

				// 後ろ要素との連結
				pNode->pNext->pPrev = pNode->pPrev;
				if (pNode == m_pLast)
				{
					m_dummy.pPrev = m_pLast = pNode->pPrev;
				}

				LIST_NODE* next = pNode->pNext;
				delete pNode;
				pNode = nullptr;


				--m_size;

				return next;
			}


		public:
			class Iterator
			{
				friend class List;
			public:
				Iterator()
					: m_pNode(nullptr)
					, m_pList(nullptr)
				{}
				Iterator(LIST_NODE* pNode, const List<T>* pList)
					: m_pNode(pNode)
					, m_pList(pList)
				{}
				Iterator(const Iterator& right)
					: m_pNode(right.m_pNode)
					, m_pList(right.m_pList)
				{}
				virtual ~Iterator()
				{}

				Iterator& operator = (const Iterator& right)
				{
					if (this != &right)
					{
						m_pNode = right.m_pNode;
						m_pList = right.m_pList;
					}
					return *this;
				}
				
				bool operator == (const Iterator& iterator) const
				{
					// リスト違い
					if (m_pList != iterator.m_pList)
					{
						return false;
					}
					// ノード違い
					if (iterator.m_pNode != m_pNode)
					{
						// 空リストの先頭vs末尾
						if (m_pList->GetSize() == 0
							&& iterator.m_pList->GetSize() == 0)
						{
							return true;
						}
						return false;
					}
					return true;
				}
				bool operator != (const Iterator& iterator) const
				{
					// リスト違い
					if (m_pList != iterator.m_pList)
					{
						return true;
					}
					// ノード違い
					if (iterator.m_pNode != m_pNode)
					{
						// 空リストの先頭vs末尾
						if (m_pList->GetSize() == 0
							&& iterator.m_pList->GetSize() == 0)
						{
							return false;
						}
						return true;
					}
					return false;
				}
				bool operator == (const ConstIterator& iterator) const
				{
					// リスト違い
					if (m_pList != iterator.m_pList)
					{
						return false;
					}
					// ノード違い
					if (iterator.m_pNode != m_pNode)
					{
						// 空リストの先頭vs末尾
						if (m_pList->GetSize() == 0
							&& iterator.m_pList->GetSize() == 0)
						{
							return true;
						}
						return false;
					}
					return true;
				}
				bool operator != (const ConstIterator& iterator) const
				{
					// リスト違い
					if (m_pList != iterator.m_pList)
					{
						return true;
					}
					// ノード違い
					if (iterator.m_pNode != m_pNode)
					{
						// 空リストの先頭vs末尾
						if (m_pList->GetSize() == 0
							&& iterator.m_pList->GetSize() == 0)
						{
							return false;
						}
						return true;
					}
					return false;
				}

				Iterator& operator++()
				{
					m_pNode = m_pNode->pNext;
					return *this;
				}
				Iterator operator++(int)
				{
					Iterator it(*this);
					m_pNode = m_pNode->pNext;
					return it;
				}
				Iterator& operator--()
				{
					m_pNode = m_pNode->pPrev;
					return *this;
				}
				Iterator operator--(int)
				{
					Iterator it(*this);
					m_pNode = m_pNode->pPrev;
					return it;
				}


				T& operator*()
				{
					return m_pNode->data;
				}
				const T& operator*()const
				{
					return m_pNode->data;
				}
				

			private:
				LIST_NODE*		m_pNode;
				const List<T>*	m_pList;
			};

			class ConstIterator
			{
				friend class List;
			public:
				ConstIterator()
					: m_pNode(nullptr)
					, m_pList(nullptr)
				{}
				ConstIterator(const LIST_NODE* pNode, const List<T>* pList)
					: m_pNode(pNode)
					, m_pList(pList)
				{}
				ConstIterator(const ConstIterator& right)
					: m_pNode(right.m_pNode)
					, m_pList(right.m_pList)
				{}
				virtual ~ConstIterator()
				{}

				ConstIterator& operator = (const ConstIterator& right)
				{
					if (this != &right)
					{
						m_pNode = right.m_pNode;
						m_pList = right.m_pList;
					}
					return *this;
				}

				bool operator == (const Iterator& iterator) const
				{
					// リスト違い
					if (m_pList != iterator.m_pList)
					{
						return false;
					}
					// ノード違い
					if (iterator.m_pNode != m_pNode)
					{
						// 空リストの先頭vs末尾
						if (m_pList->GetSize() == 0
							&& iterator.m_pList->GetSize() == 0)
						{
							return true;
						}
						return false;
					}
					return true;
				}
				bool operator != (const Iterator& iterator) const
				{
					// リスト違い
					if (m_pList != iterator.m_pList)
					{
						return true;
					}
					// ノード違い
					if (iterator.m_pNode != m_pNode)
					{
						// 空リストの先頭vs末尾
						if (m_pList->GetSize() == 0
							&& iterator.m_pList->GetSize() == 0)
						{
							return false;
						}
						return true;
					}
					return false;
				}
				bool operator == (const ConstIterator& iterator) const
				{
					// リスト違い
					if (m_pList != iterator.m_pList)
					{
						return false;
					}
					// ノード違い
					if (iterator.m_pNode != m_pNode)
					{
						// 空リストの先頭vs末尾
						if (m_pList->GetSize() == 0
							&& iterator.m_pList->GetSize() == 0)
						{
							return true;
						}
						return false;
					}
					return true;
				}
				bool operator != (const ConstIterator& iterator) const
				{
					// リスト違い
					if (m_pList != iterator.m_pList)
					{
						return true;
					}
					// ノード違い
					if (iterator.m_pNode != m_pNode)
					{
						// 空リストの先頭vs末尾
						if (m_pList->GetSize() == 0
							&& iterator.m_pList->GetSize() == 0)
						{
							return false;
						}
						return true;
					}
					return false;
				}
				ConstIterator& operator++()
				{
					m_pNode = m_pNode->pNext;
					return *this;
				}
				ConstIterator operator++(int)
				{
					ConstIterator it(*this);
					m_pNode = m_pNode->pNext;
					return it;
				}
				ConstIterator& operator--()
				{
					m_pNode = m_pNode->pPrev;
					return *this;
				}
				ConstIterator operator--(int)
				{
					ConstIterator it(*this);
					m_pNode = m_pNode->pPrev;
					return it;
				}


				const T& operator*()const
				{
					return m_pNode->data;
				}

			private:
				const LIST_NODE*	m_pNode;
				const List<T>*		m_pList;
			};

		public:
			void SwapNode(int left, int right)
			{
				auto lit = GetBegin();
				for (int i = 0; i < left; ++i)
					++lit;
				auto rit = GetBegin();
				for (int i = 0; i < right; ++i)
					++rit;
				_SwapNode(lit.m_pNode, rit.m_pNode);
			}

		private:
			bool _SwapNode(LIST_NODE* left, LIST_NODE* right);

			template<class CMP>
			void _QSort(const Iterator& left, const Iterator& right, CMP cmp);


			void _print(bool reverse = false)
			{
				for (auto it = GetBegin(); it != GetEnd(); ++it)
				{
					printf("%d ", *it);
				}
				printf("\n");
				if (reverse)
				{
					for (auto it = --GetEnd(); it != GetBegin(); --it)
					{
						printf("%d ", *it);
					}
					printf("%d\n", *GetBegin());
				}
			}

		private:
			LIST_NODE*	m_pFirst;
			LIST_NODE*	m_pLast;
			LIST_NODE	m_dummy;

			size_t		m_size;

		};	// class List<T>


		template<class T>
		template<class CMP>
		void List<T>::QSort(CMP cmp)
		{
			_QSort(GetBegin(), --GetEnd(), cmp);
		}

		template<class T>
		template<class CMP>
		void List<T>::_QSort(const Iterator& left, const Iterator& right, CMP cmp)
		{
			if (left == right)
			{
				return;
			}
			LIST_NODE* pLeft = left.m_pNode;
			LIST_NODE* pRight = right.m_pNode;
#if 1
			LIST_NODE* plp = pLeft->pPrev;
			LIST_NODE* pln = pLeft->pNext;
			LIST_NODE* prp = pRight->pPrev;
			LIST_NODE* prn = pRight->pNext;
			printf("left:%d, right:%d\n"
					"%d,%d,%d | %d,%d,%d\n",
					*left, *right,
					(plp)?(plp->data):-1, *left, pln->data, prp->data, *right, prn->data);
			_print();
#endif
			Iterator lit = left, rit = right;
			//--rit;
			const T& pivot = *left;
			for (;;) {
				while (cmp(*lit, pivot))
				{
					++lit;
				}
				while (cmp(pivot, *rit))
				{
					--rit;
				}
				// 同じ要素を選択したら
				if (lit == rit)
				{
					//return;
					rit++;
					printf("右半分\n");
					_QSort(rit, Iterator(pRight, this), cmp);
					//++lit;
					break;
				}
				// 右と左が逆転したら
				Iterator it = rit;
				++it;
				if (lit == it)
				{
					break;
				}

				// ノードの入れ替え
				//std::swap(*lit, *rit);
				LIST_NODE* pLeftNode = lit.m_pNode;
				LIST_NODE* pRightNode = rit.m_pNode;
				if (_SwapNode(pLeftNode, pRightNode))
				{
					// 次ノードへ
					lit = ++Iterator(pRightNode, this);
					rit = --Iterator(pLeftNode, this);
					
					if (pLeftNode == pLeft)
					{
						pLeft = pRightNode;
						pRight = pLeftNode;
					}
				}
				else
				{
					++lit;
					--rit;
				}
			}
			// 戻りすぎた分を進む
			//++rit;

			// 左半分
			printf("左半分\n");
			_QSort(Iterator(pLeft, this), lit, cmp);
			// 右半分
			printf("右半分\n");
			_QSort(rit, Iterator(pRight, this), cmp);
		}

		template<class T>
		bool List<T>::_SwapNode(LIST_NODE* left, LIST_NODE* right)
		{
			// 同じ要素を交換する場合
			if (left == right)
			{
				return false;
			}
			
			LIST_NODE* leftPrev = left->pPrev;
			LIST_NODE* leftNext = left->pNext;
			LIST_NODE* rightPrev = right->pPrev;
			LIST_NODE* rightNext = right->pNext;
			printf("%d <-> %d\n", left->data, right->data);
			// 左右の入れ替え
			if (left == rightPrev || leftNext == right)
			{
				if (left != m_pFirst)
					leftPrev->pNext = right;
				rightNext->pPrev = left;

				left->pNext = rightNext;
				right->pPrev = leftPrev;

				left->pPrev = right;
				right->pNext = left;

			}
			else 
			{
				if (left != m_pFirst)
					leftPrev->pNext = right;
				rightNext->pPrev = left;

				leftNext->pPrev = right;
				rightPrev->pNext = left;

				left->pNext = rightNext;
				right->pPrev = leftPrev;

				left->pPrev = rightPrev;
				right->pNext = leftNext;
			}

			if (left == m_pFirst)
				m_pFirst = right;
			if (right == m_pLast)
				m_pLast = left;

			return true;
			//_print();
		}

	}	// namespace chapter02

}	// namespace ex01_DataSturucture

#include "List.inl"

#endif	// __INCLUDED_LIST_H__