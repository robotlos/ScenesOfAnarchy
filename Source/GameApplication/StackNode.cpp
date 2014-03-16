#pragma once;
#include "GameApplicationPCH.h"
#include "StackNode.h"

StackNode::StackNode(VisBaseEntity_cl* dp)
{
	dataPointer = dp;
	next = NULL;
}

StackNode::StackNode(VisBaseEntity_cl* dp, StackNode* old_first)
{
	dataPointer = dp;
	next = old_first;
}
	

StackNode::~StackNode(void)
{
}
	

StackNode* StackNode::getNext()
{
	return next;
}

VisBaseEntity_cl* StackNode::getDataPnter()
{
	return dataPointer;
}