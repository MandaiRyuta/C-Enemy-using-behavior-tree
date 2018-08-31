#pragma once

class NodeBase;
class BehaviorData;

class BehaviorTree
{
public:
	BehaviorTree() {}
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

public:
	BehaviorTree() : 
		m_root(NULL) {}

	//���s�m�[�h�𐄘_����
	NodeBase* Inference();
	//�V�[�P���X�m�[�h���琄�_�J�n
	NodeBase* SequenceBack();
	//�m�[�h�ǉ�
	void AddNode();
	//�c���[�\����\��
	void PrintTree();
	//���s
	NodeBase* Run();
private:
	NodeBase* m_root;
};