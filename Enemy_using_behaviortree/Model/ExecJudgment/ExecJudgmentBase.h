#pragma once

class Model;

class ExecJudgmentBase
{
public:
	virtual bool Judgment(Model* target) = 0;
};