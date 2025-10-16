/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Player::Player(const shared_ptr<Stage>& ptr):Object(ptr),m_MoveSpeed(2.0f){}
	void Player::OnCreate() {
		Object::OnCreate();

		m_Draw = AddComponent<PNTStaticDraw>();
		m_Draw->SetMeshResource(L"DEFAULT_CUBE");

		SetScale(Vec3(0.5f));
		m_ThrowOrbit = m_Stage->AddGameObject<ThrowOrbit>(ORBIT_SQUARER, 0.5f, 0.25f);
	}
	void Player::OnUpdate() {
		auto& input = InputManager::GetInputManager();
		float elapsed = App::GetApp()->GetElapsedTime();
		float stickLX = input->GetLStick().x;
		Vec2 stickR = input->GetRStick();

		float deadzone = 0.1f;
		//通常移動(X軸)
		if (fabs(stickLX) >= deadzone) {
			Vec3 position = GetPosition();
			position.x += stickLX * m_MoveSpeed * elapsed;

			SetPosition(position);
		}
		//軌道表示
		if (stickR.lengthSqr() > deadzone * deadzone) {
			float orbitsLength = 10.0f;
			m_ThrowOrbit->Throw(GetPosition(), GetPosition() + static_cast<Vec3>(stickR.normalize() * orbitsLength));
		}
		else {
			m_ThrowOrbit->Close();
		}
		float triggerR = input->GetRTrigger();//XR
		float triggerDeadzone = 10.0f;
		//発射中
		if (triggerR > triggerDeadzone) {
			if (input->GetDownButton(L"A")){

			}
		}
	}

}
//end basecross

