#include "Globals.h"
#include "Application.h"
#include "ModuleSensor.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleBoss.h"
#include "ModuleSceneIntro.h"



ModuleSensor::ModuleSensor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleSensor::~ModuleSensor()
{}

// Load assets
bool ModuleSensor::Start()
{
	LOG("Loading sensor");

	

	pbody = App->physics->CreateRectangleSensor(450, 420, 35, 150);
	

	pbody->body->SetGravityScale(3);

	pbody->listener = this;


	pbody2 = App->physics->CreateRectangleSensor(370, 220, 35, 150);


	pbody2->body->SetGravityScale(4);

	pbody2->listener = this;


	return true;

}

// Unload assets
bool ModuleSensor::CleanUp()
{
	LOG("Unloading sensor");

	return true;
}

// Update: draw background
update_status ModuleSensor::Update()
{
	


	return UPDATE_CONTINUE;
}

bool ModuleSensor::IsClosed()
{
	return closed;
}


void ModuleSensor::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB->body->IsBullet())
	{

		
		if (bodyA->body->GetGravityScale() == 3)
		{
			closed = false;

		}
		else if (bodyA->body->GetGravityScale() == 4)
		{
			closed = true;
		}
		

		
	}
	
}





