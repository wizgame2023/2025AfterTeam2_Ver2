/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void ThrowOrbit::OnCreate() {
		Object::OnCreate();
	}
	void ThrowOrbit::OnUpdate2() {
		Vec3 direction = m_TargetPosition - m_ThrowPosition;
		float distance = direction.length();
		if (distance < m_Duration) {
			MatchOrbitCount(0);
			return;
		}

		int orbitCount = static_cast<int>(distance / m_Duration);
		Vec3 orbitAddPosition = direction / orbitCount;
		direction = direction.normalize();

		MatchOrbitCount(orbitCount);
		for (int i = 0, size = m_Orbits.size(); i < size; i++) {
			Vec3 position = m_ThrowPosition + orbitAddPosition * i;
			float height = m_Duration - m_OrbitGap;
			auto transform = m_Orbits[i]->GetTrans();
			transform->SetPosition(position);
			if (m_OrbitWidth == ORBIT_SQUARER) {
				transform->SetScale(Vec3(height, height, 1.0f));
			}
			else {
				transform->SetScale(Vec3(m_OrbitWidth, height, 1.0f));
			}

			float rad = atan2f(-direction.x, direction.y);
			Vec3 forward = transform->GetForward();
			auto rot = XMMatrixRotationAxis(forward, rad);
			auto world = m_Transform->GetWorldMatrix();
			world.rotation((Quat)XMQuaternionRotationMatrix(rot));

			transform->SetQuaternion(transform->GetQuaternion() * world.quatInMatrix());
		}
	}

	void ThrowOrbit::MatchOrbitCount(int orbitCount) {
		int currentCount = m_Orbits.size();
		if (currentCount < orbitCount) {
			m_Orbits.reserve(orbitCount);
		}
		for (int i = currentCount; i < orbitCount; i++) {
			auto board = m_Stage->AddGameObject<Board>(L"", Vec3(), Vec3(m_OrbitWidth, 0.1f, 1.0f), true);
			m_Orbits.push_back(board);
		}
		for (int i = currentCount; i > orbitCount; i--) {
			m_Stage->RemoveGameObject<Board>(m_Orbits[i]);
			m_Orbits.erase(m_Orbits.begin() + i);
		}
	}
}
//end basecross
