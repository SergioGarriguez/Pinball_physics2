#include "Globals.h"
#include "Application.h"
#include "ModulePiston.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"


ModulePiston::ModulePiston(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	idleAnim.PushBack({ 0, 0, 32, 270 });
	idleAnim.PushBack({ 32, 0, 32, 270 });
	idleAnim.PushBack({ 64, 0, 32, 270 });
	idleAnim.PushBack({ 96, 0, 32, 270 });
	idleAnim.PushBack({ 128, 0, 32, 270 });
	idleAnim.PushBack({ 160, 0, 32, 270 });
	idleAnim.PushBack({ 192, 0, 32, 270 });
	idleAnim.PushBack({ 224, 0, 32, 270 });
	idleAnim.PushBack({ 256, 0, 32, 270 });
	idleAnim.PushBack({ 288, 0, 32, 270 });
	idleAnim.PushBack({ 320, 0, 32, 270 });
	idleAnim.PushBack({ 352, 0, 32, 270 });
	idleAnim.PushBack({ 384, 0, 32, 270 });
	idleAnim.PushBack({ 416, 0, 32, 270 });
	idleAnim.PushBack({ 448, 0, 32, 270 });
	idleAnim.PushBack({ 480, 0, 32, 270 });
	idleAnim.PushBack({ 512, 0, 32, 270 });
	idleAnim.PushBack({ 544, 0, 32, 270 });
	idleAnim.PushBack({ 576, 0, 32, 270 });
	idleAnim.PushBack({ 608, 0, 32, 270 });
	idleAnim.PushBack({ 640, 0, 32, 270 });
	idleAnim.PushBack({ 672, 0, 32, 270 });
	
	idleAnim.speed = 0.28f;


	secondAnim.PushBack({ 672, 0, 32, 270 });
	secondAnim.PushBack({ 640, 0, 32, 270 });
	secondAnim.PushBack({ 608, 0, 32, 270 });
	secondAnim.PushBack({ 576, 0, 32, 270 });
	secondAnim.PushBack({ 544, 0, 32, 270 });
	secondAnim.PushBack({ 512, 0, 32, 270 });
	secondAnim.PushBack({ 480, 0, 32, 270 });
	secondAnim.PushBack({ 448, 0, 32, 270 });
	secondAnim.PushBack({ 416, 0, 32, 270 });
	secondAnim.PushBack({ 384, 0, 32, 270 });
	secondAnim.PushBack({ 352, 0, 32, 270 });
	secondAnim.PushBack({ 320, 0, 32, 270 });
	secondAnim.PushBack({ 288, 0, 32, 270 });
	secondAnim.PushBack({ 256, 0, 32, 270 });
	secondAnim.PushBack({ 224, 0, 32, 270 });
	secondAnim.PushBack({ 192, 0, 32, 270 });
	secondAnim.PushBack({ 160, 0, 32, 270 });
	secondAnim.PushBack({ 128, 0, 32, 270 });
	secondAnim.PushBack({ 96, 0, 32, 270 });
	secondAnim.PushBack({ 64, 0, 32, 270 });
	secondAnim.PushBack({ 32, 0, 32, 270 });
	secondAnim.PushBack({ 0, 0, 32, 270 });

	secondAnim.speed = 1.35f;

	thirdAnim.PushBack({ 0, 270, 32, 270 });
	thirdAnim.PushBack({ 32, 270, 32, 270 });

	thirdAnim.speed = 0.2f;
}

ModulePiston::~ModulePiston()
{}

// Load assets
bool ModulePiston::Start()
{
	LOG("Loading player2");

	veins = App->textures->Load("pinball/veins.png");
	currentAnimation = &secondAnim;
	currentAnimation->loop = false;

	anchor = App->physics->CreateRectangle(412, 721, 20, 20, 0, STATIC, 1);

	pbody = App->physics->CreateRectangle(445, 750, 30, 30, 0, DYNAMIC, 1);

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
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		
		aux = 22.0f;
		currentAnimation->loop = false;
		currentAnimation = &idleAnim;
		LOG("gggggg %d", currentAnimation->HasFinished());
		currentAnimation->loop = false;
		currentAnimation->Reset();
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		// Enable raycast mode
		
		
		if (currentAnimation->HasFinished())
		{
			//currentAnimation->Reset();
			
			aux = aux - currentAnimation->WhichIsCurrentFrame() - 1;
			currentAnimation = &thirdAnim;
			currentAnimation->loop = true;
			
		}
		pbody->body->ApplyForce(b2Vec2(0, 200), pbody->body->GetWorldCenter(), true);

		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->renderer->Blit(veins, 435, 535, &rect, 1.0f, 0);
		currentAnimation->Update();
		//pbody->body->ApplyTorque(-1000, true);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		if (currentAnimation->loop == false)
		{
			aux = aux - currentAnimation->WhichIsCurrentFrame() - 1;
		}

		
		
		currentAnimation->loop = false;
		currentAnimation = &secondAnim;
		//currentAnimation->loop = false;
		currentAnimation->SetCurrentFrame(aux);
		//currentAnimation->Reset();

		
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) != KEY_REPEAT)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->renderer->Blit(veins, 435, 535, &rect, 1.0f, 0);
		currentAnimation->Update();
	}

	//LOG("frame: %f", currentAnimation->WhichIsCurrentFrame());

	//LOG("...................... %d", METERS_TO_PIXELS(pbody->body->GetTransform().p.y));
	

	return UPDATE_CONTINUE;
}



