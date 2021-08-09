#include "AdenWorldManager.h"

AdenWorldManager& AdenWorldManager::GetInstance()
{
	static AdenWorldManager* instance = new AdenWorldManager();
	return *instance;
}

AdenWorldManager::~AdenWorldManager()
{
}

AdenWorldManager::AdenWorldManager()
{
}