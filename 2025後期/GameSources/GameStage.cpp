/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 1.0f, -10.0f);
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



	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			AddGameObject<Player>();

			auto object = AddGameObject<GameObject>();
			auto draw = object->AddComponent<PNTStaticDraw>();
			draw->SetMeshResource(L"DEFAULT_CUBE");
			draw->SetDiffuse(Col4(1, 0, 0, 1));
			auto col = object->AddComponent<CollisionObb>();
			col->SetFixed(true);
			auto trans = object->GetComponent<Transform>();
			trans->SetPosition(Vec3(0, -3, 0));
			trans->SetScale(Vec3(10, 1, 10));
			object->AddComponent<Electric>(100.0f);
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
