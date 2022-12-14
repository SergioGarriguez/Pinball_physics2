#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleBumper.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer
	//circle = box = NULL;
	ray_on = false;
	sensed = false;

	idleAnim.PushBack({ 0, 0, 40, 40 });
	idleAnim.PushBack({ 40, 0, 40, 40 });
	idleAnim.PushBack({ 80, 0, 40, 40 });
	idleAnim.PushBack({ 120, 0, 40, 40 });
	idleAnim.PushBack({ 160, 0, 40, 40 });
	

	idleAnim.PushBack({ 0, 40, 40, 40 });
	idleAnim.PushBack({ 40, 40, 40, 40 });
	idleAnim.PushBack({ 80, 40, 40, 40 });
	idleAnim.PushBack({ 120, 40, 40, 40 });
	idleAnim.PushBack({ 160, 40, 40, 40 });
	

	idleAnim.PushBack({ 0, 80, 40, 40 });
	idleAnim.PushBack({ 40, 80, 40, 40 });
	idleAnim.PushBack({ 80, 80, 40, 40 });
	idleAnim.PushBack({ 120, 80, 40, 40 });
	idleAnim.PushBack({ 160, 80, 40, 40 });
	

	idleAnim.PushBack({ 0, 120, 40, 40 });
	idleAnim.PushBack({ 40, 120, 40, 40 });
	idleAnim.PushBack({ 80, 120, 40, 40 });
	idleAnim.PushBack({ 120, 120, 40, 40 });
	idleAnim.PushBack({ 160, 120, 40, 40 });
	

	idleAnim.PushBack({ 0, 160, 40, 40 });
	idleAnim.PushBack({ 40, 160, 40, 40 });
	idleAnim.PushBack({ 80, 160, 40, 40 });
	idleAnim.PushBack({ 120, 160, 40, 40 });
	idleAnim.PushBack({ 160, 160, 40, 40 });
	

	idleAnim.PushBack({ 0, 200, 40, 40 });
	idleAnim.PushBack({ 40, 200, 40, 40 });
	idleAnim.PushBack({ 80, 200, 40, 40 });
	idleAnim.PushBack({ 120, 200, 40, 40 });
	//idleAnim.PushBack({ 160, 200, 40, 40 });

	idleAnim.speed = 0.2f;
}

ModuleSceneIntro::~ModuleSceneIntro()
{
	// You should do some memory cleaning here, if required
}

bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	circle = App->textures->Load("pinball/ball2.png"); 
	background = App->textures->Load("pinball/background.png");
	currentAnimation = &idleAnim;

	
	bonus_fx = App->audio->LoadFx("pinball/blood.wav");

	int wall[104] = {
			324, 867,
			324, 808,
			395, 765,
			395, 700,
			361, 655,
			403, 617,
			356, 539,
			356, 479,
			400, 429,
			400, 365,
			365, 345,
			365, 300,
			400, 250,
			425, 250,
			425, 800,
			475, 800,
			475, 240,
			460, 208,
			450, 190,
			430, 170,
			400, 152,
			370, 140,
			320, 130,
			280, 127,
			245, 126,
			190, 130,
			150, 150,
			120, 155,
			95, 170,
			75, 190,
			70, 210,
			67, 247,
			46, 260,
			46, 312,
			86, 345,
			86, 422,
			60, 445,
			60, 510,
			100, 575,
			56, 630,
			85, 675,
			60, 695,
			60, 730,
			100, 760,
			100, 780,
			200, 815,
			200, 867,
			1, 867,
			1, 1,
			510, 1,
			510, 867,
			430, 867
	};
	App->physics->CreateChain(0, 0, wall, 104, 0.9, STATIC);

	

	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

