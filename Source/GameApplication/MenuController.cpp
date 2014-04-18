#include "GameApplicationPCH.h"
#include "MenuController.h"
#include "Constants.h"
#include <string>
#include <iostream>
MenuController::MenuController(void)
{

}

MenuController::MenuController(VAppMenuContext* c){
	this->spContext = c;
	this->enabled = false;
	VGUIManager::GlobalManager().LoadResourceFile("Assets\\MenuSystem.xml");
	this->m_pMainMenuDialog = NULL;
}


MenuController::~MenuController(void)
{
}
#if defined(_VISION_ANDROID)
void MenuController::AndroidMenu(VInputMap* inputMap){
	char* texturePaths[4]= {"\\Textures\\gravroom.png","\\Textures\\tod.png","\\Textures\\pr.png","\\Textures\\tumb.png"}; 
	int x = Vision::Video.GetXRes();
	int y = Vision::Video.GetYRes();
	
	//AddButton("\\GravityRoomGUI\\button.tga", width*.8, height/2-75, width, height/2+75);
	
		int pos =  y * 1/6 + y/20;
		VTouchArea* area = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef( 0, pos, x/2.0, 75), -900.0f);
		inputMap->MapTrigger(GR, area, CT_TOUCH_ANY, VInputOptions::Once());
		this->AddButton("\\Textures\\gravroom.png", 0, pos, 0, 0);
		pos =  y * 2/6 + y/20;
		VTouchArea* area2 = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef( 0, pos, x/2.0, 75), -900.0f);
		inputMap->MapTrigger(TOD, area2, CT_TOUCH_ANY, VInputOptions::Once());
		this->AddButton("\\Textures\\tod.png", 0, pos, 0, 0);
		pos =  y * 3/6 + y/20;
		VTouchArea* area3 = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef( 0, pos, x/2.0, 75), -900.0f);
		inputMap->MapTrigger(PR, area3, CT_TOUCH_ANY, VInputOptions::Once());
		this->AddButton("\\Textures\\pr.png", 0, pos, 0, 0);
		pos =  y * 4/6 + y/20;
		VTouchArea* area4 = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef( 0, pos, x/2.0, 75), -900.0f);
		inputMap->MapTrigger(TUM, area4, CT_TOUCH_ANY, VInputOptions::Once());
		this->AddButton("\\Textures\\tumb.png", 0, pos, 0, 0);
	
}
#endif
void MenuController::Enable(VInputMap* inputMap){
	//VDialogCollection openDialogs = spContext->
	//for(int i = 0; i < openDialogs.Count(); i++){
		//spContext->CloseDialog(openDialogs.GetAt(i));
	//}
	
	this->enabled=true;
#if defined(WIN32)
	this->m_pMainMenuDialog = spContext->ShowDialog("Assets\\MainMenu.xml");
	/*Screen Dimensions */
	int x = Vision::Video.GetXRes();
	int y = Vision::Video.GetYRes();

	/* Create Buttons */
	VPushButton* buttonGR = new VPushButton();
	VPushButton* buttonToD = new VPushButton();
	VPushButton* buttonScene3 = new VPushButton();
	VPushButton* buttonScene4 = new VPushButton();
	//VPushButton* buttonScene5 = new VPushButton();
	//VPushButton* buttonScene6 = new VPushButton();

	VPushButton* buttonArray[4] = {buttonGR, buttonToD, buttonScene3, buttonScene4};//, buttonScene5, buttonScene6};
	char *sceneNames[4] = {"Gravity Room", "Tower of Doom", "Particle Rain", "Tumbler"};//, "Car Derby", "Water Simulation"};

	for(int i = 0; i < 4; i++){
		buttonArray[i]->SetPosition(0, y * i/6 + y/20);		
		buttonArray[i]->SetText(sceneNames[i]);
		buttonArray[i]->SetSize(x, y/20);		
		buttonArray[i]->SetDialogResult(i+1);	//every scene has a dialog result used for loading call
		buttonArray[i]->SetEnabled(true); //not sure if this is necessary

		buttonArray[i]->Text().SetFont(Vision::Fonts.FindFont("MenuFont"));
		buttonArray[i]->Text().SetColor(VColorRef (50,50,255,255));
		
		buttonArray[i]->Text().SetHorizontalAlignment(VisFont_cl::ALIGN_CENTER);
		buttonArray[i]->Text().SetVerticalAlignment(VisFont_cl::ALIGN_CENTER);
		
		m_pMainMenuDialog->AddControl(buttonArray[i]);
	}
#endif

#if defined(_VISION_ANDROID)
	AndroidMenu(inputMap);
#endif

}

void MenuController::AddButton(char* buttonImage, int x, int y, int width, int height){
	VisScreenMask_cl *butt = new VisScreenMask_cl();
	butt->LoadFromFile(buttonImage);
	butt->SetPos(x,y);
	if(width !=0 && height !=0){
		butt->SetTargetSize(width, height);
	}
}


void MenuController::Disable(){
	if(this->m_pMainMenuDialog != NULL){
	this->spContext->CloseDialog(this->m_pMainMenuDialog);
	this->m_pMainMenuDialog = NULL;
	this->enabled = false;
	}
}

int MenuController::DialogResultToSceneID(int dialogResults){
/*	if(dialogResults == 1){ //Gravity Room = 1
		return GRAVITY_ROOM;
	}
	else if(dialogResults == 2){ //Tower of Doom = 2
		return TOWER_OF_DOOM;
	}
	//TODO: add cases 3-6
	else if(dialogResults == 6){
		return WATER_SIMULATION;
	}*/
	return MAIN_MENU;
}
int MenuController::Run(VInputMap* inputMap){
#if defined(WIN32)
	return this->m_pMainMenuDialog->GetDialogResult(); //nothing else is really necessary besides this
#endif

#if defined(_VISION_ANDROID)
	if(inputMap->GetTrigger(GR)){
		return 1;
	}
	if(inputMap->GetTrigger(TOD)){
		return 2;
	}
	if(inputMap->GetTrigger(PR)){
		return 3;
	}
	if(inputMap->GetTrigger(TUM)){
		return 4;
	}
	return 0;
#endif
}

void MenuController::BackButton(){
	
}
