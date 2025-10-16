/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
#define ORBIT_SQUARER -1

	class ThrowOrbit : public Object {
		float m_Duration;	//�z�u�Ԋu
		float m_OrbitGap;	//�z�u�̌���
		float m_OrbitWidth;	//����

		Vec3 m_ThrowPosition;	//�n�_
		Vec3 m_TargetPosition;	//�I�_
		
		vector<shared_ptr<Board>> m_Orbits;	//�O����̓_�̔z��

		/// <summary>
		/// �w�肵�����̋O����̓_���쐬����
		/// </summary>
		/// <param name="orbitCount">�_�̐�</param>
		void MatchOrbitCount(int orbitCount);
	public:
		ThrowOrbit(const shared_ptr<Stage>& ptr,float width,float duration,float gap) : Object(ptr), m_OrbitWidth(width),m_Duration(duration),m_OrbitGap(gap){}
		virtual ~ThrowOrbit(){}

		virtual void OnCreate()override;
		virtual void OnUpdate2()override;

		/// <summary>
		/// ��΂��n�_�ƏI�_���w�肷��
		/// </summary>
		/// <param name="start">�n�_</param>
		/// <param name="target">�I�_</param>
		void Throw(const Vec3& start, const Vec3& target) {
			m_ThrowPosition = start;
			m_TargetPosition = target;
		}

		/// <summary>
		/// �O�������܂�
		/// </summary>
		void Close() {
			m_ThrowPosition = m_TargetPosition = Vec3();
		}
	};
}
//end basecross
