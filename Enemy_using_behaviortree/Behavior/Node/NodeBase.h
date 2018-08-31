#pragma once
#include <string>
#include <vector>
#include "../behavior.h"
#include "../../Model/ActionBase/ActionBase.h"

class ExecJudgmentBase;
class BehaviorData;

class NodeBase
{
public:
	NodeBase(std::string name, NodeBase* parent, NodeBase* sibling, int priority, BehaviorTree::SELECT_RULE select_rule, ExecJudgmentBase* exec_judgment, ActionBase* action, int hierarchy_number) :
		m_name_(name),
		m_Parent_(parent),
		m_Sibling(sibling),
		m_Priority(priority),
		m_SelectRule(select_rule),
		m_ExecJudgment(exec_judgment),
		m_Action(action),
		m_HierarchyNumber(hierarchy_number),
		m_Child_(NULL)
	{
	}
	
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
	NodeBase* GetChild(unsigned int idx)
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
	bool HasAction()
	{
		return m_Action != NULL ? true : false;
	}

	bool Judgment(Model* target);
	//�D�揇�ʑI��
	NodeBase* SelectPriority(std::vector<NodeBase*> *list);
	//�����_���I��
	NodeBase* SelectRandom(std::vector<NodeBase*> *list);
	//�I���E�I�t�I��
	NodeBase* SelectOnOff(std::vector<NodeBase*> *list, BehaviorData* data);
	//�V�[�P���X�I��
	NodeBase* SelectSequence(std::vector<NodeBase*> *list, BehaviorData* data);
	//�m�[�h����
	NodeBase* SearchNode(std::string search_name);
	//�m�[�h���_
	NodeBase* Inference(Model* target, BehaviorData* data);
	//�m�[�h���\��
	void PrintName();
	//���s
	ActionBase::STATE Run(Model* target);

private:
	std::string m_name_;					//���O
	NodeBase* m_Parent_;					//�e�m�[�h
	std::vector<NodeBase* > m_Child_;		//�q�m�[�h
	NodeBase* m_Sibling;					//�Z��m�[�h
	BehaviorTree::SELECT_RULE m_SelectRule; //�I�����[��
	ActionBase* m_Action;				//���s�N���X
	ExecJudgmentBase* m_ExecJudgment;	//����N���X
	unsigned int m_Priority;				//�D�揇��
	int m_HierarchyNumber;;					//�K�w�ԍ�

};