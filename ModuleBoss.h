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
	void Reset();
	bool IsBeaten();


public:
	PhysBody* pbody;
	PhysBody* pbody2;
	bool exploding = false;
	bool has_exploded = false;
	

	SDL_Texture* saucer;
	SDL_Texture* explosion;


	bool bumper1 = false;

	int hits_taken = 0;

	bool HasSpawned = false;
	bool BossBeaten = false; 
	bool destroy = false;


	uint sfx;
	uint sfx2;
	

	b2PrismaticJoint* prismatic_joint;

	Animation* currentAnimation = nullptr;
	Animation idleAnim;
	Animation secondAnim;
	Animation thirdAnim;
	Animation explosionAnim;

	Animation* currentAnimation2 = nullptr;
	Animation idleAnim2;
	Animation beatingAnim2;

	
	

};