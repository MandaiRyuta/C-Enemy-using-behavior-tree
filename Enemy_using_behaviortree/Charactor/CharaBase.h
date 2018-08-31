#pragma once
#include <vector>

//�L�����N�^�[���̃X�e�[�^�X��ݒ肷��ꏊ
class CharaBase
{
public:
	CharaBase(float max_hp, float max_mp, float attack, float deffence) : 
		m_Hp_(max_hp),
		m_MaxHp_(max_hp),
		m_Mp_(max_mp),
		m_MaxMp_(max_mp),
		m_Attack_(attack),
		m_Deffence_(deffence)
	{
	}
	//hp�Q�b�^�[
	float GetHp()
	{
		return m_Hp_;
	}
	//MP�Q�b�^�[
	float GetMp()
	{
		return m_Mp_;
	}
	//�U���̓Q�b�^�[
	float GetAttack()
	{
		return m_Attack_;
	}
	//�h��̓Q�b�^�[
	float GetDeffence()
	{
		return m_Deffence_;
	}
	//�X�L�����������Ă��邩
	bool HasSkill()
	{
		if (m_SkillList_.size() > 0)
		{
			return true;
		}
		return false;
	}
	//���@�������Ă��邩
	bool HasMagic()
	{
		if (m_MsgicList_.size() > 0)
		{
			return true;
		}
		return false;
	}
	//HP�I�[�o�[����
	bool IsHpPercentOver(float check_percent);
	//MP�I�[�o�[����
	bool IsMpPercentOver(float check_percent);
	//���S����
	bool IsDie();
protected:
	std::vector<int> m_SkillList_;		//�X�L�����X�g
	std::vector<int> m_MsgicList_;		//���@���X�g

	float m_Hp_;		//HP
	float m_MaxHp_;		//�ő�HP
	float m_Mp_;			//MP
	float m_MaxMp_;		//�ő�MP
	float m_Attack_;	//�U����
	float m_Deffence_;	//�h���
};