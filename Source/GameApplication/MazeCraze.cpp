#include "GameApplicationPCH.h"
#include "MazeCraze.h"
#include <cstdlib>

#define BALL_START_POSITION       hkvVec3(392.0f, -207.0f, -50)
	EntityStack *entStack = new EntityStack();


MazeCraze::MazeCraze(void)
{
//#if defined(WIN32)
		VisBaseEntity_cl *pCamera  = Vision::Game.SearchEntity("camera");
		Vision::Camera.AttachToEntity(pCamera, hkvVec3::ZeroVector());
		pCamera->SetPosition(-20, -25, 930);
		pCamera->SetOrientation(0, 90, 0);
		IController *controller; 
		//entStack = new EntityStack();
//#endif	

}

bool MazeCraze::Run(VInputMap* inputMap){


	if(inputMap->GetTrigger(CUSTOM_CONTROL_ONE)){
		VisBaseEntity_cl *tB = Vision::Game.SearchEntity("TriggerBox");
		VASSERT(tB);
		
		
		int x = (rand() % 800) - 400;
		int y = (rand() % 800) - 400;
		VisBaseEntity_cl *ball = this->AddSphere(x, y, -50);
		ball->SetScaling(.4);
		ball->RemoveAllComponents();
		 vHavokRigidBody *sphere = new vHavokRigidBody();
		sphere->Havok_TightFit = true;
		sphere->Havok_Restitution = 1.95f;
		ball->AddComponent(sphere);
		sphere->SetLinearVelocity(hkvVec3((rand() % 500), (rand() % 500), 0) );
		sphere->SetFriction(.05);
		//Vision::Message.Print(200, 200, 0, "Collisions: %d", + sphere->get);
		//this->AddBall(x, y, -50, .40); //x, y, z and scaling values
	}
	return true;
}
MazeCraze::~MazeCraze(void)
{
}

VisBaseEntity_cl* MazeCraze::AddBall(float x, float y, float z, float scaling){
	VisBaseEntity_cl *ball = Vision::Game.CreateEntity("VisBaseEntity_cl", hkvVec3(x, y, -50) , "Assets\\Ball.Model");
		ball->SetScaling(scaling);
		vHavokRigidBody *sphere = new vHavokRigidBody();
		sphere->Havok_TightFit = true;
		sphere->Havok_Restitution = 1.95f;
		ball->AddComponent(sphere);
		sphere->SetLinearVelocity(hkvVec3((rand() % 500), (rand() % 500), 0) );
		sphere->SetFriction(.05);
		entStack->push(ball);
		return ball;
}
void MazeCraze::MapTriggers(VInputMap* inputMap){
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, V_KEYBOARD, VInputControl::CT_KB_UP); 
}

