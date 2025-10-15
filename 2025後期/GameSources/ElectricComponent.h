/*!
@file Character.h
@brief キャラクターなど
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
		/// 現在の電力量を設定
		/// </summary>
		/// <param name="electric"></param>
		void SetElectricAmount(float electric) {
			m_ElectricAmount = electric;
		}

		/// <summary>
		/// 現在の残り電力量
		/// </summary>
		/// <returns></returns>
		float GetElectricAmount()const {
			return m_ElectricAmount;
		}

		/// <summary>
		/// 電力を追加。最大電力は越えない
		/// </summary>
		/// <param name="electric">追加電力量</param>
		void AddElectric(float electric) {
			m_ElectricAmount = min(m_ElectricAmount + electric, m_MaxElectric);
		}

		/// <summary>
		/// 電力を減少。０以下になると自身のGameObject相手ににイベントを発生
		/// </summary>
		/// <param name="electric">減少電力量</param>
		void SubElectric(float electric) {
			m_ElectricAmount = max(m_ElectricAmount - electric, 0);
			if (m_ElectricAmount == 0) {
				PostEvent(0.0f, GetThis<Electric>(), GetGameObject(), L"Electric Zero");
			}
		}

		/// <summary>
		/// 二つの電力を均等に分割する
		/// </summary>
		/// <param name="other">分割相手</param>
		void EvenElectric(shared_ptr<Electric>& other);

		/// <summary>
		/// 電力を相手から奪う
		/// </summary>
		/// <param name="other">強奪相手</param>
		void SnatchElectric(shared_ptr<Electric>& other);
	};
}
//end basecross
