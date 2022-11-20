#include "Globals.h"
#include "Application.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


ModulePlayer2::ModulePlayer2(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player2");

	flipper = App->textures->Load("pinball/flipper2.png");

	anchor = App->physics->CreateRectangle(150, 785, 20, 20, 0.9, STATIC, 1);

	pbody = App->physics->CreateRectangle(120, 785, 80, 20, 0.3, DYNAMIC, 1000);
	pbody->body->SetGravityScale(0);
	//pbody->body->
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = pbody->body;
	revoluteJointDef.bodyB = anchor->body;
	revoluteJointDef.collideConnected = false;

	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(-40), 0);
	revoluteJointDef.localAnchorB.Set(0,0 );

	revoluteJointDef.enableLimit = true;
	revoluteJointDef.lowerAngle = -7 * DEGTORAD;
	revoluteJointDef.upperAngle = 60 * DEGTORAD;

	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 15000;
	revoluteJointDef.motorSpeed = -1500;
	

	App->physics->CreateRevJoint(revolution_joint, revoluteJointDef);

	//revolution_joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
	


	pbody->listener = this;
	return true;


}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		// Enable raycast mode
		

		pbody->body->ApplyTorque(-340000, true);
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		//LOG("     %f", pbody->body->GetAngle() * RADTODEG);
		if (pbody->body->GetAngle() * RADTODEG < -45)
		{
			//pbody->body->ApplyTorque(290000, true);
			pbody->body->SetAngularVelocity(-5);
		}
	}

	

	App->renderer->Blit(flipper, METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 40, METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 10, NULL, 1.0f, pbody->GetRotation());
	

	return UPDATE_CONTINUE;
}



