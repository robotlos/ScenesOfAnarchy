#pragma once
#include <Vision/Runtime/Engine/SceneElements/VisApiBaseEntity.hpp>
#include "StackNode.h"
#include "EntityStack.h"
#include "Constants.h"

class EntityStack 
{
public:
	EntityStack(void);
	~EntityStack(void);
	VisBaseEntity_cl* pop();
	void push(VisBaseEntity_cl* new_first);
	VisBaseEntity_cl* peek();
	int getLength();


protected:
	StackNode * first;
	int length;
	StackNode* popNode();
	//void pushNode(StackNode* new_first);
	StackNode* peekNode();
	
};