#include "Globals.h"
#include "Application.h"
#include "ModuleBumper.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleBoss.h"
#include "ModuleSceneIntro.h"



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
	LOG("Loading bumper");

	pbody = App->physics->CreateCircle(195, 500, 30, 1.2, STATIC);

	pbody->body->SetGravityScale(1);

	sfx = App->audio->LoadFx("pinball/meat2.wav");
	sfx2 = App->audio->LoadFx("pinball/combo.wav");

	heart = App->textures->Load("pinball/heart2.png");
	currentAnimation = &idleAnim;
	currentAnimation2 = &idleAnim2;

	pbody2 = App->physics->CreateCircle(195, 300, 30, 1.2, STATIC);

	pbody2->body->SetGravityScale(2);


	pbody->listener = this;
	pbody2->listener = this;


	char lookupTable[] = { "abcdefghijklmnopqrstuvwxyz0123456789:R =+-&([]|/_)!" };
	scoreFont = App->fonts->Load("pinball/Font.png", lookupTable, 1);



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
	
	
	currentAnimation->Update();
	currentAnimation2->Update();



	sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->BlitText(100, 20, scoreFont, scoreText);
	App->fonts->BlitText(20, 20, scoreFont, "score");

	sprintf_s(scoreText, 10, "%7d", max_score);
	App->fonts->BlitText(100, 40, scoreFont, scoreText);
	App->fonts->BlitText(20, 40, scoreFont, "max");

	sprintf_s(scoreText, 10, "%7d", prev_score);
	App->fonts->BlitText(100, 60, scoreFont, scoreText);
	App->fonts->BlitText(20, 60, scoreFont, "prev");

	sprintf_s(scoreText, 10, "%7d", App->scene_intro->GetLives());
	App->fonts->BlitText(100, 90, scoreFont, scoreText);
	App->fonts->BlitText(20, 90, scoreFont, "lives");

	if (App->boss->IsBeaten())
	{
		App->fonts->BlitText(270, 40, scoreFont, "victory");
	}

	return UPDATE_CONTINUE;
}

void ModuleBumper::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	

	if (bodyB->body->IsBullet())
	{

		App->audio->PlayFx(sfx);
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
			App->audio->PlayFx(sfx2);

			currentAnimation = &idleAnim;
			currentAnimation2 = &idleAnim2;
		}
	}
	
	
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
	
}

int ModuleBumper::GetScore()
{
	return score;
}



