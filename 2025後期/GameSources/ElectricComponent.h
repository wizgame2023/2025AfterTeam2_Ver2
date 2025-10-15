/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class Electric : public Component {
		float m_ElectricAmount;
		float m_MaxElectric;
	public:
		Electric(const shared_ptr<GameObject>& ptr, float electric);
		virtual ~Electric(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDraw()override{}

		/// <summary>
		/// ���݂̓d�͗ʂ�ݒ�
		/// </summary>
		/// <param name="electric"></param>
		void SetElectricAmount(float electric) {
			m_ElectricAmount = electric;
		}

		/// <summary>
		/// ���݂̎c��d�͗�
		/// </summary>
		/// <returns></returns>
		float GetElectricAmount()const {
			return m_ElectricAmount;
		}

		/// <summary>
		/// �d�͂�ǉ��B�ő�d�͉͂z���Ȃ�
		/// </summary>
		/// <param name="electric">�ǉ��d�͗�</param>
		void AddElectric(float electric) {
			m_ElectricAmount = min(m_ElectricAmount + electric, m_MaxElectric);
		}

		/// <summary>
		/// �d�͂������B�O�ȉ��ɂȂ�Ǝ��g��GameObject����ɂɃC�x���g�𔭐�
		/// </summary>
		/// <param name="electric">�����d�͗�</param>
		void SubElectric(float electric) {
			m_ElectricAmount = max(m_ElectricAmount - electric, 0);
			if (m_ElectricAmount == 0) {
				PostEvent(0.0f, GetThis<Electric>(), GetGameObject(), L"Electric Zero");
			}
		}

		/// <summary>
		/// ��̓d�͂��ϓ��ɕ�������
		/// </summary>
		/// <param name="other">��������</param>
		void EvenElectric(shared_ptr<Electric>& other);

		/// <summary>
		/// �d�͂𑊎肩��D��
		/// </summary>
		/// <param name="other">���D����</param>
		void SnatchElectric(shared_ptr<Electric>& other);
	};
}
//end basecross
