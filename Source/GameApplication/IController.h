#ifndef ENTITYSTACK_H  
#define ENTITYSTACK_H
#endif
#pragma once
#include "Constants.h"
#include "EntityStack.h"
#include "StackNode.h"

class IController
{
public:
	EntityStack* entityStack;
	IController(void);
	virtual ~IController(void);
	virtual void MapTriggers(VInputMap* inputMap){}
	virtual void Run(VInputMap* inputMap){}
protected:
	/*static*/ 
	VisBaseEntity_cl* AddSphere();
	/*static*/ 
	VisBaseEntity_cl* AddCube();
	/*static*/ 
	VisBaseEntity_cl* AddRagdoll();
	/*static*/ 
	void RemoveLast(void);   //Removes the last entity added.
};

