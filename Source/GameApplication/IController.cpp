#include "GameApplicationPCH.h"
#include "IController.h"
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokPhysicsModule.hpp>
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokRagdoll.hpp>


IController::IController(void)
{
}


IController::~IController(void)
{
}


VisBaseEntity_cl* IController::AddRagdoll(){
	VisBaseEntity_cl *ent = Vision::Game.CreateEntity("VisBaseEntity_cl", hkvVec3(-100.0f, 5, 100), "Models\\Warrior\\Warrior.model");
	vHavokRagdoll *ragdoll = new vHavokRagdoll();
	ragdoll->SetRagdollCollisionFile("Models\\Warrior\\WarriorRagdoll.hkt");
	ent->AddComponent(ragdoll);
	return ent;
}

VisBaseEntity_cl* IController::AddSphere(){
	VisBaseEntity_cl *ent = Vision::Game.CreateEntity("VisBaseEntity_cl", hkvVec3(-100.0f, -30, 100), "Models\\Misc\\Sphere.Model");
	vHavokRigidBody *sphere = new vHavokRigidBody();
	sphere->Havok_TightFit = true;
	sphere->Havok_Restitution = 1.0f;
	ent->AddComponent(sphere);
	return ent;
}

VisBaseEntity_cl* IController::AddCube(){
	VisBaseEntity_cl *ent = Vision::Game.CreateEntity("VisBaseEntity_cl", hkvVec3(-100.0f, 30, 100), "Models\\Misc\\Cube.Model");
	vHavokRigidBody *cube = new vHavokRigidBody();
	cube->Havok_TightFit = true;
	ent->AddComponent(cube);
	return ent;
}