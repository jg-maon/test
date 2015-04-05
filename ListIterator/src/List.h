/**************************************************************************//**
	@file		DoublyList.hpp
	@brief		�o�������X�g�N���X ��`, ����
	@author		Masato Yamamoto
	@date		2014-11-09
			
	@par		[����]
				�ۑ�R ��P
				(2) �e�L�X�g�t�@�C�� Scores.txt �ɂ́A����Q�[���̃X�R�A�ƃ��[�U�[�����L�q����Ă��܂��B
                    ���̃t�@�C���́u�X�R�A�A���[�U�[���̃Z�b�g�v���ЂƂ̗v�f�Ƃ��đo�������X�g�Ɋi�[���A
                    ��ʏ��ɕ\��������v���O�������쐬���Ȃ����B
					���� STL ���̊����̃��C�u�����͎g�p�������삷�邱��
	@note

		Copyright (C) 2014  M.Yamamoto
*//***************************************************************************/


#ifndef __INCLUDED_DOUBLY_LIST_HPP__
#define __INCLUDED_DOUBLY_LIST_HPP__

#ifndef _UTILITY_
#include <utility>
#endif

namespace ns_Exercise3
{

#pragma region _List_val
	/**************************************************************************//**
		@class		_List_val
		@brief		�o�������X�g�ɒǉ�����m�[�h�N���X
		@par		[����]
					��ۑ�R�@��P�� �o�������X�g�N���X
	*//***************************************************************************/
	template <class _Ty> class _List_val
	{
		typedef _List_val<_Ty>	_Myt;		//!< ���g�^
		//====================================================
		// ���\�b�h�錾
		//====================================================
	public:
		/**************************************************************************//**
			@brief		�R���X�g���N�^
			@param[in]	�Ȃ�
			@return		�Ȃ�
		*//***************************************************************************/
		_List_val() :
			m_pVal(0)
			, m_pPrev(0)
			, m_pNext(0)
		{

		}
		
		/**************************************************************************//**
			@brief		�R���X�g���N�^
			@param[in]	_val	�f�[�^
			@param[in]	_pPrev	�O�̗v�f
			@param[in]	_pNext	���̗v�f
		*//***************************************************************************/
		_List_val(const _Ty& _Val, _Myt* _pPrev, _Myt* _pNext) :
			m_pVal(0)
			, m_pPrev(_pPrev)
			, m_pNext(_pNext)
		{
			m_pVal = new _Ty(_Val);
		}

		/**************************************************************************//**
			@brief		�f�X�g���N�^
			@param[in]	�Ȃ�
			@return		�Ȃ�
		*//***************************************************************************/
		~_List_val()
		{
			delete m_pVal;
		}

		/**************************************************************************//**
			@brief		�f�[�^�̎擾
			@param[in]	�Ȃ�
			@return		�f�[�^
		*//***************************************************************************/
		const _Ty* val() const
		{
			return m_pVal;
		}


		/**************************************************************************//**
			@brief		�O�̗v�f�̎擾
			@param[in]	�Ȃ�
			@return		�O�̗v�f
		*//***************************************************************************/
		_Myt* prev() const	
		{
			return m_pPrev;
		}

		/**************************************************************************//**
			@brief		�O�v�f�̐ݒ�
			@param[in]	_pPrev	�O�̗v�f
			@return		�Ȃ�
		*//***************************************************************************/
		void prev(_Myt* _pPrev)
		{
			m_pPrev = _pPrev;
		}


		/**************************************************************************//**
			@brief		���̗v�f�̎擾
			@param[in]	�Ȃ�
			@return		���̗v�f
		*//***************************************************************************/
		_Myt* next() const
		{
			return m_pNext;
		}

		/**************************************************************************//**
			@brief		���v�f�̐ݒ�
			@param[in]	_pNext	���̗v�f
			@return		�Ȃ�
		*//***************************************************************************/
		void next(_Myt* _pNext)
		{
			m_pNext = _pNext;
		}


	protected:
	private:

		//====================================================
		// �ϐ��錾
		//====================================================
	public:
	protected:
	private:
		_Ty*	m_pVal;			//!< �f�[�^
		_Myt*	m_pPrev;		//!< �O�̗v�f
		_Myt*	m_pNext;		//!< ���̗v�f

	};

#pragma endregion	// _List_val



