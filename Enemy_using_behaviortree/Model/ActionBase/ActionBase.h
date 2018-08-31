#pragma once

class Model;

class ActionBase
{
public:
	enum STATE
	{
		RUN,		//���s��
		FAILED,		//���s���s
		COMPLETE,	//���s����	
	};
	//���s�����i�������z�֐��j
	virtual STATE Run(Model* target) = 0;
};