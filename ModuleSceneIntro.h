#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:

	// Constructors & Destructors
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	float GetBallPosX();
	float GetBallPosY();
	int GetLives();
	void PlusLives();

public:

	float Restitution = 0.0f;

	// Lists of physics objects
	p2List<PhysBody*> circles;
	

	int lives = 3;

	// Lower ground sensor (will kill all objects passig through it)
	PhysBody* lower_ground_sensor;
	bool sensed;

	// Textures
	SDL_Texture* circle;
	SDL_Texture* box;
	
	SDL_Texture* background;

	Animation* currentAnimation = nullptr;
	Animation idleAnim;

	// FX
	uint bonus_fx;
	

	// Raycast
	p2Point<int> ray;
	bool ray_on;
};
