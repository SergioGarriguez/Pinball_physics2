#include "Globals.h"
#include "Application.h"
#include "ModuleBoss.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"



ModuleBoss::ModuleBoss(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	idleAnim.PushBack({ 0, 0, 40, 40 });
	idleAnim.PushBack({ 40, 0, 40, 40 });
	

	idleAnim.speed = 0.1f;

	secondAnim.PushBack({ 0, 40, 40, 40 });
	secondAnim.PushBack({ 40, 40, 40, 40 });
	

	secondAnim.speed = 0.1f;


	hits_taken = 0;
	
}

ModuleBoss::~ModuleBoss()
{}

// Load assets
bool ModuleBoss::Start()
{
	LOG("Loading player2");

	pbody = App->physics->CreateCircle(250, 500, 20, 1, DYNAMIC);

	pbody->body->SetGravityScale(0);

	heart = App->textures->Load("pinball/saucer.png");
	currentAnimation = &idleAnim;
	

	pbody->body->SetFixedRotation(true);
	pbody->body->ApplyForceToCenter(b2Vec2(rand()%400 - 200, rand() % 400 - 200), true);

	


	//if (hits_taken > 1 && hits_taken <= 99)
	//{
	//	pbody->body->ApplyForceToCenter(b2Vec2(100, 0), true);
	//}


	
	


	pbody->listener = this;
	
	return true;


}

// Unload assets
bool ModuleBoss::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModuleBoss::Update()
{
	
	if (METERS_TO_PIXELS(pbody->body->GetTransform().p.y) > 850)
	{
		pbody->body->SetTransform(b2Vec2(PIXEL_TO_METERS(250), PIXEL_TO_METERS(500)), 0);
		
	}


	if (hits_taken > 1 && hits_taken <= 99)
	{
		//pbody->body->SetLinearVelocity(b2Vec2(rand() % 40 - 20, rand() % 40 - 20));


		currentAnimation = &secondAnim;
	}



	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	App->renderer->Blit(heart, METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 20, METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 20, &rect, 1.0f, pbody->GetRotation());
	
	//LOG("%d", currentAnimation->GetCurrentFrame());
	currentAnimation->Update();
	

	return UPDATE_CONTINUE;
}

void ModuleBoss::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Play Audio FX on every collision, regardless of who is colliding
	//if (bodyB->body->GetType() == b2_staticBody)

	if (bodyB->body->IsBullet())
	{
		hits_taken++;
	}

	

	LOG("hits taken: %d", hits_taken);

	
	

	// Do something else. You can also check which bodies are colliding (sensor? ball? player?)
}

void ModuleBoss::SetScore()
{
	
	
}



