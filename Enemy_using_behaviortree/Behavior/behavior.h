#pragma once
#include <string>
class NodeBase;
class BehaviorData;

//���f���̌`�󁕔��聕���[�V�����N���X
class Model;
class ExecJudgmentBase;
class ActionBase;

class BehaviorTree
{
public:
	BehaviorTree() :
		m_root(NULL)
	{}
	~BehaviorTree() {}

public:
	enum SELECT_RULE
	{
		NONE,
		PRIORITY,
		SEQUENCE,
		SEQUENTIAL_LOOPING,
		RANDOM,
		ON_OFF,
	};

	//���s�m�[�h�𐄘_����
	NodeBase* Inference(Model* target, BehaviorData* data);
	//�V�[�P���X�m�[�h���琄�_�J�n
	NodeBase* SequenceBack(NodeBase* sequence_node, Model* target, BehaviorData* data);
	//�m�[�h�ǉ�
	void AddNode(std::string search_name, std::string entry_name, int priority, SELECT_RULE select_rule, ExecJudgmentBase* judgment, ActionBase* action);
	//�c���[�\����\��
	void PrintTree();
	//���s
	NodeBase* Run(Model* target, NodeBase* action_node, BehaviorData* data);
private:
	NodeBase* m_root;
};