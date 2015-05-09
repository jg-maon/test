/**=============================================================================
	@file		Random.h
	@brief		���������N���X ��`
	@author		Masato Yamamoto
	@date		2014-11-24
			
	@par		[����]
				����������̒�`
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
		@brief		���������N���X
		@par
					<< �V���O���g���p�^�[�� >>
					�����N���X�������ɃV�[�h�������A
					�����Z���k�c�C�X�^�[������[min, max)�̗����̎擾������
	*/
	class Random
	{
		//=====================================================
		// ���\�b�h�錾
		//=====================================================
	public:
		
		/**
			@brief		�C���X�^���X�擾
			@param[in]	�Ȃ�
			@return		����������
		*/
		static Random* GetInstance();

		
		/**
			@brief		�f�X�g���N�^
			@param[in]	�Ȃ�
			@return		�Ȃ�			
		*/
		virtual ~Random();


		/**
			@brief		�����擾
			@param[in]	min		�ŏ��l
			@param[in]	max		�ő�l
			@return		[min, max)�̗���
		*/
		template<typename ValueType> inline ValueType GetRandom(const ValueType& min, const ValueType& max);
		
		/**
			@brief		�����擾(�����l)
			@param[in]	min		�ŏ��l
			@param[in]	max		�ő�l
			@return		[min, max)�̗���
		*/
		template<> inline int GetRandom<int>(const int& min, const int& max);


	protected:

	private:
		/**
			@brief		�R���X�g���N�^
			@param[in]	�Ȃ�
			@return		�Ȃ�
			@par		�����V�[�h������
		*/
		Random();

		Random(const Random&) = delete;
		Random& operator= (const Random&) = delete;

		//=====================================================
		// �ϐ��錾
		//=====================================================
	protected:

	private:

		::std::mt19937 m_engine;			//!< �����Z���k�c�C�X�^�[

	};



}	// ns_Random

#include "Random.inl"


#ifdef __cplusplus
#define USING_NS_RANDOM		using namespace ns_Random
#else
#define USING_NS_RANDOM
#endif


#endif	// __RANDOM_H__