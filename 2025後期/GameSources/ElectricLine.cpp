/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	ElectricLine::ElectricLine(const shared_ptr<Stage>& ptr, const shared_ptr<Player>& player, Vec3& velocity,float speed):
		Object(ptr),m_Player(player),m_Velocity(velocity),m_MoveSpeed(speed)
	{}

	void ElectricLine::OnCreate() {
		Object::OnCreate();
		auto collision = AddComponent<CollisionSphere>();
		auto player = m_Player.lock();
		collision->AddExcludeCollisionGameObject(player);
		collision->SetDrawActive(true);
		SetScale(Vec3(0.1f));
		
		SetPosition(player->GetPosition());
	}
	void ElectricLine::OnUpdate() {
		if (m_OtherElectric.lock() != nullptr) return;
		float elapsed = App::GetApp()->GetElapsedTime();
		Vec3 position = GetPosition();
		position += m_Velocity * m_MoveSpeed * elapsed;
		SetPosition(position);
	}
	void ElectricLine::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (auto electric = other->GetComponent<Electric>(false)) {
			auto player = m_Player.lock();
			auto playerElectric = player->GetComponent<Electric>();
			playerElectric->EvenElectric(electric);
			m_OtherElectric = electric;
		}
	}
}
//end basecross
