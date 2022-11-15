#include "Globals.h"
#include "Application.h"
#include "ModulePiston.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


ModulePiston::ModulePiston(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePiston::~ModulePiston()
{}

// Load assets
bool ModulePiston::Start()
{
	LOG("Loading player2");

	anchor = App->physics->CreateRectangle(412, 721, 20, 20, 0, STATIC);

	pbody = App->physics->CreateRectangle(445, 750, 30, 30, 0, DYNAMIC);

	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.bodyA = anchor->body;
	prismaticJointDef.bodyB = pbody->body;
	prismaticJointDef.collideConnected = false;

	prismaticJointDef.localAnchorA.Set(0, 0);
	prismaticJointDef.localAnchorB.Set(0, 0);
	prismaticJointDef.localAxisA.Set(0, 1);
	prismaticJointDef.localAnchorB.Set(-0.8, 0);

	prismaticJointDef.enableLimit = true;
	prismaticJointDef.lowerTranslation = PIXEL_TO_METERS(-170);
	prismaticJointDef.upperTranslation = PIXEL_TO_METERS(50);

	prismaticJointDef.enableMotor = true;
	prismaticJointDef.maxMotorForce = 200;
	prismaticJointDef.motorSpeed = -1000;


	App->physics->CreatePrisJoint(prismatic_joint, prismaticJointDef);


	//pbody->body->SetGravityScale(0);
	////pbody->body->
	//b2RevoluteJointDef revoluteJointDef;
	//revoluteJointDef.bodyA = pbody->body;
	//revoluteJointDef.bodyB = anchor->body;
	//revoluteJointDef.collideConnected = false;
	//
	//revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(-40), 0);
	//revoluteJointDef.localAnchorB.Set(0,0 );
	//
	//revoluteJointDef.enableLimit = true;
	//revoluteJointDef.lowerAngle = -7 * DEGTORAD;
	//revoluteJointDef.upperAngle = 60 * DEGTORAD;
	//
	//revoluteJointDef.enableMotor = true;
	//revoluteJointDef.maxMotorTorque = 100;
	//revoluteJointDef.motorSpeed = -10;
	//
	//
	//App->physics->CreateRevJoint(revolution_joint, revoluteJointDef);

	//revolution_joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
	
	


	pbody->listener = this;
	return true;


}

// Unload assets
bool ModulePiston::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePiston::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		// Enable raycast mode
		
		pbody->body->ApplyForce(b2Vec2(0, 200), pbody->body->GetWorldCenter(), true);
		//pbody->body->ApplyTorque(-1000, true);
	}
	

	return UPDATE_CONTINUE;
}



