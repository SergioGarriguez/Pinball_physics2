#include "Globals.h"
#include "Application.h"
#include "ModuleBumper.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleBoss.h"



ModuleBumper::ModuleBumper(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	idleAnim.PushBack({ 0, 0, 60, 60 });
	idleAnim.PushBack({ 60, 0, 60, 60 });
	idleAnim.PushBack({ 120, 0, 60, 60 });

	idleAnim.speed = 0.05f;

	beatingAnim.PushBack({ 0, 0, 60, 60 });
	beatingAnim.PushBack({ 60, 0, 60, 60 });
	beatingAnim.PushBack({ 120, 0, 60, 60 });

	beatingAnim.speed = 0.2f;


	idleAnim2.PushBack({ 0, 0, 60, 60 });
	idleAnim2.PushBack({ 60, 0, 60, 60 });
	idleAnim2.PushBack({ 120, 0, 60, 60 });

	idleAnim2.speed = 0.05f;

	beatingAnim2.PushBack({ 0, 0, 60, 60 });
	beatingAnim2.PushBack({ 60, 0, 60, 60 });
	beatingAnim2.PushBack({ 120, 0, 60, 60 });

	beatingAnim2.speed = 0.2f;
}

ModuleBumper::~ModuleBumper()
{}

// Load assets
bool ModuleBumper::Start()
{
	LOG("Loading player2");

	pbody = App->physics->CreateCircle(195, 500, 30, 1.2, STATIC);

	pbody->body->SetGravityScale(1);

	heart = App->textures->Load("pinball/heart2.png");
	currentAnimation = &idleAnim;
	currentAnimation2 = &idleAnim2;

	pbody2 = App->physics->CreateCircle(195, 300, 30, 1.2, STATIC);

	pbody2->body->SetGravityScale(2);


	pbody->listener = this;
	pbody2->listener = this;
	return true;


}

// Unload assets
bool ModuleBumper::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModuleBumper::Update()
{
	

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		bumper1 = false;
		bumper2 = false;
		currentAnimation = &idleAnim;
		currentAnimation2 = &idleAnim2;
		
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		bumper1 = false;
		bumper2 = false;
		currentAnimation = &idleAnim;
		currentAnimation2 = &idleAnim2;
	}

	App->renderer->Blit(heart, METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 30, METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 30, &rect, 1.0f, pbody->GetRotation());
	App->renderer->Blit(heart, METERS_TO_PIXELS(pbody2->body->GetTransform().p.x) - 30, METERS_TO_PIXELS(pbody2->body->GetTransform().p.y) - 30, &rect2, 1.0f, pbody2->GetRotation());
	
	//LOG("%d", currentAnimation->GetCurrentFrame());
	currentAnimation->Update();
	currentAnimation2->Update();

	return UPDATE_CONTINUE;
}

void ModuleBumper::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Play Audio FX on every collision, regardless of who is colliding
	//if (bodyB->body->GetType() == b2_staticBody)

	if (bodyB->body->IsBullet())
	{
		if (bodyA->body->GetGravityScale() == 1)
		{
			bumper1 = true;

			currentAnimation = &beatingAnim;

		}
		else if (bodyA->body->GetGravityScale() == 2)
		{
			bumper2 = true;
			currentAnimation2 = &beatingAnim2;

		}
		score += 50;

		if (bumper1 && bumper2)
		{
			score += 200;
			LOG("combo");
			bumper1 = false;
			bumper2 = false;

			currentAnimation = &idleAnim;
			currentAnimation2 = &idleAnim2;
		}
	}
	
	LOG("prev score: %d", prev_score);
	LOG("max score: %d", max_score);
	LOG("now score: %d", score);

	
	

	// Do something else. You can also check which bodies are colliding (sensor? ball? player?)
}

void ModuleBumper::SetScore()
{
	prev_score = score;
	if (score > max_score)
	{
		max_score = score;
	}
	score = 0;
	bumper1 = false;
	bumper2 = false;
	currentAnimation = &idleAnim;
	currentAnimation2 = &idleAnim2;
	App->boss->Reset();
}

void ModuleBumper::AddScore(int amount)
{
	score += amount;
	LOG("prev score: %d", prev_score);
	LOG("max score: %d", max_score);
	LOG("now score: %d", score);
}

int ModuleBumper::GetScore()
{
	return score;
}



