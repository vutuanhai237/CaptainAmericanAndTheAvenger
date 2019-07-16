#include "DataCollect.h"

DataCollect* DataCollect::instance = NULL;


DataCollect::DataCollect()
{
}


DataCollect * DataCollect::GetInstance()
{
	if (instance == NULL) instance = new DataCollect();
	return instance;
}

void DataCollect::SetIsDashing(bool isdashing)
{
	this->isDashing = isdashing;
}

bool DataCollect::GetIsDashing()
{
	return isDashing;
}

DataCollect::~DataCollect()
{
}
