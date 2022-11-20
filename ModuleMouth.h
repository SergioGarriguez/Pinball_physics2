#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Animation.h"
#include "ModuleFonts.h"

class ModuleMouth : public Module
{
public:
	ModuleMouth(Application* app, bool start_enabled = true);
	virtual ~ModuleMouth();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void BeginContact(b2Contact* contact);


public:
	PhysBody* pbody;
	

	SDL_Texture* mouth;

	

	

	

	Animation* currentAnimation = nullptr;
	Animation idleAnim;
	Animation bitingAnim;

	

	

	
	

};