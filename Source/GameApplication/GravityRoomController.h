#pragma once
#include "IController.h"
#if defined(_VISION_ANDROID)
#include <Vision/Runtime/Base/Input/VInputAndroid.hpp>
#endif
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokPhysicsModule.hpp>
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokContactListener.hpp>

#include "myCollisionListener.h"

class GravityRoomController : public IController{
public:
	GravityRoomController(void);
	virtual ~GravityRoomController(void);
	virtual void MapTriggers(VInputMap* inputMap) HKV_OVERRIDE;
	hkpContactListener* collListener;
	virtual bool Run(VInputMap* inputMap) HKV_OVERRIDE;
private:
#if defined(_VISION_ANDROID)
	VMotionInputAndroid* pMotionInput;
#endif
	vHavokPhysicsModule* pMod;
	hkpWorld* myWorld;
};

