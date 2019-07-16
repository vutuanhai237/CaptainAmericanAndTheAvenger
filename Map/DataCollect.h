#pragma once
#include <d3d9.h>
class DataCollect
{
private: 
	DataCollect();
	static DataCollect*instance;
	bool isDashing;
public:
	static DataCollect*GetInstance();

	void SetIsDashing(bool isdashing);
	bool GetIsDashing();
	~DataCollect();
};

