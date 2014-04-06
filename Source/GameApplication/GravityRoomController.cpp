#pragma once
#include "GameApplicationPCH.h"
#include "GravityRoomController.h"

GravityRoomController::GravityRoomController(void)
{
	VisBaseEntity_cl *pCamera  = Vision::Game.SearchEntity("CameraPosition");
	Vision::Camera.AttachToEntity(pCamera, hkvVec3::ZeroVector());
	//vHavokPhysicsModule *pMod = static_cast<vHavokPhysicsModule*>(vHavokPhysicsModule::GetInstance());
	pMod = static_cast<vHavokPhysicsModule*>(vHavokPhysicsModule::GetInstance());

	myWorld = pMod->GetPhysicsWorld();
	collListener = new myCollisionListener;
	myWorld->markForWrite();
	myWorld->addContactListener(collListener);
	myWorld->unmarkForWrite();
	automate = false;
	time = 0;
	rotate = hkvMat3(1.0f, 0.0f, 0.04, 0.0f, 1.0f, 0.0f, -0.04f, 0.0f, 1.0f);
	pMod->GetGravity(grav);
#if defined(_VISION_ANDROID)
	pMotionInput = (VMotionInputAndroid*)(&VInputManager::GetInputDevice(INPUT_DEVICE_MOTION_SENSOR));
	pMotionInput->SetEnabled(true);
#endif
}


GravityRoomController::~GravityRoomController(void)
{
#if defined(_VISION_ANDROID)
	myWorld->removeContactListener(collListener);
	delete collListener;
#endif
}

bool GravityRoomController::Run(VInputMap* inputMap){
#if defined(_VISION_ANDROID)
	hkvVec3 accel = pMotionInput->GetAcceleration();
	//Multiply it by 1K to increase the intensity
	accel = accel *1000;
	//Havok uses weird axises (axi?) so they had to be swapped and negated
	hkvVec3 gravity = hkvVec3(-1*accel.z,-1*accel.x,accel.y);
	//set the new gravity
	pMod->SetGravity(gravity);
#endif
	if(!automate)
	{
		if(inputMap->GetTrigger(CUSTOM_CONTROL_ONE)){
			this->AddCube();
			//this->RemoveLast();
		}
		if(inputMap->GetTrigger(CUSTOM_CONTROL_TWO)){
			this->AddSphere(-100.0f, -30, 100);
			//this->RemoveLast();
		}
		if(inputMap->GetTrigger(CUSTOM_CONTROL_THREE)){
			this->AddRagdoll(-100.0f, 5, 100);
		}
		if(inputMap->GetTrigger(CUSTOM_CONTROL_FIVE)){
			automate = true;
		}
	}
	else
	{
		autorun();
	}
	return true;
}

void GravityRoomController::MapTriggers(VInputMap* inputMap){

#if defined(WIN32)
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, V_KEYBOARD, VInputControl::CT_KB_UP, VInputOptions::Once());
	inputMap->MapTrigger(CUSTOM_CONTROL_TWO, V_KEYBOARD, VInputControl::CT_KB_DOWN, VInputOptions::Once());
	inputMap->MapTrigger(CUSTOM_CONTROL_THREE, V_KEYBOARD, VInputControl::CT_KB_LEFT, VInputOptions::Once());
	inputMap->MapTrigger(CUSTOM_CONTROL_FOUR, V_KEYBOARD, VInputControl::CT_KB_RIGHT, VInputOptions::Once());
	inputMap->MapTrigger(CUSTOM_CONTROL_FIVE, V_KEYBOARD, VInputControl::CT_KB_HOME, VInputOptions::Once());
#endif
	
#if defined(_VISION_ANDROID)
	int width = Vision::Video.GetXRes();
	int height = Vision::Video.GetYRes();
	VTouchArea* addRagdollArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef((float)width *.8f, (float)height * 0 , (float)width , (float)height * .2f), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, addRagdollArea, CT_TOUCH_ANY);
	AddButton("\\GravityRoomGUI\\cube.tga", width*.8, 0, width*.2, height*.2);
	
	VTouchArea* addCubeArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(0.0f, (float)height*.8f, (float)width*.2f, (float)height), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_TWO, addCubeArea, CT_TOUCH_ANY);
	AddButton("\\GravityRoomGUI\\sphere.tga", 0,height*.8, width*.2, height*.2);
	
	VTouchArea* addSphereArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef((float)width * .8f,(float)height * .8f , (float)width, (float)height), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_THREE, addSphereArea, CT_TOUCH_ANY);
	AddButton("\\GravityRoomGUI\\ragdoll.tga", width*.8, height*.8, width*.2, height*.2);

	VTouchArea* removeLastArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef( 0.0f, 0.0f ,width * .2f , height * .2f ), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_FOUR, removeLastArea, CT_TOUCH_ANY);
	AddButton("\\GravityRoomGUI\\remove.tga", 0, 0, width*.2, height*.2);

	VTouchArea* autorunArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef( width/2-150, height/2-150, width/2+150, height/2+150), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_FIVE, autorunArea, CT_TOUCH_ANY);
	//AddButton("\\GravityRoomGUI\\button.tga", width/2-50, height/2-50, width/2+150, height/2+150);
#endif

}

void GravityRoomController::autorun() {
	if(time == 0)
		pMod->GetGravity(oldGrav);

	grav = rotate * grav;
	pMod->SetGravity(grav);

	if(time%60 == 0)
		this->AddCube();
	if(time%50 == 0)
		this->AddSphere();
	if(time%200 == 0)
		this->AddRagdoll();

	if(time > 3600)
	{
		automate = false;
		pMod->SetGravity(oldGrav);
	}
	time++;
}