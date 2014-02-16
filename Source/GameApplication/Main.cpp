/*
*
* Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
* prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
* Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
*
*/

#include "GameApplicationPCH.h"
#include <Vision/Runtime/Framework/VisionApp/VAppImpl.hpp>

#include <Vision/Runtime/Framework/VisionApp/Modules/VHelp.hpp>
#include "IController.h"
#include "GravityRoomController.h"
// Use the following line to initialize a plugin that is statically linked.
// Note that only Windows platform links plugins dynamically (on Windows you can comment out this line).
VIMPORT IVisPlugin_cl* GetEnginePlugin_GamePlugin();




class ProjectTemplateApp : public VAppImpl
{
public:
	//changes by carlos
	enum State{
		MAIN_MENU_STATE,
		GAME_STATE
	};
//end changes by carlos
	ProjectTemplateApp() 
	//changes by carlos
	: m_state(MAIN_MENU_STATE)
	, m_pMainMenuDialog(NULL)
	//end changes by carlos
	{}
	virtual ~ProjectTemplateApp() {}

	virtual void SetupAppConfig(VisAppConfig_cl& config) HKV_OVERRIDE;
	virtual void PreloadPlugins() HKV_OVERRIDE;

	virtual void Init() HKV_OVERRIDE;
	virtual void AfterSceneLoaded(bool bLoadingSuccessful) HKV_OVERRIDE;
	virtual bool Run() HKV_OVERRIDE;
	virtual void DeInit() HKV_OVERRIDE;
	void UpdateFPS();
	IController* controller;
	float m_iFrameCounter;
	float m_fTimeAccumulator;
	float m_fCurrentFrameTime;
	float m_fCurrentFps;

	///changes by carlos
	bool changeScene(int iDlgResult, VDialog* m_pMainMenuDialog);
	bool runGame();
	bool exitScene();
	void initMenu();
	bool is_TowerOfDoom;
	bool is_GravityRoom;
	void addButtons();
	private:
	State m_state;
	VDialog* m_pMainMenuDialog;
	///end changes by carlos
};

VAPP_IMPLEMENT_SAMPLE(ProjectTemplateApp);

void ProjectTemplateApp::SetupAppConfig(VisAppConfig_cl& config)
{
	// Set custom file system root name ("havok_sdk" by default)
	config.m_sFileSystemRootName = "template_root";

	// Set the initial starting position of our game window and other properties
	// if not in fullscreen. This is only relevant on windows
	config.m_videoConfig.m_iXRes = 1280; // Set the Window size X if not in fullscreen.
	config.m_videoConfig.m_iYRes = 720;  // Set the Window size Y if not in fullscreen.
	config.m_videoConfig.m_iXPos = 50;   // Set the Window position X if not in fullscreen.
	config.m_videoConfig.m_iYPos = 50;   // Set the Window position Y if not in fullscreen.

	// Name to be displayed in the windows title bar.
	config.m_videoConfig.m_szWindowTitle = "StandAlone Project Template";

	config.m_videoConfig.m_bWaitVRetrace = true;

	// Fullscreen mode with current desktop resolution

#if defined(WIN32)
	/*
	DEVMODEA deviceMode;
	deviceMode = Vision::Video.GetAdapterMode(config.m_videoConfig.m_iAdapter);
	config.m_videoConfig.m_iXRes = deviceMode.dmPelsWidth;
	config.m_videoConfig.m_iYRes = deviceMode.dmPelsHeight;
	config.m_videoConfig.m_bFullScreen = true;
	*/
#endif

}

void ProjectTemplateApp::PreloadPlugins()
{
	// Use the following line to load a plugin. Remember that, except on Windows platform, in addition
	// you still need to statically link your plugin library (e.g. on mobile platforms) through project
	// Properties, Linker, Additional Dependencies.
	VISION_PLUGIN_ENSURE_LOADED(GamePlugin);
}

//---------------------------------------------------------------------------------------------------------
// Init function. Here we trigger loading our scene
//---------------------------------------------------------------------------------------------------------
void ProjectTemplateApp::Init()
{
	m_iFrameCounter=0;
	m_fTimeAccumulator=0;
	m_fCurrentFrameTime=0;
	m_fCurrentFps=0;

	// Set filename and paths to our stand alone version.
	// Note: "/Data/Vision/Base" is always added by the sample framework
	
	//changes by carlos
	/*        changes by carlos
	VisAppLoadSettings settings("Scenes/GravityRoom.vscene");

	settings.m_customSearchPaths.Append(":template_root/Assets");
	LoadScene(settings);*/

		initMenu();
		// Prepare the world in order to have skinning shaders for the render to texture menu
	Vision::InitWorld();

	//end changes by carlos

}
//added by Bardia
void ProjectTemplateApp::addButtons(){

#if defined(_VISION_ANDROID)
	int width = Vision::Video.GetXRes();
	int height = Vision::Video.GetYRes();

	VisScreenMask_cl *addCube = new VisScreenMask_cl();
	addCube->LoadFromFile("\\GravityRoomGUI\\button.tga");
	addCube->SetPos(width *.85, height * .10 );

	VisScreenMask_cl *deleteLast = new VisScreenMask_cl();
	deleteLast->LoadFromFile("\\GravityRoomGUI\\button.tga");
	deleteLast->SetPos(width *.10, height * .10 );

	VisScreenMask_cl *addRagdoll = new VisScreenMask_cl();
	addRagdoll->LoadFromFile("\\GravityRoomGUI\\button.tga");
	addRagdoll->SetPos(width *.85, height * .85 );

	VisScreenMask_cl *addSphere = new VisScreenMask_cl();
	addSphere->LoadFromFile("\\GravityRoomGUI\\button.tga");
	addSphere->SetPos(width *.10, height * .85 );

#endif

}

