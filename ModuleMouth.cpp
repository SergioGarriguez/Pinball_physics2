#include "Globals.h"
#include "Application.h"
#include "ModuleMouth.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSensor.h"
#include "ModuleSceneIntro.h"



ModuleMouth::ModuleMouth(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	idleAnim.PushBack({ 0, 0, 20, 90 });
	

	idleAnim.speed = 0.05f;

	bitingAnim.PushBack({ 20, 0, 20, 90 });
	

	bitingAnim.speed = 0.2f;


	
}

ModuleMouth::~ModuleMouth()
{}

// Load assets
bool ModuleMouth::Start()
{
	LOG("Loading bumper");

	mouth = App->textures->Load("pinball/mouth.png");
	currentAnimation = &idleAnim;

	//pbody = App->physics->CreateRectangle(405, 203, 0.000000001f, 90, 0.9, KINEMATIC, 0);
	

	//pbody->body->SetGravityScale(42);

	
	

	//pbody->listener = this;
	return true;

}

// Unload assets
bool ModuleMouth::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModuleMouth::Update()
{
	

	if (App->sensor->IsClosed())
	{
		currentAnimation = &bitingAnim;
	}
	else
	{
		currentAnimation = &idleAnim;
	}

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	

	

	App->renderer->Blit(mouth, 405, 203 - 45, &rect, 1.0f, 0);
	
	
	//LOG("%d", currentAnimation->GetCurrentFrame());
	currentAnimation->Update();
	



	

	

	return UPDATE_CONTINUE;
}

void ModuleMouth::BeginContact(b2Contact* contact)
{
	
}

void ModuleMouth::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
	
}





