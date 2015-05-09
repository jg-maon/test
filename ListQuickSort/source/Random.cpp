/**=============================================================================
	@file		Random.cpp
	@brief		乱数発生クラス 実装
	@author		Masato Yamamoto
	@date		2014-11-24
			
	@par		[説明]
				乱数発生器の実装
	@note

		Copyright (C) 2014  M.Yamamoto
=============================================================================*/
#include "Random.h"


namespace ns_Random
{
#pragma region class Random
	/**
		@brief		インスタンス取得
		@param[in]	なし
		@return		乱数発生器
	*/
	Random* Random::GetInstance()
	{
		static Random random;
		return &random;	
	}
		
	/**
		@brief		デストラクタ
		@param[in]	なし
		@return		なし			
	*/
	Random::~Random()
	{
	}

	/**
		@brief		コンストラクタ
		@param[in]	なし
		@return		なし
		@par		乱数シード初期化
	*/
	Random::Random()
	{
		::std::random_device device;
		m_engine.seed(device());
	}
#pragma endregion	// Random

}	// ns_Random
