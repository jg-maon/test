/**************************************************************************//**
	@file		DoublyList.hpp
	@brief		双方向リストクラス 定義, 実装
	@author		Masato Yamamoto
	@date		2014-11-09
			
	@par		[説明]
				課題３ 問１
				(2) テキストファイル Scores.txt には、あるゲームのスコアとユーザー名が記述されています。
                    このファイルの「スコア、ユーザー名のセット」をひとつの要素として双方向リストに格納し、
                    上位順に表示させるプログラムを作成しなさい。
					※注 STL 等の既存のライブラリは使用せず自作すること
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
		@brief		双方向リストに追加するノードクラス
		@par		[説明]
					≪課題３　問１≫ 双方向リストクラス
	*//***************************************************************************/
	template <class _Ty> class _List_val
	{
		typedef _List_val<_Ty>	_Myt;		//!< 自身型
		//====================================================
		// メソッド宣言
		//====================================================
	public:
		/**************************************************************************//**
			@brief		コンストラクタ
			@param[in]	なし
			@return		なし
		*//***************************************************************************/
		_List_val() :
			m_pVal(0)
			, m_pPrev(0)
			, m_pNext(0)
		{

		}
		
		/**************************************************************************//**
			@brief		コンストラクタ
			@param[in]	_val	データ
			@param[in]	_pPrev	前の要素
			@param[in]	_pNext	次の要素
		*//***************************************************************************/
		_List_val(const _Ty& _Val, _Myt* _pPrev, _Myt* _pNext) :
			m_pVal(0)
			, m_pPrev(_pPrev)
			, m_pNext(_pNext)
		{
			m_pVal = new _Ty(_Val);
		}

		/**************************************************************************//**
			@brief		デストラクタ
			@param[in]	なし
			@return		なし
		*//***************************************************************************/
		~_List_val()
		{
			delete m_pVal;
		}

		/**************************************************************************//**
			@brief		データの取得
			@param[in]	なし
			@return		データ
		*//***************************************************************************/
		const _Ty* val() const
		{
			return m_pVal;
		}


		/**************************************************************************//**
			@brief		前の要素の取得
			@param[in]	なし
			@return		前の要素
		*//***************************************************************************/
		_Myt* prev() const	
		{
			return m_pPrev;
		}

		/**************************************************************************//**
			@brief		前要素の設定
			@param[in]	_pPrev	前の要素
			@return		なし
		*//***************************************************************************/
		void prev(_Myt* _pPrev)
		{
			m_pPrev = _pPrev;
		}


		/**************************************************************************//**
			@brief		次の要素の取得
			@param[in]	なし
			@return		次の要素
		*//***************************************************************************/
		_Myt* next() const
		{
			return m_pNext;
		}

		/**************************************************************************//**
			@brief		次要素の設定
			@param[in]	_pNext	次の要素
			@return		なし
		*//***************************************************************************/
		void next(_Myt* _pNext)
		{
			m_pNext = _pNext;
		}


	protected:
	private:

		//====================================================
		// 変数宣言
		//====================================================
	public:
	protected:
	private:
		_Ty*	m_pVal;			//!< データ
		_Myt*	m_pPrev;		//!< 前の要素
		_Myt*	m_pNext;		//!< 次の要素

	};

#pragma endregion	// _List_val



	template<class _Ty> class _List_iterator;

