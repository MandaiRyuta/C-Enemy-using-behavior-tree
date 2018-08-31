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

	//実行ノードを推論する
	NodeBase* Inference();
	//シーケンスノードから推論開始
	NodeBase* SequenceBack();
	//ノード追加
	void AddNode();
	//ツリー構造を表示
	void PrintTree();
	//実行
	NodeBase* Run();
private:
	NodeBase* m_root;
};