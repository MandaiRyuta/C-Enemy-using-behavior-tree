#pragma once
#include <string>
class NodeBase;
class BehaviorData;

//モデルの形状＆判定＆モーションクラス
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

	//実行ノードを推論する
	NodeBase* Inference(Model* target, BehaviorData* data);
	//シーケンスノードから推論開始
	NodeBase* SequenceBack(NodeBase* sequence_node, Model* target, BehaviorData* data);
	//ノード追加
	void AddNode(std::string search_name, std::string entry_name, int priority, SELECT_RULE select_rule, ExecJudgmentBase* judgment, ActionBase* action);
	//ツリー構造を表示
	void PrintTree();
	//実行
	NodeBase* Run(Model* target, NodeBase* action_node, BehaviorData* data);
private:
	NodeBase* m_root;
};