	template<class _Ty> class _List_iterator;

#pragma region	List

	/**************************************************************************//**
		@class		List
		@brief		�o�������X�g�N���X
		@par		[����]
					��ۑ�R�@��P�� �o�������X�g�N���X
	*//***************************************************************************/
	template<typename _Ty> class List
	{
	public:
		typedef List<_Ty>		_Myt;			//!< ���g�^
		typedef _List_val<_Ty>	_Mybase;		//!< �v�f�^

		typedef _List_iterator<_Ty>	iterator;
		friend iterator;

		//=====================================================
		// ���\�b�h�錾
		//=====================================================
	public:
		/**************************************************************************//**
			@brief		�R���X�g���N�^
			@param[in]	�Ȃ�
			@return		�Ȃ�
			*//***************************************************************************/
		List() :
			m_dummy(0)
		{
			m_dummy = new _Mybase;
			m_dummy->next(m_dummy);
			m_dummy->prev(m_dummy);

		}


		/**************************************************************************//**
			@brief		�R�s�[�R���X�g���N�^
			@param[in]	_Right		���X�g
			@return		�Ȃ�
			*//***************************************************************************/
		List(const _Myt& _Right) :
			m_dummy(0)
		{
			m_dummy = new _Mybase(*_Right.m_dummy);
			m_dummy->next(m_dummy);
			m_dummy->prev(m_dummy);
			// ���X�g�̕���
			for (_Mybase* n = _Right.first(); n != _Right.end(); n = n->next())
			{
				push_back(*n->val());
			}

		}

		/**************************************************************************//**
			@brief		=���Z�q
			@param[in]	_Right		���X�g
			@return		�Ȃ�
			*//***************************************************************************/
		_Myt& operator=(const _Myt& _Right)
		{
			if (this != &_Right)
			{
				this->clear();
				delete m_dummy;

				m_dummy = new _Mybase(*_Right.m_dummy);
				m_dummy->next(m_dummy);
				m_dummy->prev(m_dummy);
				// ���X�g�̕���
				for (_Mybase* n = _Right.first(); n != _Right.end(); n = n->next())
				{
					push_back(*n->val());
				}

			}
			return *this;
		}








		/**************************************************************************//**
			@brief		�f�X�g���N�^
			@param[in]	�Ȃ�
			@return		�Ȃ�
			*//***************************************************************************/
		virtual ~List()
		{
			// ���X�g�폜
			this->clear();
			// �ԕ����폜
			delete m_dummy;
		}

		iterator begin()
		{
			return iterator(this, 0);
		}

		
		/**************************************************************************//**
			@brief		�擪�̗v�f�̎擾
			@param[in]	�Ȃ�
			@return		�擪�̗v�f
		*//***************************************************************************/
		_Mybase* first() const
		{
			return m_dummy->next();
		}

		
		/**************************************************************************//**
			@brief		�����̗v�f�̎擾
			@param[in]	�Ȃ�
			@return		�����̗v�f
		*//***************************************************************************/
		_Mybase* last() const
		{
			return m_dummy->prev();
		}


		
		/**************************************************************************//**
			@brief		�����̎��̗v�f(�ԕ�)�̎擾
			@param[in]	�Ȃ�
			@return		�����̎��̗v�f(�ԕ�)
		*//***************************************************************************/
		_Mybase* end() const
		{
			return m_dummy;
		}

		/**************************************************************************//**
			@brief			�v�f���w��ʒu�̑O�ɒǉ�����
			@param[in/out]	_pPos	�v�f�}���ʒu
			@param[in]		_Val	�ǉ�����v�f
			@return			�V�����}�����ꂽ�v�f
		*//***************************************************************************/
		_Mybase* InsertFront(_Mybase* _pPos, const _Ty& _Val)
		{
			_Mybase* ins = new _Mybase(_Val, _pPos, _pPos->next());
			// ���������m�ۂł��Ȃ�������v�f�̘A���������I��
			if (!ins)
			{
				return _pPos;
			}
			_pPos->next()->prev(ins);
			_pPos->next(ins);
			return ins;
		}



		
		/**************************************************************************//**
			@brief			�v�f���w��ʒu�̌��ɒǉ�����
			@param[in/out]	_pPos	�v�f�}���ʒu
			@param[in]		_Val	�ǉ�����v�f
			@return			�V�����}�����ꂽ�v�f
		*//***************************************************************************/
		_Mybase* InsertBack(_Mybase* _pPos, const _Ty& _Val)
		{
			_Mybase* ins = new _Mybase(_Val, _pPos->prev(), _pPos);
			// ���������m�ۂł��Ȃ�������v�f�̘A���������I��
			if (!ins)
			{
				return _pPos;
			}
			_pPos->prev()->next(ins);
			_pPos->prev(ins);
			return ins;
		}


		iterator InsertBack(const iterator& _pos, const _Ty&  _Val);

		iterator erase(const iterator& _pos);


		/**************************************************************************//**
			@brief		���X�g�̐擪�ɗv�f��ǉ�
			@param[in]	_Val	�ǉ�����v�f
			@return		�V�����}�����ꂽ�v�f
		*//***************************************************************************/
		_Mybase* push_front(const _Ty& _Val)
		{
			return InsertBack(first(), _Val);
		}



		
		/**************************************************************************//**
			@brief		���X�g�̐擪�ɗv�f��ǉ�
			@param[in]	_Val	�ǉ�����v�f
			@return		�V�����}�����ꂽ�v�f
		*//***************************************************************************/
		_Mybase* push_back(const _Ty& _Val)
		{
			return InsertFront(last(), _Val);
		}


		/**************************************************************************//**
			@brief		���X�g�ɓo�^����Ă���v�f�̑S�폜
			@param[in]	�Ȃ�
			@return		�Ȃ�
		*//***************************************************************************/
		void clear()
		{
			for (_Mybase* n = first(); n != end(); n = erase(n));
		}


		/**************************************************************************//**
			@brief			�w��ʒu�̗v�f�̍폜
			@param[in/out]	_pPos	�폜�ʒu
			@return			�폜�����v�f�̎��̗v�f
		*//***************************************************************************/
		_Mybase* erase(const _Mybase* _pPos)
		{
			if (_pPos == m_dummy)
			{
				return m_dummy;
			}
			_pPos->prev()->next(_pPos->next());
			_pPos->next()->prev(_pPos->prev());
			_Mybase* next = _pPos->next();
			delete _pPos;
			_pPos = nullptr;
			return next;
		}


		
		/**************************************************************************//**
			@brief		�w��v�f�̑S�폜
			@param[in]	_Val	�폜�f�[�^
			@return		�Ȃ�
		*//***************************************************************************/
		void erase(const _Ty& _Val)
		{
			// �S�v�f�̒T��
			for (_Mybase* n = first(); n != end();)
			{
				if (n->data() == data) // �m�[�h�̎��f�[�^�ƈ�v�����ꍇ
				{
					n = erase(n);		// �v�f���폜���A���̃m�[�h��
				}
				else // �f�[�^�ƈ�v���Ȃ��ꍇ��
				{
					n = n->next();		// ���̃m�[�h�̎��̃m�[�h��
				}
			}
		}


		/**************************************************************************//**
			@brief		���X�g�̐擪�̗v�f���폜
			@param[in]	�Ȃ�
			@return		�Ȃ�
		*//***************************************************************************/
		void pop_front()
		{
			erase(first());
		}
		
		/**************************************************************************//**
			@brief		���X�g�̖����̗v�f���폜
			@param[in]	�Ȃ�
			@return		�Ȃ�
		*//***************************************************************************/
		void pop_back()
		{
			erase(last());
		}

		/**************************************************************************//**
			@brief		���X�g����
			@param[in]	�Ȃ�
			@return		���X�g���󂩂ǂ���
		*//***************************************************************************/
		bool empty() const
		{
			return (size() == 0);
		}


		/**************************************************************************//**
			@brief		���X�g�ɓo�^����Ă���v�f�̐�
			@param[in]	�Ȃ�
			@return		�v�f��
		*//***************************************************************************/
		size_t size() const
		{
			size_t i = 0;
			for (_Mybase* n = first(); n != end(); n = n->next())
			{
				++i;
			}
			return i;
		}


		/**************************************************************************//**
			@brief		�~���\�[�g����
			@param[in]	�Ȃ�
			@return		�Ȃ�
		*//***************************************************************************/
		void sort()
		{
			// �v�f����0�܂���1�̎��̓\�[�g�s�v
			{
				size_t s = size();
				if (s == 0 || s == 1)
					return;
			}

			_Mybase* top = 0;		// �����̃��[�v�̏I�[(�o�u���̏オ�肫��Ƃ���)
			// [0] ~ [size-1]�܂�
			for (_Mybase* i = first(); i != last(); i = top)
			{
				_Mybase* prev = 0;	// �O�v�f
				_Mybase* j;
				// �Ō������߂�
				for (j = last(); j != i && j->next() != i; j = prev)
				{
					// ����ւ��O�̑O�v�f
					prev = j->prev();

					// �\�[�g�� ��O�̗v�f���傫����Γ���ւ�
					if (*j->val() > *prev->val())
					{
						// ����ւ�����
						// ���ݒn��3�Ƃ��āA1 <-> 2 <-> 3 <-> 4��2�ƌ�������ꍇ���l����
						// �ڕW���ʂ́A1 <-> 3 <-> 2 <-> 4

						// 1 -> 3���Ȃ���
						j->prev()->prev()->next(j);

						// 2 <- 4���Ȃ���
						j->next()->prev(prev);

						// 2 -> 4���Ȃ��� = 2 <-> 4���m��
						prev->next(j->next());

						// 1 <- 3���Ȃ��� = 1 <-> 3���m��
						j->prev(prev->prev());

						// 3 <- 2���Ȃ���
						prev->prev(j);

						// 3 -> 2���Ȃ��� = 2 <-> 3���m��
						j->next(prev);

						// ����ւ���A�\�[�g�̐����������킹�邽�߂ɑO�v�f(���̃\�[�g�̑Ώ�)���㏑��
						prev = j;
					}
				}
				if (j->next() == i)
				{
					// �\�[�g���ɏI�_�̗v�f(�擪)�܂œ���ւ����s��ꂽ�ꍇ
					top = i;	// �I�_�v�f�𒲐�
				}
				else
				{
					// ����ւ��O�̎��v�f���Z�b�g
					top = i->next();
				}
			}
		}

		
		/**************************************************************************//**
			@brief		�����̏����ɂ���ă\�[�g����
			@param[in]	_Pred		�\�[�g���@
			@return		�Ȃ�
		*//***************************************************************************/
		template<class _Pr> void sort(_Pr _Pred)
		{
			// �v�f����0�܂���1�̎��̓\�[�g�s�v
			{
				size_t s = size();
				if (s == 0 || s == 1)
					return;
			}

			_Mybase* top = 0;		// �����̃��[�v�̏I�[(�o�u���̏オ�肫��Ƃ���)
			// [0] ~ [size-1]�܂�
			for (_Mybase* i = first(); i != last(); i = top)
			{
				_Mybase* prev = 0;	// �O�v�f
				_Mybase* j;
				// �Ō������߂�
				for (j = last(); j != i && j->next() != i; j = prev)
				{
					// ����ւ��O�̑O�v�f
					prev = j->prev();

					// �\�[�g�� ��O�̗v�f���傫����Γ���ւ�
					if (_Pred(*j->val(), *prev->val()))
					{
						// ����ւ�����
						// ���ݒn��3�Ƃ��āA1 <-> 2 <-> 3 <-> 4��2�ƌ�������ꍇ���l����
						// �ڕW���ʂ́A1 <-> 3 <-> 2 <-> 4

						// 1 -> 3���Ȃ���
						j->prev()->prev()->next(j);

						// 2 <- 4���Ȃ���
						j->next()->prev(prev);

						// 2 -> 4���Ȃ��� = 2 <-> 4���m��
						prev->next(j->next());

						// 1 <- 3���Ȃ��� = 1 <-> 3���m��
						j->prev(prev->prev());

						// 3 <- 2���Ȃ���
						prev->prev(j);

						// 3 -> 2���Ȃ��� = 2 <-> 3���m��
						j->next(prev);

						// ����ւ���A�\�[�g�̐����������킹�邽�߂ɑO�v�f(���̃\�[�g�̑Ώ�)���㏑��
						prev = j;
					}
				}
				if (j->next() == i)
				{
					// �\�[�g���ɏI�_�̗v�f(�擪)�܂œ���ւ����s��ꂽ�ꍇ
					top = i;	// �I�_�v�f�𒲐�
				}
				else
				{
					// ����ւ��O�̎��v�f���Z�b�g
					top = i->next();
				}
			}
		}

		void QSort()
		{
			// �v�f���Ȃ���΃\�[�g�I��
			if (this->size() <= 1)
			{
				return;
			}
			const _Ty* pivot = this->first()->val();
			*this = *_QSort(pivot);

		}

	protected:

	private:

		_Myt* _QSort(const _Ty* pivot)
		{
			_Mybase* pos = this->first()->next();
			_Myt* low = new _Myt();		// pivot�����������l���i�[
			_Myt* high = new _Myt();	// pivot�����傫���l���i�[

			for (; pos != this->end(); pos = pos->next())
			{
				const _Ty* val = pos->val();
				if (*val <= *pivot)
				{
					low->push_back(*val);
				}
				else
				{
					high->push_back(*val);
				}
			}
			size_t lSize = low->size();
			size_t hSize = high->size();
			low->QSort();
			high->QSort();

			low->last()->next(high->first());
			high->first()->prev(low->last());
			return low;
		}


		//=====================================================
		// �ϐ��錾
		//=====================================================
	public:

	protected:

	private:

		_Mybase* m_dummy;			//!< �_�~�[(data:�ԕ��Anext:�擪�Aprev:����)
	};

	
#pragma endregion	// List


