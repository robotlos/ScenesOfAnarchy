#include "GameApplicationPCH.h"
#include "ParticleRainController.h"
#include <vector>
#include <time.h>


int ballCount = 0;
int camNumber = 0;

// 50 Locations
static hkvVec3 autoModeLocations[] = {hkvVec3(-1600,-600,3000), hkvVec3(-1600,-300,3000), hkvVec3(-1600,0,3000),
							  hkvVec3(-1600,300,3000), hkvVec3(-1600,600,3000), hkvVec3(-1600,900,3000),
							  hkvVec3(-1600,1200,3000), hkvVec3(-1600,1500,3000), hkvVec3(-1600,1800,3000),
							  hkvVec3(-1600,2100,3000), hkvVec3(-1600,2400,3000), hkvVec3(-1600,2700,3000),
                              hkvVec3(-1600,3000,3000), hkvVec3(-1600,3300,3000), hkvVec3(-1600,3600,3000),
							  hkvVec3(-1600,3900,3000), hkvVec3(-1600,4200,3000),hkvVec3(-1600,-600,3000), 
							  
							  hkvVec3(-600,-300,3000), hkvVec3(-600,0,3000),
							  hkvVec3(-600,300,3000), hkvVec3(-600,600,3000), hkvVec3(-600,900,3000),
							  hkvVec3(-600,1200,3000), hkvVec3(-600,1500,3000), hkvVec3(-600,1800,3000),
							  hkvVec3(-600,2100,3000), hkvVec3(-600,2400,3000), hkvVec3(-600,2700,3000),
                              hkvVec3(-600,3000,3000), hkvVec3(-600,3300,3000), hkvVec3(-600,3600,3000),
							  hkvVec3(-600,3900,3000), hkvVec3(-600,4200,3000),

							  hkvVec3(600,-300,3000), hkvVec3(600,0,3000),
							  hkvVec3(600,300,3000), hkvVec3(600,600,3000), hkvVec3(600,900,3000),
							  hkvVec3(600,1200,3000), hkvVec3(600,1500,3000), hkvVec3(600,1800,3000),
							  hkvVec3(600,2100,3000), hkvVec3(600,2400,3000), hkvVec3(600,2700,3000),
                              hkvVec3(600,3000,3000), hkvVec3(600,3300,3000), hkvVec3(600,3600,3000),
							  hkvVec3(600,3900,3000), hkvVec3(600,4200,3000)
							 };



// Used for Automation mode
double timecounter = 0;
clock_t this_time;
clock_t last_time;

ParticleRainController::ParticleRainController(void)
{
	VisBaseEntity_cl *pCamera  = Vision::Game.SearchEntity("cam5");
	Vision::Camera.AttachToEntity(pCamera, hkvVec3(0.0f, 0.0f, 0.0f));
	this_time = clock();
	last_time = this_time;
	menuMode = true;
	menuDisplayed = false;
	this->autoMode = false;
	this->userInputBalls = 0;
	time = 0;
	this->dialog = NULL;
#if defined(_VISION_ANDROID)
	autoButt=NULL;
	normalButt=NULL;
#endif
}


ParticleRainController::~ParticleRainController(void)
{
}

void ParticleRainController::DeInitGUI(){
	if(this->dialog!=NULL){
		this->spContext->CloseDialog(this->dialog);
		this->dialog = NULL;
	}
#if defined(_VISION_ANDROID)
	if(autoButt!=NULL){
	autoButt->DisposeObject();
	normalButt->DisposeObject();
	autoButt=NULL;
	normalButt=NULL;
	}
#endif

}
// For non automated mode
void ParticleRainController::RandomRain(int numOfBalls){
	
	numOfBalls = numOfBalls <= 0 ?  50 : numOfBalls;

	while (ballCount < numOfBalls){
			int randomx = rand() % 6000 - 3255;
			int randomy = rand() % 6000 - 1416;
		
			hkvVec3 spawnLocation = hkvVec3(randomx, randomy, 3000);
			AddSphere(randomx, randomy, 3000);
			++ballCount;
			bodyCount++;
		}
	ballCount = 0;
}

// Use previous locations to spawn balls
void ParticleRainController::RainBalls(int numOfBalls){
	
		
		// Only allow 50 or less balls at a time
		numOfBalls = (numOfBalls <= 0 || numOfBalls > 50) ? 50 : numOfBalls;

		for (int i = 0; i < numOfBalls; i++){
			AddSphere(autoModeLocations[i].x, autoModeLocations[i].y, autoModeLocations[i].z);
			++ballCount;
			bodyCount++;
		}
	
	ballCount = 0;
}
	

void ParticleRainController::StartAutoMode(){
	this_time = clock();
	
	if(time%80 == 0){
		last_time = this_time;
		this->RainBalls(15);
	}
	time++;
	
}

