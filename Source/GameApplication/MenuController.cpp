#include "GameApplicationPCH.h"
#include "MenuController.h"
#include "Constants.h"


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
	int menuResults =MAIN_MENU;

	int dialogResults = this->m_pMainMenuDialog->GetDialogResult();
	if(dialogResults != 0){
		menuResults = DialogResultToSceneID(dialogResults);
	}

	return menuResults;

}