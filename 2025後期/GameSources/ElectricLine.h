/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player;
	class ElectricLine : public Object {
		weak_ptr<Player> m_Player;
		weak_ptr<Electric> m_OtherElectric;
		Vec3 m_Velocity;
		float m_MoveSpeed;
	public:
		ElectricLine(const shared_ptr<Stage>& ptr,const shared_ptr<Player>& player,Vec3& velocity,float speed);
		virtual ~ElectricLine(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;


		shared_ptr<Electric> GetOtherElectric() {
			return m_OtherElectric.lock();
		}
	};
}
//end basecross
