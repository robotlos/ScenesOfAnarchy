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
}


ParticleRainController::~ParticleRainController(void)
{
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
		}
	
	ballCount = 0;
}
	

void ParticleRainController::StartAutoMode(){
	this_time = clock();
	
	if (difftime(this_time, last_time) > 2500){
		last_time = this_time;
		this->RainBalls(this->userInputBalls);
	}
	
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
			if(this->dialog->GetDialogResult() == 42){
				this->userInputBalls = atoi((((VTextControl *)this->dialog->Items().FindItem(VGUIManager::GetID("Input")))->GetText()));
				
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

	

	if(inputMap->GetTrigger(CUSTOM_CONTROL_ONE)){
		this->RandomRain(this->userInputBalls);
	}
	if(inputMap->GetTrigger(CUSTOM_CONTROL_TWO)){
		this->ChangeCam();
	}
	return true;
}

void ParticleRainController::EnableMenu(){

	this->dialog = spContext->ShowDialog("Assets\\Dialogs\\InputDialog.xml");
	int x = Vision::Video.GetXRes();
	int y = Vision::Video.GetYRes();
	//To properly scale the dialog box grab input object
	//this->dialog->Items().FindItem(//Find input by id);
	/*
	VImageControl* logo = new VImageControl();
	logo->SetPosition(50,50);
	logo->SetSize(300,75);
	logo->Image().SetTexture(Vision::TextureManager.Load2DTexture("Assets\\Dialogs\\TOD.png"));
	this->dialog->AddControl(logo);
	*/
	VPushButton* accept = new VPushButton();
	accept->SetPosition(90, 350);
	accept->SetSize(300,75);
	accept->SetEnabled(true);
	accept->SetText("Accept");
	accept->SetDialogResult(42);
	this->dialog->AddControl(accept);
	
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
	
	VTouchArea* addBallsArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(0.0f, (float)height * 0.5f, (float)width, (float)height), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, addBallsArea, CT_TOUCH_ANY);
	VTouchArea* toggleCamera = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(0.0f, 0.0f, (float)width, (float)height * 0.5f), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_TWO, toggleCamera, CT_TOUCH_ANY);

#endif
}