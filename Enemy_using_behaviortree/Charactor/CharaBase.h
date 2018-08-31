#pragma once
#include <vector>

class CharaBase
{
public:
	CharaBase(float max_hp, float max_mp, float attack, float deffence) : {}

private:
	std::vector<int> m_SkillList_;		//スキルリスト
	std::vector<int> m_MsgicList_;		//魔法リスト

	float m_Hp_;		//HP
	float m_MaxHp_;		//最大HP
	float m_Mp;			//MP
	float m_MaxMp_;		//最大MP
	float m_Attack_;	//攻撃力
	float m_Deffence_;	//防御力
};