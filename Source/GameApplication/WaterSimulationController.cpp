#include "GameApplicationPCH.h"
#include "WaterSimulationController.h"
#include <time.h>

double time_counter = 0;
clock_t current_time;
clock_t previous_time;

WaterSimulationController::WaterSimulationController(void)
{
	current_time = clock();
	previous_time = current_time;
	menuMode = true;
	menuDisplayed = false;
	autoMode = false;

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
	
		if(menuMode){
		if(menuDisplayed){
			// User clicked accept
			if(this->dialog->GetDialogResult() == 42){
				//this->userInputBalls = atoi((((VTextControl *)this->dialog->Items().FindItem(VGUIManager::GetID("Input")))->GetText()));

				// Check if automated mode checkbox was selected
				if (((VCheckBox *)this->dialog->Items().FindItem(VGUIManager::GetID("Input2")))->IsChecked()){
					this->autoMode = true;
				}
				this->spContext->CloseDialog(this->dialog);
				menuMode = false;
				menuDisplayed = false;
			}

		}
		else{
			EnableMenu();
		}
	}
	else{

		if (this->autoMode){
			this->StartAutoMode();
		}
	}
	if(inputMap->GetTrigger(CUSTOM_CONTROL_ONE))
		 this->AddWaterDrop(0, -300, 100, .05f); //x, y, z and scaling values
		
	if(inputMap->GetTrigger(CUSTOM_CONTROL_TWO))
		this->Drain(); //turns drain on/off
	

	return true;
}

void WaterSimulationController::StartAutoMode(){
		current_time = clock();
		if(difftime(current_time,previous_time) > 1000 ){
			previous_time = current_time;
			this->AddWaterDrop(0, -300, 100, .05f);
		}
}

void WaterSimulationController::EnableMenu(){

	this->dialog = spContext->ShowDialog("Assets\\Dialogs\\InputDialog.xml");
	int x = Vision::Video.GetXRes();
	int y = Vision::Video.GetYRes();
	VPushButton* accept = new VPushButton();
	accept->SetPosition(90, 350);
	accept->SetSize(300,75);
	accept->SetEnabled(true);
	accept->SetText("Accept");
	accept->SetDialogResult(42);
	this->dialog->AddControl(accept);

	menuDisplayed = true;
}

void WaterSimulationController::DeInitGUI(){
	this->spContext->CloseDialog(this->dialog);
	this->dialog = NULL;
}

void WaterSimulationController::InitMenu(VAppMenuContext* context){
	spContext = context;
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
