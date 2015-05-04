
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
			// �\�[�g�J�n���̍��[�v�f�ƉE�[�v�f�̃L���b�V��
			LIST_NODE* pLeft = left.m_pNode;
			LIST_NODE* pRight = right.m_pNode;

			// swap�v�f�T���p�C�e���[�^
			Iterator lit = left, rit = right;
			--rit;

			// �s�{�b�g(��l)
			const T& pivot = *left;
			for (;;)
			{
				// �s�{�b�g���������ɗ���ׂ��v�f������܂ō����̃C�e���[�^��i�߂�
				while (cmp(*lit, pivot))
				{
					++lit;
				}
				// �s�{�b�g�����E���ɗ���ׂ��v�f������܂ŉE���̃C�e���[�^��߂�
				while (cmp(pivot, *rit))
				{
					--rit;
				}
				// �����v�f��I��������
				if (lit == rit)
				{
					// �\�[�g�I��
					break;
				}
				// �E�ƍ����t�]������
				Iterator it = rit;
				++it;
				if (lit == it)
				{
					// �\�[�g�I��
					break;
				}

				
				// �m�[�h�̓���ւ�
				LIST_NODE* pLeftNode = lit.m_pNode;
				LIST_NODE* pRightNode = rit.m_pNode;
				if (_SwapNode(lit, rit))
				{
					// ���v�f�ƉE�v�f���w���L���b�V���̏�����
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
			// �E�����̃\�[�g�̂��߂ɃC�e���[�^����i�߂Ă���
			++rit;

			// ������
			_QSort(Iterator(pLeft, this), lit, cmp);
			// �E����
			_QSort(rit, Iterator(pRight, this), cmp);
		}

		template<class T>
		bool List<T>::_SwapNode(Iterator& left, Iterator& right)
		{
			// �����v�f����������ꍇ
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

			// ���E�̓���ւ�
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

			// ���X�g�̐擪�Ɩ����v�f�̃L���b�V���̏�����
			if (pLeft == m_pFirst)
				m_pFirst = pRight;
			if (pRight == m_pLast)
				m_pLast = pLeft;

			// �C�e���[�^�̌���
			std::swap(left, right);
			return true;
		}

	}
}