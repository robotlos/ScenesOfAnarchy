#pragma once
#include "IController.h"
#if defined(_VISION_ANDROID)
#include <Vision/Runtime/Base/Input/VInputAndroid.hpp>
#endif
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokPhysicsModule.hpp>

#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/Input/VFreeCamera.hpp>
class MazeCraze : public IController
{
public:
	MazeCraze(void);
	~MazeCraze(void);

	virtual void MapTriggers(VInputMap* inputMap) HKV_OVERRIDE;
	virtual bool Run(VInputMap* inputMap) HKV_OVERRIDE;

	virtual VisBaseEntity_cl* AddBall(float x, float y, float z, float scaling);

};

