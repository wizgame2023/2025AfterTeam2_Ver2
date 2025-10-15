/*!
@file SelectStage.h
@brief �Z���N�g�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Sprite;
	class NumberSprite;

	//--------------------------------------------------------------------------------------
	//	�Z���N�g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage 
	{
		int m_StageNum = 1;

		int m_Count = 0;

		bool m_IsStick = false;

		vector<Vec3> m_NumPositions;


		shared_ptr<NumberSprite> m_NumSp;

		shared_ptr<Sprite> m_BackSp;
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		SelectStage() :Stage() {}
		virtual ~SelectStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		int GetStageNum() { return m_Count; }

	private:
		void SpriteCreate();
		void NumSprite();
	};


}
//end basecross

