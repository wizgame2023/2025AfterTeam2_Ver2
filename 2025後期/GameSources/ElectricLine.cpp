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
		AddComponent<CollisionSphere>();
		SetScale(Vec3(0.1f));
	}
	void ElectricLine::OnUpdate() {

		float elapsed = App::GetApp()->GetElapsedTime();
		Vec3 position = GetPosition();
		position += m_Velocity * m_MoveSpeed * elapsed;
		SetPosition(position);
	}
	void ElectricLine::OnCollisionEnter(shared_ptr<GameObject>& other) {

	}
}
//end basecross
