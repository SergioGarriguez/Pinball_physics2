#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	PhysBody* pbody;
	PhysBody* anchor;


	b2RevoluteJoint* revolution_joint;

};