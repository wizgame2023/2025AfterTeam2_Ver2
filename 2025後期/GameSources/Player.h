/*!
@file Player.h
@brief ÉvÉåÉCÉÑÅ[Ç»Ç«
*/

#pragma once
#include "stdafx.h"
namespace basecross{
	class ThrowOrbit;

	class Player : public Object {
		shared_ptr<PNTStaticDraw> m_Draw;
		shared_ptr<ThrowOrbit> m_ThrowOrbit;

		float m_MoveSpeed;
	public:
		Player(const shared_ptr<Stage>& ptr);
		virtual ~Player(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
//end basecross