update_status ModuleSceneIntro::Update()
{
	// If user presses SPACE, enable RayCast
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		// Enable raycast mode
		ray_on = !ray_on;

		// Origin point of the raycast is be the mouse current position now (will not change)
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		if (circles.getLast() != NULL)
		{
			circles.getLast()->data->~PhysBody();
			App->bumper->SetScore();
		}
		//circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 20));
		circles.add(App->physics->CreateCircle(460, 510, 20, Restitution, DYNAMIC));

		
		circles.getLast()->data->listener = this;
		circles.getLast()->data->body->SetBullet(true);
		lives = 3;

		//LOG("%d lives", lives);
		
		
	}


	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_REPEAT)
	{
		
		//circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 20));
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 3, Restitution, DYNAMIC));


		circles.getLast()->data->listener = this;
		circles.getLast()->data->body->SetBullet(true);

	}
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		Restitution -= 0.1;
		if (circles.getLast() != NULL)
		{
			circles.getLast()->data->~PhysBody();
			App->bumper->SetScore();
		}
		circles.add(App->physics->CreateCircle(460, 510, 20, Restitution, DYNAMIC));
		circles.getLast()->data->listener = this;
		circles.getLast()->data->body->SetBullet(true);
		lives = 3;
	}
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN && Restitution < 1.5)
	{
		Restitution += 0.1;
		LOG("%f ", Restitution);
		if (circles.getLast() != NULL)
		{
			circles.getLast()->data->~PhysBody();
			App->bumper->SetScore();
		}
		circles.add(App->physics->CreateCircle(460, 510, 20, Restitution, DYNAMIC));
		circles.getLast()->data->listener = this;
		circles.getLast()->data->body->SetBullet(true);
		lives = 3;
	}
	if (circles.getLast() != NULL)
	{
		if (METERS_TO_PIXELS(circles.getLast()->data->body->GetTransform().p.y) > SCREEN_HEIGHT +50)
		{
			circles.getLast()->data->body->SetTransform(b2Vec2(PIXEL_TO_METERS(460), PIXEL_TO_METERS(510)), 0);
			circles.getLast()->data->body->SetLinearVelocity(b2Vec2(0, 0));

			lives--;
			//LOG("%d lives", lives);

			if (lives <= 0)
			{
				App->bumper->SetScore();
				//LOG("%d lives, you lost", lives);
				lives = 3;
				
			}

			
		}
		
	}

	if (App->input->GetKey(SDL_SCANCODE_W))
	{
		if (circles.getLast() != NULL)
		{

			if (METERS_TO_PIXELS(circles.getLast()->data->body->GetTransform().p.y) > 750  && METERS_TO_PIXELS(circles.getLast()->data->body->GetTransform().p.x) < 200)
			{
				circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(0, -20), true);
				
			}
			
		}
		
		
	}
	
	

	
	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		App->physics->ChangeGravity(-0.1);
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// 
		App->physics->ChangeGravity(0.1);
	}

	
	
	// The target point of the raycast is the mouse current position (will change over game time)
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// Total distance of the raycast reference segment
	int ray_hit = ray.DistanceTo(mouse);

	// Declare a vector. We will draw the normal to the hit surface (if we hit something)
	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------

	// Circles
	p2List_item<PhysBody*>* c = circles.getFirst();

	

	App->renderer->Blit(background, 0, 0, NULL, 1.0f, 0);
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);

		// If mouse is over this circle, paint the circle's texture
		if (c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
		{
			//App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		}
		SDL_Rect rect = currentAnimation->GetCurrentFrame();

		App->renderer->Blit(circle, x, y, &rect, 1.0f, c->data->GetRotation());
		
		
		auto vel = c->data->body->GetLinearVelocity();
		float velmod = vel.Length();
		
		if (velmod > 200)
		{
			c->data->body->SetLinearVelocity(b2Vec2(c->data->body->GetLinearVelocity().x / 8, c->data->body->GetLinearVelocity().y / 8));
		}
		
		

		c = c->next;
	}

	

	//if(currentAnimation->GetCurrentFrame() == )
	//currentAnimation->Reset();
	currentAnimation->Update();
	
	

	// Raycasts -----------------
	if(ray_on == true)
	{
		// Compute the vector from the raycast origin up to the contact point (if we're hitting anything; otherwise this is the reference length)
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		// Draw a line from origin to the hit point (or reference length if we are not hitting anything)
		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		// If we are hitting something with the raycast, draw the normal vector to the contact point
		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	// Keep playing
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Play Audio FX on every collision, regardless of who is colliding
	//if (bodyB->body->GetType() == b2_staticBody)

	


	App->audio->PlayFx(bonus_fx);

	// Do something else. You can also check which bodies are colliding (sensor? ball? player?)
}

float ModuleSceneIntro::GetBallPosX()
{
	if (circles.getLast() != NULL)
	{
		return METERS_TO_PIXELS(circles.getLast()->data->body->GetTransform().p.x);
	}
	
}

float ModuleSceneIntro::GetBallPosY()
{
	if (circles.getLast() != NULL)
	{
		return METERS_TO_PIXELS(circles.getLast()->data->body->GetTransform().p.y);
	}

}

int ModuleSceneIntro::GetLives()
{
	return lives;
}

void ModuleSceneIntro::PlusLives()
{
	lives++;
}