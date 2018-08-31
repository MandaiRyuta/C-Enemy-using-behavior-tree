#pragma once
#include <vector>

class CharaBase
{
public:
	CharaBase(float max_hp, float max_mp, float attack, float deffence) : {}

private:
	std::vector<int> m_SkillList_;		//�X�L�����X�g
	std::vector<int> m_MsgicList_;		//���@���X�g

	float m_Hp_;		//HP
	float m_MaxHp_;		//�ő�HP
	float m_Mp;			//MP
	float m_MaxMp_;		//�ő�MP
	float m_Attack_;	//�U����
	float m_Deffence_;	//�h���
};