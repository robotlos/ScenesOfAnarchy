#include "GameApplicationPCH.h"
#include "MazeCraze.h"

#define BALL_START_POSITION       
 static int x = 400;
 static int y = 400;
 static int counter = 0;
MazeCraze::MazeCraze(void)
{
	VisBaseEntity_cl *pCamera  = Vision::Game.SearchEntity("camera");
		Vision::Camera.AttachToEntity(pCamera, hkvVec3::ZeroVector());
		pCamera->SetPosition(-20, -25, 930);
		pCamera->SetOrientation(0, 90, 0);
		IController *controller; 
}

bool MazeCraze::Run(VInputMap* inputMap){


	//if(inputMap->GetTrigger(CUSTOM_CONTROL_ONE)){
		
		
		if(counter == 15){
			VisBaseEntity_cl *ball = this->AddSphere(x, y, -50);
			fixBall(ball);
		
			x *= -1;
		}
		else if(counter == 30){
			VisBaseEntity_cl *ball = this->AddSphere(x, y, -50);
			fixBall(ball);
			y *= -1;
		}
		else if(counter == 45){
			VisBaseEntity_cl *ball = this->AddSphere(x, y, -50);
			fixBall(ball);
			x *= -1;
		}
		else if(counter == 60){
			VisBaseEntity_cl *ball = this->AddSphere(x, y, -50);
			fixBall(ball);
			counter = 0;
			y *= -1;
		}
		counter++;
		
	//}
	return true;
}
MazeCraze::~MazeCraze(void)
{
}

VisBaseEntity_cl* MazeCraze::fixBall(VisBaseEntity_cl *ball){
		ball->SetScaling(.4);
		ball->RemoveAllComponents();
		 vHavokRigidBody *sphere = new vHavokRigidBody();
		sphere->Havok_TightFit = true;
		sphere->Havok_Restitution = 1.95f;
		ball->AddComponent(sphere);
	//	sphere->SetLinearVelocity(hkvVec3((rand() % 500), (rand() % 500), 0) );
			sphere->SetLinearVelocity(hkvVec3(35, 35, 10));
		sphere->SetFriction(0.025);
		return ball;
}
void MazeCraze::MapTriggers(VInputMap* inputMap){
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, V_KEYBOARD, VInputControl::CT_KB_UP); 
}

