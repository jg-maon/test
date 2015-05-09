/**=============================================================================
	@file		Random.cpp
	@brief		���������N���X ����
	@author		Masato Yamamoto
	@date		2014-11-24
			
	@par		[����]
				����������̎���
	@note

		Copyright (C) 2014  M.Yamamoto
=============================================================================*/
#include "Random.h"


namespace ns_Random
{
#pragma region class Random
	/**
		@brief		�C���X�^���X�擾
		@param[in]	�Ȃ�
		@return		����������
	*/
	Random* Random::GetInstance()
	{
		static Random random;
		return &random;	
	}
		
	/**
		@brief		�f�X�g���N�^
		@param[in]	�Ȃ�
		@return		�Ȃ�			
	*/
	Random::~Random()
	{
	}

	/**
		@brief		�R���X�g���N�^
		@param[in]	�Ȃ�
		@return		�Ȃ�
		@par		�����V�[�h������
	*/
	Random::Random()
	{
		::std::random_device device;
		m_engine.seed(device());
	}
#pragma endregion	// Random

}	// ns_Random