	template<class _Ty> class _List_iterator
	{
		friend List<_Ty>;
	public:
		_List_iterator(const _List_iterator& iterator)
		{
			m_index = iterator.m_index;
			m_pList = iterator.m_pList;
		}

		_Ty& operator*()
		{
			static _Ty dummy;

			_List_val<_Ty>* i = m_pList->first();
			for (size_t ii = 0; i != m_pList->end() && ii < m_index; ++ii, i = i->next());

			return m_index != SIZE_MAX ? *i->val() : dummy;
		}

		_List_iterator<_Ty>& operator++()
		{
			if (m_index >= m_pList->size())
			{
				return  *this;
			}

			m_index++;
			return *this;
		}

		_List_iterator<_Ty>& operator++(int)
		{
			if (m_index >= m_pList->size())
			{
				return  *this;
			}
			++m_index;
			return *this;
		}
		

	private:
		_List_iterator()
			: m_index(SIZE_MAX)
			, m_pList(nullptr)
		{

		}


		_List_iterator(List<_Ty>* pList, int index)
			: m_index(index)
			, m_pList(pList)
		{}

	private:
		size_t m_index;
		List<_Ty>* m_pList;

	};




	//_Mybase* InsertBack(const iterator& _pos, const _Ty&  _Val);
	template<class _Ty> _List_iterator<_Ty> List<_Ty>::InsertBack(const iterator& _pos, const _Ty&  _Val)
	{
		size_t i = 0;
		for (_Mybase* n = this->first(); n != this->end(); n = n->next())
		{
			if (i++ == _pos.m_index)
			{
				_Mybase* ins = new _Mybase(_Val, n, n->next());
				// ���������m�ۂł��Ȃ�������v�f�̘A���������I��
				if (!ins)
				{
					return iterator(this, i);
				}
				n->next()->prev(ins);
				n->next(ins);
				return iterator(this, i);
			}
		}
		return iterator(this, i);
	}
	template <class _Ty> _List_iterator<_Ty> List<_Ty>::erase(const iterator& _pos)
	{		
		_Mybase* pPos = this->first();
		size_t i = 0;
		for (; pPos != this->end() && i < _pos.m_index; pPos = pPos->next(), ++i);

		if (pPos == this->end())
		{
			return iterator(this, i);
		}
		pPos->prev()->next(pPos->next());
		pPos->next()->prev(pPos->prev());
		_Mybase* next = pPos->next();
		delete pPos;
		pPos = nullptr;
		return iterator(this, i);
	}

}



#endif	// __INCLUDED_DOUBLY_LIST_HPP__