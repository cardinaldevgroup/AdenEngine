#ifndef _ADEN_WORLD_MANAGER_H_
#define _ADEN_WORLD_MANAGER_H_

class AdenWorldManager
{
public:
	AdenWorldManager& GetInstance();
	~AdenWorldManager();

private:
	AdenWorldManager();

};

#endif // !_ADEN_WORLD_MANAGER_H_
