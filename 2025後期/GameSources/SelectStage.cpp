/*!
@file SelectStage.cpp
@brief �Z���N�g�X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//�Z���N�g�X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void SelectStage::CreateViewLight()
	{
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void SelectStage::SpriteCreate()
	{
		auto& app = App::GetApp();

		wstring path = app->GetDataDirWString();
		wstring uiPath = path + L"UI/";

		app->RegisterTexture(L"SelectUI", uiPath + L"SelectLogo.png");
		app->RegisterTexture(L"NumUI", uiPath + L"Number.png");
		app->RegisterTexture(L"CursorUI", uiPath + L"TestCursor.png");


		auto selectSp = AddGameObject<Sprite>(L"SelectUI", Vec3(-640.0f, 400.0f, 0.0f), Vec2(256, 64), Anchor::TopLeft);
		m_StageNum = 10;        // �\�����鐔���̐�
		int maxPerRow = 5;         // 1�s�ɕ\������ő吔
		float baseWidth = 100.0f;
		float spacing = 100.0f;
		float baseHeight = 100.0f;
		float rowSpacing = 200.0f;

		for (int i = 0; i < m_StageNum; i++)
		{
			int row = i / maxPerRow;
			int col = i % maxPerRow;

			float totalWidth = maxPerRow * baseWidth + (maxPerRow - 1) * spacing;
			float startX = -totalWidth / 2.0f;

			float offsetX = (baseWidth + spacing) * col;
			float offsetY = -(baseHeight + rowSpacing) * row;

			Vec3 position = Vec3(startX + offsetX, 200 + offsetY, 0.0f);
			m_NumPositions.push_back(position);  // �ʒu��ۑ�
			Vec2 size = Vec2(100, 100);

			int digit = (i + 1 >= 10) ? 2 : 1;

			m_NumSp = AddGameObject<NumberSprite>(L"NumUI", position, size, digit);
			m_NumSp->UpdateNumber(i + 1);

			if (m_BackSp == nullptr)
			{
				m_BackSp = AddGameObject<Sprite>(L"CursorUI", Vec3(position.x, position.y, position.z), size, Anchor::TopLeft);
			}

		}
	}



	void SelectStage::OnCreate() 
	{
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			SpriteCreate();
		}
		catch (...) {
			throw;
		}
	}

	void SelectStage::OnUpdate()
	{
		auto input = App::GetApp()->GetInputDevice().GetControlerVec()[0];


		if (input.wPressedButtons & XINPUT_GAMEPAD_A)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
		if (input.fThumbLX == 0)
		{
			m_IsStick = false;
		}
		if (input.fThumbLX > 0 && m_IsStick == false)
		{
			m_Count++;
			if (m_Count == 10)
			{
				m_Count = 0;
			}
			if (m_Count >= m_StageNum) m_Count = m_StageNum - 1; // �͈̓`�F�b�N

			auto targetPos = m_NumPositions[m_Count];
			m_BackSp->SetPosition(targetPos);

			m_IsStick = true;
		}
		if (input.fThumbLX < 0 && m_IsStick == false)
		{
			m_Count--;

			if (m_Count == -1)
			{
				m_Count = 10;
			}

			if (m_Count >= m_StageNum) m_Count = m_StageNum - 1; // �͈̓`�F�b�N

			auto targetPos = m_NumPositions[m_Count];
			m_BackSp->SetPosition(targetPos);

			m_IsStick = true;

		}
	}

	void SelectStage::NumSprite()
	{

	}
}
//end basecross
