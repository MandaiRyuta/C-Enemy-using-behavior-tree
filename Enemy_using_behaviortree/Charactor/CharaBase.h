#pragma once
#include <vector>

//キャラクター事のステータスを設定する場所
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
	//hpゲッター
	float GetHp()
	{
		return m_Hp_;
	}
	//MPゲッター
	float GetMp()
	{
		return m_Mp_;
	}
	//攻撃力ゲッター
	float GetAttack()
	{
		return m_Attack_;
	}
	//防御力ゲッター
	float GetDeffence()
	{
		return m_Deffence_;
	}
	//スキルを所持しているか
	bool HasSkill()
	{
		if (m_SkillList_.size() > 0)
		{
			return true;
		}
		return false;
	}
	//魔法所持しているか
	bool HasMagic()
	{
		if (m_MsgicList_.size() > 0)
		{
			return true;
		}
		return false;
	}
	//HPオーバー判定
	bool IsHpPercentOver(float check_percent);
	//MPオーバー判定
	bool IsMpPercentOver(float check_percent);
	//死亡判定
	bool IsDie();
protected:
	std::vector<int> m_SkillList_;		//スキルリスト
	std::vector<int> m_MsgicList_;		//魔法リスト

	float m_Hp_;		//HP
	float m_MaxHp_;		//最大HP
	float m_Mp_;			//MP
	float m_MaxMp_;		//最大MP
	float m_Attack_;	//攻撃力
	float m_Deffence_;	//防御力
};