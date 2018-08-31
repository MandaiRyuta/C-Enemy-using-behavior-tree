#pragma once
#include <string>
#include <vector>
#include "../behavior.h"
class NodeBase
{
public:
	NodeBase() {}
	
public:
	//���O�̃Q�b�^�[�֐�
	std::string GetName()
	{
		return m_name_;
	}
	//�e�m�[�h�̃Q�b�^�[
	NodeBase* GetParent()
	{
		return m_Parent_;
	}
	//�q�m�[�h�̃Q�b�^�[
	NodeBase* GetChild(int idx)
	{
		if (m_Child_.size() >= idx)
		{
			return NULL;
		}
		return m_Child_[idx];
	}
	//�q�m�[�h�Q�b�^�[�i�����j
	NodeBase* GetLastChild()
	{
		if (m_Child_.size() == 0)
		{
			return NULL;
		}
		return m_Child_[m_Child_.size() - 1];
	}
	//�q�m�[�h�̃Q�b�^�[�i�擪�j
	NodeBase* GetTopChild()
	{
		if (m_Child_.size() == 0)
		{
			return NULL;
		}
		return m_Child_[0];
	}
	//�Z��m�[�h�Q�b�^�[
	NodeBase* GetSibling(void)
	{
		return m_Sibling;
	}
	//�K�w�ԍ��Q�b�^�[
	int GetHirerchyNumber()
	{
		return m_HierarchyNumber;
	}
	//�D�揇�ʃQ�b�^�[
	int GetPriority()
	{
		return m_Priority;
	}
	//�e�m�[�h�Z�b�^�[
	void SetParent(NodeBase* parent)
	{
		m_Parent_ = parent;
	}
	//�q�m�[�h�ǉ�
	void AddChild(NodeBase* child)
	{
		m_Child_.push_back(child);
	}
	//�Z��m�[�h�Z�b�^�[
	void SetSibling(NodeBase* sibling)
	{
		m_Sibling = sibling;
	}
	//�s���f�[�^�������Ă��邩
	//bool HasAction()
	//{
	//	return m_Action != NULL ? true : false;
	//}

	bool Judgment();

	NodeBase* SelectPriority(std::vector<NodeBase*> *list);
private:
	std::string m_name_;					//���O
	NodeBase* m_Parent_;					//�e�m�[�h
	std::vector<NodeBase* > m_Child_;		//�q�m�[�h
	NodeBase* m_Sibling;					//�Z��m�[�h
	BehaviorTree::SELECT_RULE m_SelectRule; //�I�����[��
	//ActionBase* m_Action				//���s�N���X
	//ExecJudgmentBase* m_ExecJudgment;	//����N���X
	unsigned int m_Priority;				//�D�揇��
	int m_HierarchyNumber;;					//�K�w�ԍ�

};