void ParticleRainController::ChangeCam(){
	VisBaseEntity_cl *pCamera;
	switch(camNumber){
	case 0:
		pCamera  = Vision::Game.SearchEntity("cam");
		Vision::Camera.AttachToEntity(pCamera, hkvVec3(0.0f, 0.0f, 0.0f));
		camNumber++; break;
	case 1: 
		pCamera  = Vision::Game.SearchEntity("cam1");
		Vision::Camera.AttachToEntity(pCamera, hkvVec3(0.0f, 0.0f, 0.0f));
		camNumber++; break;
	case 2: 
		pCamera  = Vision::Game.SearchEntity("cam2");
		Vision::Camera.AttachToEntity(pCamera, hkvVec3(0.0f, 0.0f, 0.0f));
		camNumber++; break;
	case 3: 
		pCamera  = Vision::Game.SearchEntity("cam3");
		Vision::Camera.AttachToEntity(pCamera, hkvVec3(0.0f, 0.0f, 0.0f));
		camNumber++; break;
	case 4: 
		pCamera  = Vision::Game.SearchEntity("cam4");
		Vision::Camera.AttachToEntity(pCamera, hkvVec3(0.0f, 0.0f, 0.0f));
		camNumber++; break;
	case 5: 
		pCamera  = Vision::Game.SearchEntity("cam5");
		Vision::Camera.AttachToEntity(pCamera, hkvVec3(0.0f, 0.0f, 0.0f));
		camNumber = 0; break;
	default: break;
	}
}


bool ParticleRainController::Run(VInputMap* inputMap){
	
	
	if(menuMode){
		if(menuDisplayed){
			// User clicked accept
#if defined(WIN32)
			if(this->dialog->GetDialogResult() == VGUIManager::GetID("Enter")){
				
				// Check if automated mode checkbox was selected
				if (((VCheckBox *)this->dialog->Items().FindItem(VGUIManager::GetID("CheckBox")))->IsChecked()){
					this->autoMode = true;
				}
				this->DeInitGUI();
				menuMode = false;
				menuDisplayed = false;
			}
#endif
#if defined(_VISION_ANDROID)
			int width = Vision::Video.GetXRes();
	int height = Vision::Video.GetYRes();
	float mid = width /2.0;
			if(inputMap->GetTrigger(CUSTOM_CONTROL_THREE)){
				this->autoMode = true;
				this->DeInitGUI();
				inputMap->UnmapInput(CUSTOM_CONTROL_THREE);
				inputMap->UnmapInput(CUSTOM_CONTROL_FOUR);
				menuMode = false;
				menuDisplayed = false;
				VTouchArea* toggleCamera = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(width*.8, (float)height * 0.6f-30, (float)width*.8+150, (float)height * 0.6f+30), -900.0f);
				inputMap->MapTrigger(CUSTOM_CONTROL_TWO, toggleCamera, CT_TOUCH_ANY);
				AddButton("\\Textures\\ChangeCam.png", width*.8, (float)height * 0.6f-30, 0,0);
			}
			if(inputMap->GetTrigger(CUSTOM_CONTROL_FOUR)){
				this->autoMode = false;
				this->DeInitGUI();
				inputMap->UnmapInput(CUSTOM_CONTROL_THREE);
				inputMap->UnmapInput(CUSTOM_CONTROL_FOUR);
				menuMode = false;
				menuDisplayed = false;
				VTouchArea* toggleCamera = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(width*.8, (float)height * 0.6f-30, (float)width*.8+150, (float)height * 0.6f+30), -900.0f);
				inputMap->MapTrigger(CUSTOM_CONTROL_TWO, toggleCamera, CT_TOUCH_ANY);
				AddButton("\\Textures\\ChangeCam.png", width*.8, (float)height * 0.6f-30, 0,0);
				VTouchArea* addBallsArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(width*.8, (float)height * 0.3f-30, (float)width*.8+150, (float)height * 0.3f+30), -900.0f);
				inputMap->MapTrigger(CUSTOM_CONTROL_ONE, addBallsArea, CT_TOUCH_ANY);
				AddButton("\\Textures\\Drop.png", width*.8, (float)height * 0.3f-30, 0,0);
			}
#endif

		}
		else{
			this->ChangeCam();
			EnableMenu(inputMap);
		}
	}
	else{
		
		if (this->autoMode){
			this->StartAutoMode();
		}
		else{
			if(inputMap->GetTrigger(CUSTOM_CONTROL_ONE)){
				this->RandomRain(15);
			}
		}
	}

	

	if(inputMap->GetTrigger(CUSTOM_CONTROL_TWO)){
		this->ChangeCam();
	}
	return true;
}

void ParticleRainController::EnableMenu(VInputMap* inputMap){
#if defined(WIN32)
	this->dialog = spContext->ShowDialog("Assets\\CheckBoxDialog.xml");
	
#endif
	int width = Vision::Video.GetXRes();
	int height = Vision::Video.GetYRes();
	float mid = width /2.0;

#if defined(_VISION_ANDROID)
	VTouchArea* autoMode = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(mid-75, (float)height*.25f, mid+75, (float)height*.25f+60), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_THREE, autoMode, CT_TOUCH_ANY);
	autoButt = AddButton("\\Textures\\Auto.png", (int)mid-75, height*.25f, 0,0);
	VTouchArea* dropMode = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(mid-75, (float)height*.75f, mid+75, (float)height*.75f+60), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_FOUR, dropMode, CT_TOUCH_ANY);
	normalButt = AddButton("\\Textures\\Drop.png", (int)mid-75, height*.75f, 0,0);
#endif


	menuDisplayed = true;
}

void ParticleRainController::InitMenu(VAppMenuContext* context){
	spContext = context;
}

void ParticleRainController::MapTriggers(VInputMap* inputMap){
#if defined(WIN32)
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, V_KEYBOARD, VInputControl::CT_KB_UP, VInputOptions::Once());
	inputMap->MapTrigger(CUSTOM_CONTROL_TWO, V_KEYBOARD, VInputControl::CT_KB_DOWN, VInputOptions::Once());

#endif

#if defined(_VISION_ANDROID)
	int width = Vision::Video.GetXRes();
	int height = Vision::Video.GetYRes();
	float mid = width /2.0;





#endif
}