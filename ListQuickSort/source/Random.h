/**=============================================================================
	@file		Random.h
	@brief		乱数発生クラス 定義
	@author		Masato Yamamoto
	@date		2014-11-24
			
	@par		[説明]
				乱数発生器の定義
	@note

		Copyright (C) 2014  M.Yamamoto
=============================================================================*/
#ifndef __RANDOM_H__
#define __RANDOM_H__


#ifndef _RANDOM_
#include <random>
#endif

namespace ns_Random
{
	/**
		@class		Random
		@brief		乱数発生クラス
		@par
					<< シングルトンパターン >>
					乱数クラス生成時にシード初期化、
					メルセンヌツイスター方式で[min, max)の乱数の取得をする
	*/
	class Random
	{
		//=====================================================
		// メソッド宣言
		//=====================================================
	public:
		
		/**
			@brief		インスタンス取得
			@param[in]	なし
			@return		乱数発生器
		*/
		static Random* GetInstance();

		
		/**
			@brief		デストラクタ
			@param[in]	なし
			@return		なし			
		*/
		virtual ~Random();


		/**
			@brief		乱数取得
			@param[in]	min		最小値
			@param[in]	max		最大値
			@return		[min, max)の乱数
		*/
		template<typename ValueType> inline ValueType GetRandom(const ValueType& min, const ValueType& max);
		
		/**
			@brief		乱数取得(整数値)
			@param[in]	min		最小値
			@param[in]	max		最大値
			@return		[min, max)の乱数
		*/
		template<> inline int GetRandom<int>(const int& min, const int& max);


	protected:

	private:
		/**
			@brief		コンストラクタ
			@param[in]	なし
			@return		なし
			@par		乱数シード初期化
		*/
		Random();

		Random(const Random&) = delete;
		Random& operator= (const Random&) = delete;

		//=====================================================
		// 変数宣言
		//=====================================================
	protected:

	private:

		::std::mt19937 m_engine;			//!< メルセンヌツイスター

	};



}	// ns_Random

#include "Random.inl"


#ifdef __cplusplus
#define USING_NS_RANDOM		using namespace ns_Random
#else
#define USING_NS_RANDOM
#endif


#endif	// __RANDOM_H__