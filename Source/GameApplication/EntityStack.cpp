#pragma once
#include "GameApplicationPCH.h"
#include "EntityStack.h"


EntityStack::EntityStack(void)
{
	length = 0;
	first = NULL;
}
	
EntityStack::~EntityStack(void)
{
	VisBaseEntity_cl temp;
	while(length>0)
	{
		temp = *pop();
		temp.Remove();
	}
}


	
VisBaseEntity_cl* EntityStack::pop()
{
	StackNode* pNode = popNode();
	if(pNode != NULL) 
	{
		StackNode node = *pNode;
		VisBaseEntity_cl* entity = node.StackNode::getDataPnter();
		return entity;
	}
	else
	{
		return NULL;
	}
}
	
StackNode* EntityStack::popNode()
{
	if (length > 0) 
	{
		length--;
		StackNode* temp = first;
		first = (*temp).getNext();
		return temp;
	}
	else
	{
		return NULL;
	}
}

	
void EntityStack::push(VisBaseEntity_cl* new_first)
{
	StackNode *first_node;
	if(first == NULL)
	{
		first_node = new StackNode(new_first);
	}
	else
	{
		first_node = new StackNode(new_first, first);
	}
	first = first_node;
	length++;
}

/*
void EntityStack::pushNode(StackNode* new_first)
{

}
*/
	
VisBaseEntity_cl* EntityStack::peek()
{
	StackNode temp = *first;
	return temp.getDataPnter();
}
	
StackNode* EntityStack::peekNode()
{
	return first;
}

	
int EntityStack::getLength()
{
	return length;
}