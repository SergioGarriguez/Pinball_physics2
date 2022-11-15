#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"

class ModuleBumper : public Module
{
public:
	ModuleBumper(Application* app, bool start_enabled = true);
	virtual ~ModuleBumper();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void SetScore();


public:
	PhysBody* pbody;
	PhysBody* pbody2;

	bool bumper1 = false;
	bool bumper2 = false;

	int score = 0;
	int max_score = 0;

	b2PrismaticJoint* prismatic_joint;
	

};