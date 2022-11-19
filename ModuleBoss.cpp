#include "Globals.h"
#include "Application.h"
#include "ModuleBoss.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleBumper.h"



ModuleBoss::ModuleBoss(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	idleAnim.PushBack({ 0, 0, 40, 40 });
	idleAnim.PushBack({ 40, 0, 40, 40 });
	

	idleAnim.speed = 0.1f;

	secondAnim.PushBack({ 0, 40, 40, 40 });
	secondAnim.PushBack({ 40, 40, 40, 40 });
	

	secondAnim.speed = 0.1f;

	thirdAnim.PushBack({ 0, 80, 40, 40 });
	thirdAnim.PushBack({ 40, 80, 40, 40 });


	thirdAnim.speed = 0.1f;

	idleAnim2.PushBack({ 0, 0, 80, 80 });
	idleAnim2.PushBack({ 80, 0, 80, 80 });
	idleAnim2.PushBack({ 160, 0, 80, 80 });
	idleAnim2.PushBack({ 240, 0, 80, 80 });
	idleAnim2.PushBack({ 320, 0, 80, 80 });
	idleAnim2.PushBack({ 400, 0, 80, 80 });
	idleAnim2.PushBack({ 480, 0, 80, 80 });


	idleAnim2.speed = 0.2f;


	hits_taken = 0;
	
}

ModuleBoss::~ModuleBoss()
{}

// Load assets
bool ModuleBoss::Start()
{
	LOG("Loading player2");

	

	saucer = App->textures->Load("pinball/saucer.png");
	explosion = App->textures->Load("pinball/explosion.png");
	currentAnimation = &idleAnim;
	currentAnimation2 = &idleAnim2;
	

	

	


	//if (hits_taken > 1 && hits_taken <= 99)
	//{
	//	pbody->body->ApplyForceToCenter(b2Vec2(100, 0), true);
	//}


	
	


	
	
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
	if (destroy)
	{
		pbody->~PhysBody();
		destroy = false;
	}

	if (!HasSpawned && App->bumper->GetScore() > 1000)
	{
		pbody = App->physics->CreateCircle(250, 500, 20, 1, DYNAMIC);

		pbody->body->SetGravityScale(0);

		pbody->body->SetFixedRotation(true);
		pbody->body->ApplyForceToCenter(b2Vec2(rand() % 400 - 200, rand() % 400 - 200), true);

		pbody->listener = this;

		HasSpawned = true;
		currentAnimation = &idleAnim;
	}

	
	if (HasSpawned && !BossBeaten)
	{
		if (METERS_TO_PIXELS(pbody->body->GetTransform().p.y) > 850 || METERS_TO_PIXELS(pbody->body->GetTransform().p.x) > 440)
		{
			pbody->body->SetTransform(b2Vec2(PIXEL_TO_METERS(250), PIXEL_TO_METERS(500)), 0);

		}


		if (hits_taken > 1 && hits_taken <= 3)
		{
			//pbody->body->SetLinearVelocity(b2Vec2(rand() % 40 - 20, rand() % 40 - 20));

			int X = App->scene_intro->GetBallPosX();
			int Y = App->scene_intro->GetBallPosY();

			if (X < METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y < METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(5, 5));
			}
			else if (X > METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y < METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(-5, 5));
			}
			else if (X < METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y > METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(5, -5));
			}
			else if (X > METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y > METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(-5, -5));
			}
			currentAnimation = &secondAnim;
		}

		else if (hits_taken > 3 && hits_taken <= 6)
		{
			//pbody->body->SetLinearVelocity(b2Vec2(rand() % 40 - 20, rand() % 40 - 20));

			int X = App->scene_intro->GetBallPosX();
			int Y = App->scene_intro->GetBallPosY();

			if (X < METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y < METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(-5, 5));
			}
			else if (X > METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y < METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(5, -5));
			}
			else if (X < METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y > METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(5, 5));
			}
			else if (X > METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y > METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(5, -5));
			}
		}
		else if (hits_taken > 6 && hits_taken <= 10)
		{
			//pbody->body->SetLinearVelocity(b2Vec2(rand() % 40 - 20, rand() % 40 - 20));

			int X = App->scene_intro->GetBallPosX();
			int Y = App->scene_intro->GetBallPosY();

			if (X < METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y < METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(8, 5));
			}
			else if (X > METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y < METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(-8, -5));
			}
			else if (X < METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y > METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(8, 5));
			}
			else if (X > METERS_TO_PIXELS(pbody->body->GetTransform().p.x) && Y > METERS_TO_PIXELS(pbody->body->GetTransform().p.y))
			{
				pbody->body->SetLinearVelocity(b2Vec2(-8, -5));
			}
		}
		else if (hits_taken > 10 && hits_taken <= 14)
		{
			pbody->body->SetLinearVelocity(b2Vec2(rand() % 40 - 20, rand() % 40 - 20));
			currentAnimation = &thirdAnim;


		}
		else if (hits_taken > 14)
		{
			if (!exploding)
			{
				pbody2 = App->physics->CreateCircle(METERS_TO_PIXELS(pbody->body->GetTransform().p.x), METERS_TO_PIXELS(pbody->body->GetTransform().p.y), 40, 2, STATIC);

				exploding = true;
				
				
			}
			pbody->~PhysBody();
			App->bumper->AddScore(3000);
			BossBeaten = true;

			
		}


		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		

		App->renderer->Blit(saucer, METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 20, METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 20, &rect, 1.0f, pbody->GetRotation());

		//LOG("%d", currentAnimation->GetCurrentFrame());
		currentAnimation->Update();
		
	}

	if (!has_exploded && exploding)
	{
		
		currentAnimation2->loop = false;
		//LOG("-------->>>>>>> %d", currentAnimation2->HasFinished());

		SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
		App->renderer->Blit(explosion, METERS_TO_PIXELS(pbody2->body->GetTransform().p.x) - 40, METERS_TO_PIXELS(pbody2->body->GetTransform().p.y) - 40, &rect2, 1.0f, pbody2->GetRotation());
		currentAnimation2->Update();
		if (currentAnimation2->HasFinished())
		{
			has_exploded = true;
			pbody2->~PhysBody();
			
		}
	}
	
	
	

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

	

	//LOG("hits taken: %d", hits_taken);

	
	

	// Do something else. You can also check which bodies are colliding (sensor? ball? player?)
}

void ModuleBoss::Reset()
{

	if (HasSpawned && !BossBeaten)
	{
		//b2FixtureDef fixture;
		//
		//pbody->body->DestroyFixture(&fixture);
		//
		//pbody->~PhysBody();
		//
		//BossBeaten = true;
		// This WAS A PROBLEM REMEMBER TO ADD IT TO THE README IT CRASHED SO I HAD TO USE THE VARIABLE DESTROY TO CON¡MPENSATE I GESS THAT IT WAS BECAUSE WHEN THE FUCTION RESET IS CALLED IT ACTS BEFORE THIS UPDATE SO IT STILL TRYES TO UPDATE
		destroy = true;
	}

	currentAnimation2->Reset();
	//currentAnimation2->
	hits_taken = 0;
	HasSpawned = false;
	BossBeaten = false;
	exploding = false;
	has_exploded = false;
	
}

bool ModuleBoss::IsBeaten()
{
	return BossBeaten;
}


