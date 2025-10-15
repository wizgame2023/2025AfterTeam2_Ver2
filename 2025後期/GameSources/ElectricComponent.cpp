/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	Electric::Electric(const shared_ptr<GameObject>& ptr, float electric) : 
		Component(ptr),m_ElectricAmount(electric), m_MaxElectric(electric){ }

	void Electric::OnCreate() {
		//初期設定
	}
	void Electric::OnUpdate() {
		//ここでエフェクト？
	}

	void Electric::EvenElectric(shared_ptr<Electric>& other) {
		float otherElectric = other->GetElectricAmount();
		float avarage = (otherElectric + m_ElectricAmount) * 0.5f;
		other->SetElectricAmount(avarage);
		SetElectricAmount(avarage);
	}
	void Electric::SnatchElectric(shared_ptr<Electric>& other) {
		float otherElectric = other->GetElectricAmount();
		float snatchElectric = m_MaxElectric - m_ElectricAmount;
		if (otherElectric < snatchElectric) {
			snatchElectric = otherElectric;
		}

		AddElectric(snatchElectric);
		other->SubElectric(snatchElectric);
	}

}
//end basecross