#pragma region	List

	/**************************************************************************//**
		@class		List
		@brief		双方向リストクラス
		@par		[説明]
					≪課題３　問１≫ 双方向リストクラス
	*//***************************************************************************/
	template<typename _Ty> class List
	{
	public:
		typedef List<_Ty>		_Myt;			//!< 自身型
		typedef _List_val<_Ty>	_Mybase;		//!< 要素型

		typedef _List_iterator<_Ty>	iterator;
		friend iterator;

		//=====================================================
		// メソッド宣言
		//=====================================================
	public:
		/**************************************************************************//**
			@brief		コンストラクタ
			@param[in]	なし
			@return		なし
			*//***************************************************************************/
		List() :
			m_dummy(0)
		{
			m_dummy = new _Mybase;
			m_dummy->next(m_dummy);
			m_dummy->prev(m_dummy);

		}


		/**************************************************************************//**
			@brief		コピーコンストラクタ
			@param[in]	_Right		リスト
			@return		なし
			*//***************************************************************************/
		List(const _Myt& _Right) :
			m_dummy(0)
		{
			m_dummy = new _Mybase(*_Right.m_dummy);
			m_dummy->next(m_dummy);
			m_dummy->prev(m_dummy);
			// リストの複製
			for (_Mybase* n = _Right.first(); n != _Right.end(); n = n->next())
			{
				push_back(*n->val());
			}

		}

		/**************************************************************************//**
			@brief		=演算子
			@param[in]	_Right		リスト
			@return		なし
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
				// リストの複製
				for (_Mybase* n = _Right.first(); n != _Right.end(); n = n->next())
				{
					push_back(*n->val());
				}

			}
			return *this;
		}








		/**************************************************************************//**
			@brief		デストラクタ
			@param[in]	なし
			@return		なし
			*//***************************************************************************/
		virtual ~List()
		{
			// リスト削除
			this->clear();
			// 番兵等削除
			delete m_dummy;
		}

		iterator begin()
		{
			return iterator(this, 0);
		}

		
		/**************************************************************************//**
			@brief		先頭の要素の取得
			@param[in]	なし
			@return		先頭の要素
		*//***************************************************************************/
		_Mybase* first() const
		{
			return m_dummy->next();
		}

		
		/**************************************************************************//**
			@brief		末尾の要素の取得
			@param[in]	なし
			@return		末尾の要素
		*//***************************************************************************/
		_Mybase* last() const
		{
			return m_dummy->prev();
		}


		
		/**************************************************************************//**
			@brief		末尾の次の要素(番兵)の取得
			@param[in]	なし
			@return		末尾の次の要素(番兵)
		*//***************************************************************************/
		_Mybase* end() const
		{
			return m_dummy;
		}

		/**************************************************************************//**
			@brief			要素を指定位置の前に追加する
			@param[in/out]	_pPos	要素挿入位置
			@param[in]		_Val	追加する要素
			@return			新しく挿入された要素
		*//***************************************************************************/
		_Mybase* InsertFront(_Mybase* _pPos, const _Ty& _Val)
		{
			_Mybase* ins = new _Mybase(_Val, _pPos, _pPos->next());
			// メモリが確保できなかったら要素の連結をせず終了
			if (!ins)
			{
				return _pPos;
			}
			_pPos->next()->prev(ins);
			_pPos->next(ins);
			return ins;
		}



		
		/**************************************************************************//**
			@brief			要素を指定位置の後ろに追加する
			@param[in/out]	_pPos	要素挿入位置
			@param[in]		_Val	追加する要素
			@return			新しく挿入された要素
		*//***************************************************************************/
		_Mybase* InsertBack(_Mybase* _pPos, const _Ty& _Val)
		{
			_Mybase* ins = new _Mybase(_Val, _pPos->prev(), _pPos);
			// メモリが確保できなかったら要素の連結をせず終了
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
			@brief		リストの先頭に要素を追加
			@param[in]	_Val	追加する要素
			@return		新しく挿入された要素
		*//***************************************************************************/
		_Mybase* push_front(const _Ty& _Val)
		{
			return InsertBack(first(), _Val);
		}



		
		/**************************************************************************//**
			@brief		リストの先頭に要素を追加
			@param[in]	_Val	追加する要素
			@return		新しく挿入された要素
		*//***************************************************************************/
		_Mybase* push_back(const _Ty& _Val)
		{
			return InsertFront(last(), _Val);
		}


		/**************************************************************************//**
			@brief		リストに登録されている要素の全削除
			@param[in]	なし
			@return		なし
		*//***************************************************************************/
		void clear()
		{
			for (_Mybase* n = first(); n != end(); n = erase(n));
		}


		/**************************************************************************//**
			@brief			指定位置の要素の削除
			@param[in/out]	_pPos	削除位置
			@return			削除した要素の次の要素
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
			@brief		指定要素の全削除
			@param[in]	_Val	削除データ
			@return		なし
		*//***************************************************************************/
		void erase(const _Ty& _Val)
		{
			// 全要素の探査
			for (_Mybase* n = first(); n != end();)
			{
				if (n->data() == data) // ノードの持つデータと一致した場合
				{
					n = erase(n);		// 要素を削除し、次のノードへ
				}
				else // データと一致しない場合は
				{
					n = n->next();		// そのノードの次のノードへ
				}
			}
		}


		/**************************************************************************//**
			@brief		リストの先頭の要素を削除
			@param[in]	なし
			@return		なし
		*//***************************************************************************/
		void pop_front()
		{
			erase(first());
		}
		
		/**************************************************************************//**
			@brief		リストの末尾の要素を削除
			@param[in]	なし
			@return		なし
		*//***************************************************************************/
		void pop_back()
		{
			erase(last());
		}

		/**************************************************************************//**
			@brief		リストが空か
			@param[in]	なし
			@return		リストが空かどうか
		*//***************************************************************************/
		bool empty() const
		{
			return (size() == 0);
		}


		/**************************************************************************//**
			@brief		リストに登録されている要素の数
			@param[in]	なし
			@return		要素数
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
			@brief		降順ソートする
			@param[in]	なし
			@return		なし
		*//***************************************************************************/
		void sort()
		{
			// 要素数が0または1の時はソート不要
			{
				size_t s = size();
				if (s == 0 || s == 1)
					return;
			}

			_Mybase* top = 0;		// 内側のループの終端(バブルの上がりきるところ)
			// [0] ~ [size-1]まで
			for (_Mybase* i = first(); i != last(); i = top)
			{
				_Mybase* prev = 0;	// 前要素
				_Mybase* j;
				// 最後尾から戻る
				for (j = last(); j != i && j->next() != i; j = prev)
				{
					// 入れ替え前の前要素
					prev = j->prev();

					// ソート部 一つ前の要素より大きければ入れ替え
					if (*j->val() > *prev->val())
					{
						// 入れ替え処理
						// 現在地を3として、1 <-> 2 <-> 3 <-> 4の2と交換する場合を考える
						// 目標結果は、1 <-> 3 <-> 2 <-> 4

						// 1 -> 3をつなげる
						j->prev()->prev()->next(j);

						// 2 <- 4をつなげる
						j->next()->prev(prev);

						// 2 -> 4をつなげる = 2 <-> 4が確立
						prev->next(j->next());

						// 1 <- 3をつなげる = 1 <-> 3が確立
						j->prev(prev->prev());

						// 3 <- 2をつなげる
						prev->prev(j);

						// 3 -> 2をつなげる = 2 <-> 3が確立
						j->next(prev);

						// 入れ替え後、ソートの整合性を合わせるために前要素(次のソートの対象)を上書き
						prev = j;
					}
				}
				if (j->next() == i)
				{
					// ソート時に終点の要素(先頭)まで入れ替えが行われた場合
					top = i;	// 終点要素を調整
				}
				else
				{
					// 入れ替え前の次要素をセット
					top = i->next();
				}
			}
		}

		
		/**************************************************************************//**
			@brief		引数の条件によってソートする
			@param[in]	_Pred		ソート方法
			@return		なし
		*//***************************************************************************/
		template<class _Pr> void sort(_Pr _Pred)
		{
			// 要素数が0または1の時はソート不要
			{
				size_t s = size();
				if (s == 0 || s == 1)
					return;
			}

			_Mybase* top = 0;		// 内側のループの終端(バブルの上がりきるところ)
			// [0] ~ [size-1]まで
			for (_Mybase* i = first(); i != last(); i = top)
			{
				_Mybase* prev = 0;	// 前要素
				_Mybase* j;
				// 最後尾から戻る
				for (j = last(); j != i && j->next() != i; j = prev)
				{
					// 入れ替え前の前要素
					prev = j->prev();

					// ソート部 一つ前の要素より大きければ入れ替え
					if (_Pred(*j->val(), *prev->val()))
					{
						// 入れ替え処理
						// 現在地を3として、1 <-> 2 <-> 3 <-> 4の2と交換する場合を考える
						// 目標結果は、1 <-> 3 <-> 2 <-> 4

						// 1 -> 3をつなげる
						j->prev()->prev()->next(j);

						// 2 <- 4をつなげる
						j->next()->prev(prev);

						// 2 -> 4をつなげる = 2 <-> 4が確立
						prev->next(j->next());

						// 1 <- 3をつなげる = 1 <-> 3が確立
						j->prev(prev->prev());

						// 3 <- 2をつなげる
						prev->prev(j);

						// 3 -> 2をつなげる = 2 <-> 3が確立
						j->next(prev);

						// 入れ替え後、ソートの整合性を合わせるために前要素(次のソートの対象)を上書き
						prev = j;
					}
				}
				if (j->next() == i)
				{
					// ソート時に終点の要素(先頭)まで入れ替えが行われた場合
					top = i;	// 終点要素を調整
				}
				else
				{
					// 入れ替え前の次要素をセット
					top = i->next();
				}
			}
		}

		void QSort()
		{
			// 要素がなければソート終了
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
			_Myt* low = new _Myt();		// pivotよりも小さい値を格納
			_Myt* high = new _Myt();	// pivotよりも大きい値を格納

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
		// 変数宣言
		//=====================================================
	public:

	protected:

	private:

		_Mybase* m_dummy;			//!< ダミー(data:番兵、next:先頭、prev:末尾)
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
				// メモリが確保できなかったら要素の連結をせず終了
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