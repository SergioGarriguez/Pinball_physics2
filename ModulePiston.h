#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"
#include "Animation.h"

class ModulePiston : public Module
{
public:
	ModulePiston(Application* app, bool start_enabled = true);
	virtual ~ModulePiston();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	PhysBody* pbody;
	PhysBody* anchor;

	SDL_Texture* veins;
	
	Animation* currentAnimation = nullptr;
	Animation idleAnim;
	Animation secondAnim;
	Animation thirdAnim;

	float aux = 22.0f;

	b2PrismaticJoint* prismatic_joint;
	

};