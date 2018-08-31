#pragma once

class Model;

class ActionBase
{
public:
	enum STATE
	{
		RUN,		//実行中
		FAILED,		//実行失敗
		COMPLETE,	//実行成功	
	};
	//実行処理（純粋仮想関数）
	virtual STATE Run(Model* target) = 0;
};