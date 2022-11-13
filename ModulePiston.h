#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"

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


	b2PrismaticJoint* prismatic_joint;
	

};