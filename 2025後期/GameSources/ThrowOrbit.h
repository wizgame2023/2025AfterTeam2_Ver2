/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
#define ORBIT_SQUARER -1

	class ThrowOrbit : public Object {
		float m_Duration;	//配置間隔
		float m_OrbitGap;	//配置の隙間
		float m_OrbitWidth;	//横幅

		Vec3 m_ThrowPosition;	//始点
		Vec3 m_TargetPosition;	//終点
		
		vector<shared_ptr<Board>> m_Orbits;	//軌道上の点の配列

		/// <summary>
		/// 指定した数の軌道上の点を作成する
		/// </summary>
		/// <param name="orbitCount">点の数</param>
		void MatchOrbitCount(int orbitCount);
	public:
		ThrowOrbit(const shared_ptr<Stage>& ptr,float width,float duration,float gap) : Object(ptr), m_OrbitWidth(width),m_Duration(duration),m_OrbitGap(gap){}
		virtual ~ThrowOrbit(){}

		virtual void OnCreate()override;
		virtual void OnUpdate2()override;

		/// <summary>
		/// 飛ばす始点と終点を指定する
		/// </summary>
		/// <param name="start">始点</param>
		/// <param name="target">終点</param>
		void Throw(const Vec3& start, const Vec3& target) {
			m_ThrowPosition = start;
			m_TargetPosition = target;
		}

		/// <summary>
		/// 軌道をしまう
		/// </summary>
		void Close() {
			m_ThrowPosition = m_TargetPosition = Vec3();
		}
	};
}
//end basecross
