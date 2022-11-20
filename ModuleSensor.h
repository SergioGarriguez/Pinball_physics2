#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"

class ModuleSensor : public Module
{
public:
	ModuleSensor(Application* app, bool start_enabled = true);
	virtual ~ModuleSensor();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	bool IsClosed();
	


public:
	PhysBody* pbody;
	PhysBody* pbody2;
	bool closed = false;


	

};