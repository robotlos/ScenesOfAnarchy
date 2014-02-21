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
}


MenuController::~MenuController(void)
{
}

void MenuController::Enable(){
	this->m_pMainMenuDialog = spContext->ShowDialog("Assets\\MainMenu.xml");
	this->enabled=true;
	
	/*Screen Dimensions */
	int x = Vision::Video.GetXRes();
	int y = Vision::Video.GetYRes();
	/* Enable Buttons */

	VPushButton* buttonGR = new VPushButton();
	VPushButton* buttonToD = new VPushButton();
	VPushButton* buttonScene3 = new VPushButton();
	VPushButton* buttonScene4 = new VPushButton();
	VPushButton* buttonScene5 = new VPushButton();
	VPushButton* buttonScene6 = new VPushButton();

	VPushButton* buttonArray[6] = {buttonGR, buttonToD, buttonScene3, buttonScene4, buttonScene5, buttonScene6};
	char *sceneNames[6] = {"Gravity Room", "Tower of Doom", "Scene 3", "Scene 4", "Scene 5", "Scene 6"};

	for(int i = 0; i < 6; i++){
		buttonArray[i]->SetPosition((x/2) -75, i * y/6);		
		buttonArray[i]->SetText(sceneNames[i]);
		buttonArray[i]->SetSize(150, 30);		
		buttonArray[i]->SetDialogResult(i+1);		
		buttonArray[i]->SetEnabled(true);

		buttonArray[i]->Text().SetFont(Vision::Fonts.FindFont("MenuFont"));
		buttonArray[i]->Text().SetColor(VColorRef (255,255,255,255));
		
		buttonArray[i]->Text().SetHorizontalAlignment(VisFont_cl::ALIGN_CENTER);
		buttonArray[i]->Text().SetVerticalAlignment(VisFont_cl::ALIGN_CENTER);

		m_pMainMenuDialog->AddControl(buttonArray[i]);
	}
}

void MenuController::Disable(){
	this->spContext->CloseDialog(this->m_pMainMenuDialog);
	this->m_pMainMenuDialog = NULL;
	this->enabled = false;
}

int MenuController::DialogResultToSceneID(int dialogResults){
	if(dialogResults == VGUIManager::GetID("LOADGR")){
		return GRAVITY_ROOM;
	}
	else if (dialogResults == VGUIManager::GetID("LOADTD")){
		return TOWER_OF_DOOM;
	}
	return MAIN_MENU;
}
int MenuController::Run(){
	return this->m_pMainMenuDialog->GetDialogResult(); //nothing else is really necessary besides this
}

void MenuController::BackButton(){
	
}
