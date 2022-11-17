#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Animation.h"

class ModuleBoss : public Module
{
public:
	ModuleBoss(Application* app, bool start_enabled = true);
	virtual ~ModuleBoss();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void SetScore();


public:
	PhysBody* pbody;
	

	SDL_Texture* heart;

	bool bumper1 = false;

	int hits_taken = 0;
	

	

	b2PrismaticJoint* prismatic_joint;

	Animation* currentAnimation = nullptr;
	Animation idleAnim;
	Animation secondAnim;
	Animation thirdAnim;

	
	

};