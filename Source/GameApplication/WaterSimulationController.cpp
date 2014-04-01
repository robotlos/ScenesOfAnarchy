#include "GameApplicationPCH.h"
#include "WaterSimulationController.h"

WaterSimulationController::WaterSimulationController(void)
{
	
#if defined(_VISION_ANDROID) //free camera for android (joystick/finger camera)
	VisBaseEntity_cl* pCam = Vision::Game.CreateEntity("VFreeCamera", hkvVec3::ZeroVector());
	pCam->SetPosition(-290, -220, 680); //spawns with same coordinates as windows
	pCam->SetOrientation(20, 67, 19);

#endif
#if defined(WIN32)
	VisBaseEntity_cl *pCamera  = Vision::Game.SearchEntity("tankcamera");
	Vision::Camera.AttachToEntity(pCamera, hkvVec3::ZeroVector());

#endif	
	/*#if defined(_VISION_ANDROID)
	pMod = static_cast<vHavokPhysicsModule*>(vHavokPhysicsModule::GetInstance());
	pMotionInput = (VMotionInputAndroid*)(&VInputManager::GetInputDevice(INPUT_DEVICE_MOTION_SENSOR));
	pMotionInput->SetEnabled(true);
	#endif*/
}
bool WaterSimulationController::Run(VInputMap* inputMap){

	if(inputMap->GetTrigger(CUSTOM_CONTROL_ONE))
		 this->AddWaterDrop(0, -300, 100, .05f); //x, y, z and scaling values
		
	if(inputMap->GetTrigger(CUSTOM_CONTROL_TWO))
		this->Drain(); //turns drain on/off
	

	return true;
}


WaterSimulationController::~WaterSimulationController(void)
{
}
void WaterSimulationController::MapTriggers(VInputMap* inputMap){
#if defined(WIN32)
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, V_KEYBOARD, VInputControl::CT_KB_UP); 
	inputMap->MapTrigger(CUSTOM_CONTROL_TWO, V_KEYBOARD, VInputControl::CT_KB_DOWN, VInputOptions::Once()); 
#endif

#if defined(_VISION_ANDROID)
	int width = Vision::Video.GetXRes();
	int height = Vision::Video.GetYRes();
	VTouchArea* addRagdollArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef((float)width *.8f, (float)height * 0 , (float)width , (float)height * .2f), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, addRagdollArea, CT_TOUCH_ANY);

	VTouchArea* addCubeArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(0.0f, (float)height*.8f, (float)width*.2f, (float)height), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_TWO, addCubeArea, CT_TOUCH_ANY);
#endif 
}

//////////////////////////// Water Simulation Controls //////////////////////////////////////////////////////////////
VisBaseEntity_cl* WaterSimulationController::AddWaterDrop(float x, float y, float z, float scaling){
	VisBaseEntity_cl *ent = Vision::Game.CreateEntity("VisBaseEntity_cl", hkvVec3(x, y, z), "Assets\\Models\\Misc\\Sphere.Model");
	ent->SetScaling(scaling);
	vHavokRigidBody *sphere = new vHavokRigidBody();
	sphere->Havok_TightFit = true;
	sphere->Havok_Restitution = .35f;
	ent->AddComponent(sphere);
	return ent;
}

void WaterSimulationController::Drain(){ 
		TriggerBoxEntity_cl *triggerbox = vdynamic_cast <TriggerBoxEntity_cl *> (Vision::Game.SearchEntity("triggerbox")); 

		if(triggerbox->IsEnabled()) //if trigger box is enabled
			triggerbox->SetEnabled(false); //disable it

		else if(!triggerbox->IsEnabled()) //if trigger box is disabled
			triggerbox->SetEnabled(true); //enable it
}

//////////////////////// End Water Simulation Controls ////////////////////////////////////////////////////////
