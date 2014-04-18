#pragma once
#include <Vision\Runtime\Framework\VisionApp\VAppModule.hpp>
#if defined(_VISION_ANDROID)
#include <Vision/Runtime/Base/Input/VInputAndroid.hpp>
#include "Constants.h"
#endif
class MenuController
{
public:
	MenuController(void);
	MenuController(VAppMenuContext* c);
	~MenuController(void);
	void Enable(VInputMap* inputMap);
	void Disable();
	int DialogResultToSceneID(int dialogResult);
	int Run(VInputMap* inputMap);
	VAppMenuContext* spContext;
	VDialog* m_pMainMenuDialog;
	bool enabled;
	void BackButton();
#if defined(_VISION_ANDROID)
	void AndroidMenu(VInputMap* inputMap);
#endif
	void AddButton(char* buttonImage, int x, int y, int width, int height);
};

