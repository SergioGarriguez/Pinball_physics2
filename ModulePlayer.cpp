#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
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

	anchor = App->physics->CreateRectangle(365, 775, 20, 20, 0.9, STATIC);

	pbody = App->physics->CreateRectangle(297, 785, 80, 20, 0.9, DYNAMIC);
	pbody->body->SetGravityScale(0);
	//pbody->body->
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = pbody->body;
	revoluteJointDef.bodyB = anchor->body;
	revoluteJointDef.collideConnected = false;

	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(40), 0);
	revoluteJointDef.localAnchorB.Set(0,0 );

	revoluteJointDef.enableLimit = true;
	revoluteJointDef.lowerAngle = -65 * DEGTORAD;
	revoluteJointDef.upperAngle = 5 * DEGTORAD;

	

	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = -100;
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
		

		pbody->body->ApplyTorque(1000, true);
	}

	return UPDATE_CONTINUE;
}