//changes by carlos
void ProjectTemplateApp::initMenu(){
	Vision::Error.SetReportStatus(FALSE);
	Vision::ResourceSystem.SetReportSurvivingResources(FALSE);
	VAppMenuContextPtr spContext = GetContext();
	VGUIManager::GlobalManager().LoadResourceFile("Assets\\MenuSystem.xml");
	m_pMainMenuDialog = spContext->ShowDialog("Assets\\MainMenu.xml");
}
//end changes by carlos
//---------------------------------------------------------------------------------------------------------
// Gets called after the scene has been loaded
//---------------------------------------------------------------------------------------------------------
void ProjectTemplateApp::AfterSceneLoaded(bool bLoadingSuccessful)
{
	// Define some help text
	//VArray<const char*> help;
	//help.Append("How to use this demo...");
	//help.Append("");
	//RegisterAppModule(new VHelp(help));

	// Create a mouse controlled camera (set above the ground so that we can see the ground)
	//Vision::Game.CreateEntity("VisMouseCamera_cl", hkvVec3(0.0f, 0.0f, 170.0f));
	// Add other initial game code here
	// [...]

	//changes by carlos
	/*controller = new GravityRoomController();
	controller->MapTriggers(this->GetInputMap());*/
	
	if(is_GravityRoom){
	controller = new GravityRoomController();
	controller->MapTriggers(this->GetInputMap());
	VAppMenuContextPtr spContext = GetContext();
	VGUIManager::GlobalManager().LoadResourceFile("Assets\\MenuSystem.xml");
	m_pMainMenuDialog = spContext->ShowDialog("Assets\\GravityRoomGUI\\MainMenu.xml");
	addButtons();

	//VAppMenuContextPtr spContext = GetContext();
	//VGUIManager::GlobalManager().LoadResourceFile("Assets\\MenuSystem.xml");
	//m_pMainMenuDialog = spContext->ShowDialog("Assets\\GravityRoomGUI\\MainMenu.xml");
	
	}
	else if(is_TowerOfDoom){
	
	controller = new GravityRoomController();
	controller->MapTriggers(this->GetInputMap());
	}
	//end changes by carlos
}
//changes by carlos
bool ProjectTemplateApp::changeScene(int iDlgResult, VDialog* m_pMainMenuDialog){
		GetContext()->CloseDialog(m_pMainMenuDialog);
		m_pMainMenuDialog = NULL;
		m_state = GAME_STATE;
	
	if(iDlgResult == VGUIManager::GetID("LOADGR")){
		VisAppLoadSettings settings("Scenes/GravityRoom.vscene");
		settings.m_customSearchPaths.Append(":template_root/Assets");
		LoadScene(settings);
		is_GravityRoom = true;
		is_TowerOfDoom = false;
		return true;
	}
	else if(iDlgResult == VGUIManager::GetID("LOADTD")){
		VisAppLoadSettings settings("Scenes/TowerOfDoom.vscene");
		settings.m_customSearchPaths.Append(":template_root/Assets");
		LoadScene(settings);
		is_TowerOfDoom = true;
		is_GravityRoom = false;
		return true;
	}
	return false;
}

//end changes by carlos
//changes by carlos
bool ProjectTemplateApp::runGame(){
	if(is_GravityRoom){
		UpdateFPS();
		controller->Run(this->GetInputMap());
		return true;
	}
	else if(is_TowerOfDoom){
		UpdateFPS();
		return true;
	}
}

bool ProjectTemplateApp::exitScene(){
	is_GravityRoom = false;
	is_TowerOfDoom = false;
	initMenu();
	return true;
}


//end changes by carlos
//---------------------------------------------------------------------------------------------------------
// Main Loop of the application until we quit
//---------------------------------------------------------------------------------------------------------
bool ProjectTemplateApp::Run()
{
	//changes by carlos
	/*UpdateFPS();
	controller->Run(this->GetInputMap());
	return true;*/

		switch(m_state){
	case MAIN_MENU_STATE:{
			VASSERT(m_pMainMenuDialog);
			int iDlgResult = m_pMainMenuDialog->GetDialogResult();
			if(iDlgResult){
					return changeScene(iDlgResult, m_pMainMenuDialog);
		}
		return true;
	}

	case GAME_STATE:{
		if(ProjectTemplateApp::GetInputMap()->GetTrigger(VAPP_EXIT))
				return exitScene();

		else
			return runGame();
		}
	} //end switch
return true;
}

void ProjectTemplateApp::UpdateFPS(){
	m_iFrameCounter++;
	m_fTimeAccumulator += Vision::GetUITimer()->GetTimeDifference();

	if (m_fTimeAccumulator >= 1.0f)
	{
		m_fCurrentFrameTime = m_fTimeAccumulator / m_iFrameCounter;
		m_fCurrentFps = m_iFrameCounter / m_fTimeAccumulator;

		m_fTimeAccumulator = 0.0f;
		m_iFrameCounter = 0;
	}
	Vision::Message.Print(1, 10, Vision::Video.GetYRes() - 35, "FPS : %.1f\nFrame Time : %.2f", m_fCurrentFps, m_fCurrentFrameTime * 1000.0f);
}


void ProjectTemplateApp::DeInit()
{
	// De-Initialization
	// [...]
	//changes by carlos
		VGUIManager::GlobalManager().CleanupResources();
	m_pMainMenuDialog = NULL;
	//end changes by carlos
}

/*
* Havok SDK - Base file, BUILD(#20131218)
* 
* Confidential Information of Havok.  (C) Copyright 1999-2013
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
* 
* Use of this software for evaluation purposes is subject to and indicates
* acceptance of the End User licence Agreement for this product. A copy of
* the license is included with this software and is also available from salesteam@havok.com.
* 
*/
