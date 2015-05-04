
namespace ex01_DataStructure
{
	namespace chapter02
	{
		template<class T>
		template<class CMP>
		void List<T>::QSort(CMP cmp)
		{
			_QSort(GetBegin(), GetEnd(), cmp);
		}

		template<class T>
		template<class CMP>
		void List<T>::_QSort(const Iterator& left, const Iterator& right, CMP cmp)
		{
			if (left == right)
			{
				return;
			}
			// ソート開始時の左端要素と右端要素のキャッシュ
			LIST_NODE* pLeft = left.m_pNode;
			LIST_NODE* pRight = right.m_pNode;

			// swap要素探査用イテレータ
			Iterator lit = left, rit = right;
			--rit;

			// ピボット(基準値)
			const T& pivot = *left;
			for (;;)
			{
				// ピボットよりも左側に来るべき要素が来るまで左側のイテレータを進める
				while (cmp(*lit, pivot))
				{
					++lit;
				}
				// ピボットよりも右側に来るべき要素が来るまで右側のイテレータを戻す
				while (cmp(pivot, *rit))
				{
					--rit;
				}
				// 同じ要素を選択したら
				if (lit == rit)
				{
					// ソート終了
					break;
				}
				// 右と左が逆転したら
				Iterator it = rit;
				++it;
				if (lit == it)
				{
					// ソート終了
					break;
				}

				
				// ノードの入れ替え
				LIST_NODE* pLeftNode = lit.m_pNode;
				LIST_NODE* pRightNode = rit.m_pNode;
				if (_SwapNode(lit, rit))
				{
					// 左要素と右要素を指すキャッシュの初期化
					if (pLeftNode == pLeft)
					{
						pLeft = pRightNode;
					}
					if (pRightNode == pRight)
					{
						pRight = pLeftNode;
					}
				}				
				++lit;
				--rit;
			}
			// 右半分のソートのためにイテレータを一つ進めておく
			++rit;

			// 左半分
			_QSort(Iterator(pLeft, this), lit, cmp);
			// 右半分
			_QSort(rit, Iterator(pRight, this), cmp);
		}

		template<class T>
		bool List<T>::_SwapNode(Iterator& left, Iterator& right)
		{
			// 同じ要素を交換する場合
			if (left == right)
			{
				return false;
			}

			LIST_NODE* pLeft = left.m_pNode;
			LIST_NODE* pRight = right.m_pNode;

			LIST_NODE* leftPrev = pLeft->pPrev;
			LIST_NODE* leftNext = pLeft->pNext;
			LIST_NODE* rightPrev = pRight->pPrev;
			LIST_NODE* rightNext = pRight->pNext;

			// 左右の入れ替え
			if (pLeft == rightPrev || leftNext == pRight)
			{
				if (pLeft != m_pFirst)
					leftPrev->pNext = pRight;
				rightNext->pPrev = pLeft;

				pLeft->pNext = rightNext;
				pRight->pPrev = leftPrev;

				pLeft->pPrev = pRight;
				pRight->pNext = pLeft;

			}
			else
			{
				if (pLeft != m_pFirst)
					leftPrev->pNext = pRight;
				rightNext->pPrev = pLeft;

				leftNext->pPrev = pRight;
				rightPrev->pNext = pLeft;

				pLeft->pNext = rightNext;
				pRight->pPrev = leftPrev;

				pLeft->pPrev = rightPrev;
				pRight->pNext = leftNext;
			}

			// リストの先頭と末尾要素のキャッシュの初期化
			if (pLeft == m_pFirst)
				m_pFirst = pRight;
			if (pRight == m_pLast)
				m_pLast = pLeft;

			// イテレータの交換
			std::swap(left, right);
			return true;
		}

	}
}