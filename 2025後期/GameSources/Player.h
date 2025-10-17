/*!
@file Player.h
@brief ÉvÉåÉCÉÑÅ[Ç»Ç«
*/

#pragma once
#include "stdafx.h"
namespace basecross{
	class ThrowOrbit;
	class Electric;
	class ElectricLine;

	class Player : public Object {
		shared_ptr<PNTStaticDraw> m_Draw;
		shared_ptr<ThrowOrbit> m_ThrowOrbit;
		shared_ptr<Electric> m_Electric;
		shared_ptr<ElectricLine> m_ElectricLine;

		Vec3 m_LineMovingTarget;
		float m_MoveSpeed;

		bool m_IsLineMoving;
	public:
		Player(const shared_ptr<Stage>& ptr);
		virtual ~Player(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;


		void StartLineMoving(Vec3 target) {
			m_LineMovingTarget = target;
			m_IsLineMoving = true;
		}
	};
}
//end basecross

