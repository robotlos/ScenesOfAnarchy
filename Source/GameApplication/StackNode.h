#pragma once
#include <Vision/Runtime/Engine/SceneElements/VisApiBaseEntity.hpp>
#include "StackNode.h"
//#include "GameApplicationPCH.h"

class StackNode
{
public:
	StackNode(VisBaseEntity_cl* dp);
	StackNode(VisBaseEntity_cl* dp, StackNode* old_first);
	~StackNode(void);
	StackNode* getNext();
	VisBaseEntity_cl* getDataPnter();

protected:
	StackNode* next;
	VisBaseEntity_cl* dataPointer;

};