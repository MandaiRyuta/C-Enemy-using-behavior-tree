#pragma once
#include <string>
#include <vector>
#include "../behavior.h"
class NodeBase
{
public:
	NodeBase() {}
	
public:
	//名前のゲッター関数
	std::string GetName()
	{
		return m_name_;
	}
	//親ノードのゲッター
	NodeBase* GetParent()
	{
		return m_Parent_;
	}
	//子ノードのゲッター
	NodeBase* GetChild(int idx)
	{
		if (m_Child_.size() >= idx)
		{
			return NULL;
		}
		return m_Child_[idx];
	}
	//子ノードゲッター（末尾）
	NodeBase* GetLastChild()
	{
		if (m_Child_.size() == 0)
		{
			return NULL;
		}
		return m_Child_[m_Child_.size() - 1];
	}
	//子ノードのゲッター（先頭）
	NodeBase* GetTopChild()
	{
		if (m_Child_.size() == 0)
		{
			return NULL;
		}
		return m_Child_[0];
	}
	//兄弟ノードゲッター
	NodeBase* GetSibling(void)
	{
		return m_Sibling;
	}
	//階層番号ゲッター
	int GetHirerchyNumber()
	{
		return m_HierarchyNumber;
	}
	//優先順位ゲッター
	int GetPriority()
	{
		return m_Priority;
	}
	//親ノードセッター
	void SetParent(NodeBase* parent)
	{
		m_Parent_ = parent;
	}
	//子ノード追加
	void AddChild(NodeBase* child)
	{
		m_Child_.push_back(child);
	}
	//兄弟ノードセッター
	void SetSibling(NodeBase* sibling)
	{
		m_Sibling = sibling;
	}
	//行動データを持っているか
	//bool HasAction()
	//{
	//	return m_Action != NULL ? true : false;
	//}

	bool Judgment();

	NodeBase* SelectPriority(std::vector<NodeBase*> *list);
private:
	std::string m_name_;					//名前
	NodeBase* m_Parent_;					//親ノード
	std::vector<NodeBase* > m_Child_;		//子ノード
	NodeBase* m_Sibling;					//兄弟ノード
	BehaviorTree::SELECT_RULE m_SelectRule; //選択ルール
	//ActionBase* m_Action				//実行クラス
	//ExecJudgmentBase* m_ExecJudgment;	//判定クラス
	unsigned int m_Priority;				//優先順位
	int m_HierarchyNumber;;					//階層番号

};