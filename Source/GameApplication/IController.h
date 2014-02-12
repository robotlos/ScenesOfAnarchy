#pragma once
#include "Constants.h"

class IController
{
public:
	IController(void);
	virtual ~IController(void);
	virtual void MapTriggers(VInputMap* inputMap){}
	virtual void Run(VInputMap* inputMap){}
	static void RecordFps(IVFileOutStream* file,float fps);
protected:
	static VisBaseEntity_cl* AddSphere();
	static VisBaseEntity_cl* AddCube();
	static VisBaseEntity_cl* AddRagdoll();
	
};

