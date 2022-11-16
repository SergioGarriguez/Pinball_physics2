#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"




ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	flipper = App->textures->Load("pinball/flipper.png");

	anchor = App->physics->CreateRectangle(365, 773, 20, 20, 0.9, STATIC, 1);

	pbody = App->physics->CreateRectangle(297, 783, 80, 20, 0.3, DYNAMIC, 1000);
	pbody->body->SetGravityScale(0);
	//pbody->body->
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = pbody->body;
	revoluteJointDef.bodyB = anchor->body;
	revoluteJointDef.collideConnected = false;

	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(40), 0);
	revoluteJointDef.localAnchorB.Set(0,0 );

	revoluteJointDef.enableLimit = true;
	revoluteJointDef.lowerAngle = -55 * DEGTORAD;
	revoluteJointDef.upperAngle = 5 * DEGTORAD;

	

	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = -25000;
	//revoluteJointDef.motorSpeed = 360 * DEGTORAD;

	App->physics->CreateRevJoint(revolution_joint, revoluteJointDef);

	//revolution_joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
	
	

	pbody->listener = this;
	return true;


}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		// Enable raycast mode
		

		pbody->body->ApplyTorque(290000, true);
	}

	

	App->renderer->Blit(flipper, METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 40, METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 10, NULL, 1.0f, pbody->GetRotation());

	//> data->GetRotation()

	return UPDATE_CONTINUE;
}



