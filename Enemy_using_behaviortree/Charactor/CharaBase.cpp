#include "CharaBase.h"

bool CharaBase::IsHpPercentOver(float check_percent)
{
	float percent = m_Hp_ / m_MaxHp_;

	if (percent * 100.0f >= check_percent)
	{
		return true;
	}

	return false;
}

bool CharaBase::IsMpPercentOver(float check_percent)
{
	float percent = m_Mp_ / m_MaxMp_;

	if (percent * 100.0f >= check_percent)
	{
		return true;
	}

	return false;
}

bool CharaBase::IsDie()
{
	return m_Hp_ <= 0.0f ? true : false;
}
