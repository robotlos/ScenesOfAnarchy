#pragma once
#include "IController.h"
#if defined(_VISION_ANDROID)
#include <Vision/Runtime/Base/Input/VInputAndroid.hpp>
#endif
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokPhysicsModule.hpp>

class ParticleRainController : public IController
{
public:
	ParticleRainController(void);
	virtual ~ParticleRainController(void);
	virtual void MapTriggers(VInputMap* inputMap) HKV_OVERRIDE;
	virtual bool Run(VInputMap* inputMap) HKV_OVERRIDE;
	virtual void DeInitGUI() HKV_OVERRIDE;
	void RainBalls(int numOfBalls);
	void RandomRain(int numOfBalls);
	void StartAutoMode();
	VDialog* dialog;
	void ChangeCam();
	void InitMenu(VAppMenuContext* context);
	void EnableMenu(VInputMap* inputMap);
	bool menuMode;
	bool menuDisplayed;
	bool autoMode;
	int time;
	VAppMenuContext* spContext;
	int userInputBalls;

#if defined(_VISION_ANDROID)
	vHavokPhysicsModule* pMod;
	VMotionInputAndroid* pMotionInput;
	VisScreenMask_cl* autoButt;
	VisScreenMask_cl* normalButt;
#endif
};

