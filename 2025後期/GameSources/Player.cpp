/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Player::Player(const shared_ptr<Stage>& ptr):Object(ptr),m_MoveSpeed(2.0f), m_IsLineMoving(false){}
	void Player::OnCreate() {
		Object::OnCreate();

		auto collision = AddComponent<CollisionObb>();
		m_Draw = AddComponent<PNTStaticDraw>();
		m_Draw->SetMeshResource(L"DEFAULT_CUBE");

		SetScale(Vec3(0.5f));
		m_ThrowOrbit = m_Stage->AddGameObject<ThrowOrbit>(ORBIT_SQUARER, 0.5f, 0.25f);

		m_Electric = AddComponent<Electric>(100.0f);
	}
	void Player::OnUpdate() {
		auto& input = InputManager::GetInputManager();
		float elapsed = App::GetApp()->GetElapsedTime();
		float stickLX = input->GetLStick().x;
		Vec2 stickR = input->GetRStick();
		float triggerR = input->GetRTrigger();//XR
		float triggerDeadzone = 10.0f;

		float deadzone = 0.1f;
		//通常移動(X軸)
		
		if (m_IsLineMoving) {
			Vec3 position = GetPosition();
			Vec3 direction = m_LineMovingTarget - position;
			float distance = GetScale().y / 2.0f;

			if (direction.lengthSqr() < distance * distance) {
				m_IsLineMoving = false;
			}
			Vec3 amount = direction.normalize() * m_MoveSpeed * elapsed * 5.0f;
			SetPosition(position + amount);

		}else if (fabs(stickLX) >= deadzone) {
			Vec3 position = GetPosition();
			position.x += stickLX * m_MoveSpeed * elapsed;

			SetPosition(position);
		}
		//軌道表示
		if (stickR.lengthSqr() > deadzone * deadzone) {
			float orbitsLength = 10.0f;
			m_ThrowOrbit->Throw(GetPosition(), GetPosition() + static_cast<Vec3>(stickR.normalize() * orbitsLength));

			//発射中
			if (triggerR > triggerDeadzone) {
				if (m_ElectricLine == nullptr) {
					m_ElectricLine = m_Stage->AddGameObject<ElectricLine>(GetThis<Player>(), static_cast<Vec3>(stickR), 40.0f);
				}
			}
		}
		else {
			m_ThrowOrbit->Close();
		}

		if (triggerR > triggerDeadzone) {
			if (input->GetDownButton(L"A")) {
				if (m_ElectricLine->GetOtherElectric()) {
					//SetPosition(m_ElectricLine->GetPosition());
					StartLineMoving(m_ElectricLine->GetPosition());
				}
			}
		}
		else {
			m_Stage->RemoveGameObject<ElectricLine>(m_ElectricLine);
			m_ElectricLine = nullptr;
		}
	}

}
//end basecross

