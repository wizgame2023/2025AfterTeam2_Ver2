/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"
namespace basecross{

	class Player : public Object {
	public:
		Player(const shared_ptr<Stage>& ptr) : Object(ptr){}
		virtual ~Player(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
//end basecross

