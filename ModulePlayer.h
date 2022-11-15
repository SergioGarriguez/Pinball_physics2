#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();
	
	bool Start();
	update_status Update();
	bool CleanUp();

public:

	int something;
	// Textures
	SDL_Texture* flipper;


	PhysBody* pbody;
	PhysBody* anchor;


	b2RevoluteJoint* revolution_joint;

	

};